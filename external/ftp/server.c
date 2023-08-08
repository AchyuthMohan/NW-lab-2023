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
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(6655);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(server<0){
        printf("socket error..\n");
        exit(1);
    }
    else{
        printf("Socket created successfully..\n");
    }
    int b=bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(b<0){
        printf("Binding error..\n");
        exit(1);
    }
    else{
        printf("Binded successfully.\n");
    }
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Listening error..\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    if(client<0){
        printf("Accept error..\n");
        exit(1);
    }
    else{
        printf("Acepted..\n");
    }
    FILE *fp=fopen("result.txt","w");
    while(1){
        int r=recv(client,buffer,1024,0);
        fprintf(fp,"%s",buffer);
        if(r<=0){
            break;
        }
        bzero(buffer,1024);
    }
    close(server);
    close(client);
}