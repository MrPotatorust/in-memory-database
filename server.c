#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <sys/epoll.h>
#include <unistd.h> // read(), write(), close()
#define MAX_BUFFER_LENGTH 256
#define MAX_CONNECTIONS 1000
#define PORT 8080
#define SA struct sockaddr

#include "config.h"
#include "server.h"
#include "./src/helpers.h"
#include "./src/actions.h"
#include "./src/seeder.h"
#include "./src/config_parser/config.h"

// Function designed for chat between client and server.
void func(int connfd)
{
    char returnBuff[MAX_BUFFER_LENGTH];
    char clientBuff[MAX_BUFFER_LENGTH];
    char *actionMessage = NULL;
    // infinite loop for chat
    for (;;)
    {
        memset(returnBuff, 0, MAX_BUFFER_LENGTH);
        memset(clientBuff, 0, MAX_BUFFER_LENGTH);

        // read the message from client and copy it in buffer
        ssize_t nbytes = read(connfd, clientBuff, sizeof(clientBuff));

        if (nbytes <= 0)
        {
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
        if (strncmp("exit", clientBuff, 4) == 0)
        {
            printf("Server Exit...\n");
            write(connfd, "exit \n", sizeof(char) * 6);
            break;
        }
        write(connfd, returnBuff, sizeof(returnBuff));
    }
}

// Driver function
int main()
{
    int sockfd, connfd, epollfd, nfds;
    socklen_t addrlen;
    struct sockaddr_in servaddr, cli;
    struct epoll_event ev, events[MAX_CONNECTIONS];

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

    // Now server is ready to listen and verification
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
        nfds = epoll_wait(epollfd, events, MAX_CONNECTIONS, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

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

#include <fcntl.h>
#include <unistd.h>

int setnonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return -1;

    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}