#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

int main(){
    int client;
    struct sockaddr_in servAddr;
    // socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    client=socket(AF_INET,SOCK_DGRAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(6565);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(client==-1){
        printf("error\n");
        exit(1);
    }
    else{
        printf("socket created suceessfully..\n");
    }
    while(1){
        printf("Enter the content to be send to server: \n");
        scanf("%s",buffer);
        if(strcmp(buffer,"exit")==0){
            break;
        }
        sendto(client,buffer,sizeof(buffer),0,(struct sockaddr *)&servAddr,sizeof(servAddr));
        recvfrom(client,buffer,1024,0,NULL,NULL);
        printf("From server: \n");
        printf("%s\n",buffer);
    }
    close(client);
    exit(0);
}