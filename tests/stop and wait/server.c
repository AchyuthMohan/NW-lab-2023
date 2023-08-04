#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int k = 10, m = 1, server, newSock;
    char buffer[1024];
    struct sockaddr_in servAddr, clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    
    server = socket(PF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5600);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (listen(server, 5) == 0)
    {
        printf("Listening..");
    }
    else
    {
        printf("Error in listening..");
    }
    newSock = accept(server, (struct sockaddr *)&clientAddr, &clientAddrSize);
    if (newSock == -1)
    {
        printf("Error in establishing connection");
        exit(1);
    }
    else{
        printf("Accept worked..\n");
    }
    while (k != 0)
    {
        int y = recv(newSock, buffer, 1024, 0);
        if (y == -1)
        {
            printf("Error");
            exit(1);
        }
        if (strncmp(buffer, "frame", 5) == 0)
        {
            printf("Frame %d received..\n", m);
        }
        else
        {
            printf("Frame lost..\n");
        }
        if (m % 2 == 0)
        {
            strcpy(buffer, "ack");
        }
        else
        {
            printf("Error in acknowledgement..\n");
            strcpy(buffer,"kca");
            for(int i=0;i<3;i++){
                printf("Waiting for %d seconds\n",i+1);
            }
            printf("Retransmitting acknowledgement..\n");
            strcpy(buffer,"ack");
            sleep(3);
        }
        printf("Sending acknowledgement.\n");
        int z=send(server,buffer,19,0);
        if(z==-1){
            printf("Error in sending..\n");
            exit(1);
        }
        k--;
        m++;
    }
    close(newSock);
}