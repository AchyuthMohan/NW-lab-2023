#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main(){
    int client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    client=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servAddr.sin_port=htons(6656);
    if(client<0){
        printf("Error\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    int c=connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(c<0){
        printf("error\n");
        exit(1);
    }
    else{
        printf("Connected..\n");
    }
    printf("Enter the string: \n");
    scanf("%s",buffer);
    send(client,buffer,sizeof(buffer),0);
    recv(client,buffer,1024,0);
    printf("From server: %s\n",buffer);
    close(client);
}