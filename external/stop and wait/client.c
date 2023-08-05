#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int client, y, k = 5, m = 1, p;
    char buffer[1024];
    struct sockaddr_in servAddr;
    socklen_t addrSize;
    client = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5600);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    y = connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (y == -1)
    {
        printf("Error\n");
        exit(1);
    }
    while (k != 0)
    {
        if (m <= 5)
        {
            printf("Sending %d\n", m);
        }
        if (m % 2 == 0)
        {
            strcpy(buffer, "frame");
        }
        else
        {
            strcpy(buffer, "error");
            printf("Packet lose..\n");
            for (p = 1; p <= 3; p++)
            {
                printf("waiting for %d seconds\n", p);
            }
            printf("Retransmitting..\n");
            strcpy(buffer, "frame");
            sleep(3);
        }
        int x = send(client, buffer, 19, 0);
        if (x == -1)
        {
            printf("Error\n");
            exit(1);
        }
        else
        {
            printf("Sent %d\n", m);
        }
        int z = recv(client, buffer, 1024, 0);
        if (z == -1)
        {
            printf("Error in receiving ..\n");
            exit(1);
        }
        k--;
        m++;
        if (strncmp(buffer, "ack", 5) == 0)
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
