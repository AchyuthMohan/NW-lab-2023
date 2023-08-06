#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(){
    int server,client;
    char buffer[1024];
    struct sockaddr_in servAddr, clientAddr;
    server=socket(AF_INET,SOCK_STREAM,0);
    socklen_t clientAddrSize=sizeof(clientAddr);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(5600);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(listen(server,5)==0){
        printf("Listenig \n");
    }
    else{
        printf("Error\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    while(1){
        
        int x=recv(client,buffer,1024,0);
        printf("Message from client: \n");
        printf("%s",buffer);
        printf("Enter the content to be send to client: \n");
        scanf("%s",buffer);
        if(strcmp(buffer,"exit")==0){
            close(server);
            close(client);
            exit(0);
        }
        send(client,buffer,sizeof(buffer),0);
    }
    close(client);
    close(server);

}