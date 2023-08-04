#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
int main()
{
    int k = 10, m = 1, client, y;
    char buffer[1024];
    struct sockaddr_in servAddr;
    client = socket(PF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5600);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    y = connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (y == -1)
    {
        printf("Error connection failed..\n");
        exit(1);
    }
    else
    {
        printf("Successfuly connected..\n");
    }
    while (k != 0)
    {
        if (m <= 10)
        {
            printf("sending\n");
        }
        if (m % 2 == 0)
        {
            strcpy(buffer, "frame");
        }
        else
        {
            strcpy(buffer, "error");
            printf("retransmitting..\n");
            for (int i = 1; i <= 3; i++)
            {
                printf("Waiting for %d\n", i);
            }
            strcpy(buffer, "frame");
            sleep(3);
        }
        int x = send(client, buffer, 19, 0);
        if (x == -1)
        {
            printf("Error..\n");
            exit(1);
        }
        else
        {
            printf("Sent..");
        }
        int z = recv(client, buffer, 19, 0);
        if (z == -1)
        {
            printf("Error");
            exit(1);
        }
        else
        {
            printf("Received..\n");
        }
        k--;
        m++;
        if (strncmp(buffer, "ack", 3) == 0)
        {
            printf("Acknowledgement received for %d\n", m - 1);
        }
        else
        {
            printf("Acknowledgement not received..\n");
        }
    }
    close(client);
}
