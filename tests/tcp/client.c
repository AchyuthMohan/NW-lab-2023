#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(){
    int client;
    char buffer[1024];
    struct sockaddr_in servAddr;
    client=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(5600);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    while(1){
        connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
        printf("Enter the message content: \n");
        scanf("%s",buffer);
        if(strcmp(buffer,"exit")==0){
            printf("Bei");
            close(client);
            exit(0);
        }
        send(client,buffer,sizeof(buffer),0);
        recv(client,buffer,1024,0);
        printf("From server: \n");
        printf("%s",buffer);
    }
    
}
