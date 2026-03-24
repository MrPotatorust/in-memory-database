#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <sys/epoll.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include "config.h"
#include "server.h"
#include "./src/helpers.h"
#include "./src/actions.h"
#include "./src/seeder.h"
#include "./src/config_parser/config.h"

#define MAX_BUFFER_LENGTH 256
#define MAX_CONNECTIONS 1000
#define PORT 8080
#define SA struct sockaddr

#define PERSIST_EVERY_SECONDS 120
#define TIME_T_SECONDS_DIGITS 10
#define STORAGE_DIR_PATH "./storage"
#define STORAGE_FILE_EXT ".txt"

// The server function
void func(int connfd)
{
    char returnBuff[MAX_BUFFER_LENGTH];
    char clientBuff[MAX_BUFFER_LENGTH];
    char *actionMessage = NULL;

    memset(returnBuff, 0, MAX_BUFFER_LENGTH);
    memset(clientBuff, 0, MAX_BUFFER_LENGTH);

    // read the message from client and copy it in buffer
    ssize_t nbytes = read(connfd, clientBuff, sizeof(clientBuff));

    if (nbytes == 0)
    {
        printf("Closing socket %i \n", connfd);
        close(connfd);
        return;
    }

    if (nbytes < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            return;
        }

        printf("Closing socket %i due to read error\n", connfd);
        close(connfd);
        return;
    }

    clientBuff[strcspn(clientBuff, "\n")] = 0;

    actionMessage = action(clientBuff);

    // Backup if the message could not be allocated
    if (actionMessage != NULL && strlen(actionMessage) < MAX_BUFFER_LENGTH)
    {
        strcpy(returnBuff, actionMessage);
    }
    else
    {
        strcpy(returnBuff, "An uknown error occured action didnt return a message \n");
    }
    printStorage();

    free(actionMessage);
    actionMessage = NULL;

    printf("Returning to client: %s", returnBuff);
    write(connfd, returnBuff, sizeof(returnBuff));
}

// Driver function
int main()
{
    int sockfd, connfd, epollfd, nfds;
    socklen_t addrlen;
    struct sockaddr_in servaddr, cli;
    struct epoll_event ev, events[MAX_CONNECTIONS];

    time_t currentTime;
    time_t lastSaveTime = 0;

    srand((unsigned int)time(NULL));

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    memset(&servaddr, 0, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    printf("Server listening..\n");

    addrlen = sizeof(cli);
    epollfd = epoll_create1(0);
    if (epollfd == -1)
    {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1)
    {
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    for (;;)
    {
        time(&currentTime);

        // persist to local file
        if (labs((long int)currentTime - (long int)lastSaveTime) > PERSIST_EVERY_SECONDS)
        {
            persist();
        }

        nfds = epoll_wait(epollfd, events, MAX_CONNECTIONS, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        printf("New event \n");
        for (int n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == sockfd)
            {
                connfd = accept(sockfd,
                                (SA *)&cli, &addrlen);
                if (connfd == -1)
                {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                printf("Accepted socket %i \n", connfd);
                setnonblocking(connfd);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = connfd;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd,
                              &ev) == -1)
                {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                // Function for chatting between client and server
                func(events[n].data.fd);
            }
        }
    }
}

int setnonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return -1;

    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int persist()
{
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0:
        break;
    default:
        printf("Running persist in child %i \n", pid);
        return 0;
    }

    time_t saveTime;
    time(&saveTime);

    // Generate the filename from the current time
    char filePath[strlen(STORAGE_DIR_PATH) + TIME_T_SECONDS_DIGITS + strlen(STORAGE_FILE_EXT) + 2]; // slash + null terminator
    snprintf(filePath, sizeof(filePath), "%s/%li%s", STORAGE_DIR_PATH, saveTime, STORAGE_FILE_EXT);

    if (canAccessDir(STORAGE_DIR_PATH) != 0)
        return 1;

    persistStorage(filePath);

    return 0;
}
