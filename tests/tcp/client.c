#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(){
    int client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    client=socket(AF_INET,SOCK_STREAM,0);
    if(client<0){
        printf("Error in socket creating..\n");
        exit(1);
    }
    else{
        printf("Socket created successfully..\n");
    }
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(3333);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    int y=connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(y<0){
        printf("Error in connecting..\n");
        exit(1);
    }
    while(1){
        printf("Enter the message content: \n");
        scanf("%s",buffer);
        if(strcmp(buffer,"exit")==0){
            break;
        }
        send(client,buffer,sizeof(buffer),0);
        recv(client,buffer,1024,0);
        printf("From server: %s\n",buffer);
    }
    close(client);
    exit(0);
}