#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int server,client;
    char buffer[1024];
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(6565);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(server==-1){
        printf("Socket error..\n");
        exit(1);
    }
    else{
        printf("Socket created successfully..");
    }
    bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(listen(server,5)==0){
        printf("listening...\n");
    }
    else{
        printf("listening error..\n");
        exit(1);
    }
    
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    while(1){
        recv(client,buffer,1024,0);
        printf("From client: \n");
        printf("%s",buffer);
        printf("Enter the content to send to client: \n");
        scanf("%s",buffer);
        if(strcmp(buffer,"exit")==0){
            printf("bye..\n");
            close(client);
            close(server);
            exit(0);
        }
        send(client,buffer,sizeof(buffer),0);
    }
    close(server);
    close(client);
}