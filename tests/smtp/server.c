#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int main(){
    int server,client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(7000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(server<0){
        printf("Error in socket..\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    int x=bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(x<0){
        printf("Error in binding..\n");
        exit(1);
    }
    else{
        printf("Binding done\n");
    }
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Error\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr*)&clientAddr,&clientAddrSize);
    if(client<0){
        printf("Error in accept..\n");
    }
    strcpy(buffer,"220 Welcome to SMTP server\r\n");
    send(client,buffer,sizeof(buffer),0);
    while(1){
        recv(client,buffer,1024,0);
        printf("From client: %s\n",buffer);
        if(strstr(buffer,"QUIT")!=NULL){
            strcpy(buffer,"221 Good bye\r\n");
            send(client,buffer,sizeof(buffer),0);
            break;
        }
        else{
            char *response="220 OK\r\n";
            send(client,response,strlen(response),0);
        }
    }
    close(server);
    close(client);
    exit(0);
}