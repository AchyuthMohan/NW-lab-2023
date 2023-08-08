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
    client=socket(AF_INET,SOCK_DGRAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(3000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(client<0){
        printf("Error.\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    while(1){
        printf("Enter the message: \n");
        scanf("%s",buffer);
        sendto(client,buffer,sizeof(buffer),0,(struct sockaddr *)&servAddr,sizeof(servAddr));
        recvfrom(client,buffer,1024,0,(struct sockaddr *)&clientAddr,&clientAddrSize);
        printf("From server: %s\n",buffer);
    }
    close(client);
}