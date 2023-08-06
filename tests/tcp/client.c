#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int client;
    char buffer[1024];
    struct sockaddr_in servAddr;
    // socklen_t clientAddrSize=sizeof(clientAddr);
    client=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(6565);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    int x=connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(x==-1){
        printf("Error\n");
        exit(1);
    }
    else{
        printf("Connection established..\n");
    }
    while(1){
        printf("Enter the content to be send to server: \n");
        scanf("%s",buffer);
        if(strcmp(buffer,"exit")==0){
            close(client);
            exit(0);
        }
        send(client,buffer,sizeof(buffer),0);
        recv(client,buffer,1024,0);
        printf("Message from server: \n");
        printf("%s",buffer);
    }
    close(client);
    exit(0);
}
