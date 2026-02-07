#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

#include "config.h"
#include "./src/helpers.h"
#include "./src/actions.h"
#include "./src/seeder.h"
#include "./src/config_parser/config.h"

// Function designed for chat between client and server.
void func(int connfd)
{
    char returnBuff[MAX];
    char clientBuff[MAX];
    // char serverBuff[MAX];
    // int n;
    // infinite loop for chat
    for (;;)
    {
        memset(returnBuff, 0, MAX);
        memset(clientBuff, 0, MAX);
        // memset(serverBuff, 0, MAX);

        // read the message from client and copy it in buffer
        read(connfd, clientBuff, sizeof(clientBuff));
        printf("From client: %s", clientBuff);

        char *actionMessage = action(clientBuff);

        // Backup if the message could not be allocated
        if (actionMessage != NULL && strlen(actionMessage) < MAX)
        {
            strcpy(returnBuff, actionMessage);
        }
        else
        {
            strcpy(returnBuff, "An uknown error occured action didnt return a message \n");
        }
        // printStorage();

        printf("Returning to client: %s", returnBuff);

        // print buffer which contains the client contents
        // n = 0;
        // while ((serverBuff[n++] = (char)getchar()) != '\n')
        //     ;

        
        free(actionMessage);
        
        printf("ClientBuff %s", clientBuff);
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
    int sockfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cli;

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
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");

    // Function for chatting between client and server
    func(connfd);

    printf("Closing socket... \n");
    // After chatting close the socket
    close(sockfd);
}