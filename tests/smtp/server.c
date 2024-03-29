#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
int main(){
    int server,client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(2000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(server<0){
        printf("Error in socket..\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Listen error..\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    char *welcomeMessage="Welcome to SMTP server\r\n";
    send(client,welcomeMessage,strlen(welcomeMessage),0);
    while(1){
        recv(client,buffer,1024,0);
        printf("From client: %s\n",buffer);
        if(strstr(buffer,"QUIT")!=NULL){
            char *response="Good bye\r\n";
            send(client,response,sizeof(response),0);
            break;
        }
        else{
            char *response="220 OK\r\n";
            send(client,*response,sizeof(response),0);
        }
    }
    close(server);
    close(client);
    return 0;
}