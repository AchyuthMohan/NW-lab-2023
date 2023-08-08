#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
int main()
{
    FILE *fp;
    int client;
    struct sockaddr_in servAddr, clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    char buffer[1024];
    client = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6655);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (client < 0)
    {
        printf("socket error..\n");
        exit(1);
    }
    else
    {
        printf("Socket created successfully..\n");
    }
    char fname[50];
    int c=connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(c<0){
        printf("Connection errror");
        exit(1);
    }
    else{
        printf("Connected..\n");

    }
    printf("Enter the file name: \n");
    scanf("%s",fname);
    fp=fopen(fname,"r");
    if(fp==NULL){
        printf("File error \n");
        exit(1);
    }
    while(fscanf(fp,"%s",buffer)!=EOF){
        send(client,buffer,sizeof(buffer),0);
        bzero(buffer,1024);
    }
    close(client);
}
