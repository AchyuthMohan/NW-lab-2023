#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int main(){
    int server;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    server=socket(AF_INET,SOCK_DGRAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(3000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(server<0){
        printf("Error.\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    // if(listen(server,5)==0){
    //     printf("Listening...\n");
    // }
    // else{
    //     printf("Listen error..\n");
    //     exit(1);
    // }
    while(1){
        recvfrom(server,buffer,1024,0,(struct sockaddr *)&clientAddr,&clientAddrSize);
        printf("From client: %s\n",buffer);
        printf("Enter the mesage: \n");
        scanf("%s",buffer);
        sendto(server,buffer,sizeof(buffer),0,(struct sockaddr *)&clientAddr,clientAddrSize);
    }
    close(server);
}