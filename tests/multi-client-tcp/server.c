#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(){
    int server,client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    server=socket(AF_INET,SOCK_STREAM,0);
    if(server<0){
        printf("Error in socket creating..\n");
        exit(1);
    }
    else{
        printf("Socket created successfully..\n");
    }
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(3333);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Listening error..\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    if(client<0){
        printf("Accept error\n");
        exit(1);
    }
    while(1){
        recv(client,buffer,1024,0);
        printf("Client: %s\n",buffer);
        printf("Enter the contents to be send to client: \n");
        scanf("%s",buffer);
        if(strcmp(buffer,"exit")==0){
            break;
        }
        send(client,buffer,sizeof(buffer),0);
    }
    close(server);
    close(client);
    exit(0);
}