#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int server, x, k = 5, newSock, m = 1, p;
    char buffer[1024];
    struct sockaddr_in servAddr, clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    server = socket(PF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5600);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

    bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr));

    if (listen(server, 5) == 0)
    {
        printf("Listening..\n");
    }
    else
    {
        printf("Error\n");
    }

    newSock = accept(server, (struct sockaddr *)&clientAddr, &clientAddrSize);
    if (newSock == -1)
    {
        printf("Error occurred while accepting connection..\n");
        exit(1);
    }

    while (k != 0)
    {
        int y = recv(newSock, buffer, 1024, 0);
        if (y == -1)
        {
            printf("Error in receiving..\n");
            exit(1);
        }
        if (strncmp(buffer, "frame", 5) == 0)
        {
            printf("received %d successfully\n", m);
        }
        else
        {
            printf("did not receive %d\n", m);
        }
        if (m % 2 == 0)
        {
            strcpy(buffer, "ack");
        }
        else
        {
            strcpy(buffer, "kca");
            printf("Acknowledgement lost..\n");
            for (p = 1; p <= 3; p++)
            {
                printf("Waiting for %d seconds\n", p);
            }
            printf("retransmitting ack..\n");
            strcpy(buffer, "ack");
            sleep(3);
        }
        printf("Sending acknowledgement %d\n", m);
        int z = send(newSock, buffer, 19, 0);
        if (z == -1)
        {
            printf("Error in sending ..\n");
            exit(1);
        }
        k--;
        m++;
    }
    close(newSock);
}
