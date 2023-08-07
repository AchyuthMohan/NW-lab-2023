#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(){
    int server,client;
    struct sockaddr_in servAddr,clientAddr;
    char buffer[1024];
    socklen_t clientAddrSize=sizeof(clientAddr);
    server=socket(AF_INET,SOCK_STREAM,0);
    if(server<0){
        printf("Socket error..\n");
        exit(1);
    }
    else{
        printf("Socket created successfully..\n");
    }
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(3000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    int x=bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(x==-1){
        printf("binding error..\n");
        exit(1);
    }
    else{
        printf("Socket binded successfully..\n");
    }
    if(listen(server,5)==0){
        printf("Listenimg..\n");
    }
    else{
        printf("Listen error..\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    if(client==-1){
        printf("Error..\n");
        exit(1);
    }
    char *welcomeMessage = "220 Welcome to SMTP server\r\n";
    send(client, welcomeMessage, strlen(welcomeMessage), 0);
    while(1){
        recv(client,buffer,1024,0);
        printf("From client: %s\n",buffer);
        if (strcmp(buffer, "QUIT") == 0) {
            char *response = "221 Goodbye\r\n";
            send(client, response, strlen(response), 0);
            break;
        }
        else{
            char *response = "250 OK\r\n";
            send(client, response, strlen(response), 0);
        }
    }
    close(server);
    close(client);
}