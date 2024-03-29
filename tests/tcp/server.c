#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main(){
    int server,client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servAddr.sin_port=htons(6655);
    if(server<0){
        printf("Error\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Error in listening..\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    if(client<0){
        printf("Error in accept..\n");
        exit(1);
    }
    else{
        printf("Accepted..\n");
    }
    while(1){
        recv(client,buffer,1024,0);
        printf("from client: %s\n",buffer);
        printf("Enter the message content: \n");
        scanf("%s",buffer);
        send(client,buffer,sizeof(buffer),0);
        if(strcmp(buffer,"exit")==0){
            break;
        }
    }
    close(server);
    close(client);
    return 0;
}