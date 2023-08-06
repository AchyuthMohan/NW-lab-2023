#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

int main(){
    int server;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    server=socket(AF_INET,SOCK_DGRAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(6565);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(server==-1){
        printf("Socket error..\n");
        exit(1);
    }
    else{
        printf("Socket created successfully..\n");
    }
    int x=bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(x==-1){
        printf("error binding..\n");
        exit(1);
    }
    else{
        printf("Binded successfully..\n");
    }
    while(1){
        recvfrom(server,buffer,1024,0,(struct sockaddr *)&clientAddr,&clientAddrSize);
        printf("Message from client: %s\n",buffer);
        printf("Enter the content to be send to client: \n");
        scanf("%s",buffer);
        if(strcmp(buffer,"exit")==0){
            break;
        }
        sendto(server,buffer,sizeof(buffer),0,(struct sockaddr *)&clientAddr,clientAddrSize);
    }
    close(server);
    exit(0);
}