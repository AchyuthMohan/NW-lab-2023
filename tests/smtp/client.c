#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
int main(){
    int client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    client=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(2000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(client<0){
        printf("Error in socket..\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    int x=connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(x<0){
        printf("Connection error..\n");
        exit(1);
    }
    else{
        printf("Connected..\n");
    }
    recv(client,buffer,1024,0);
    printf("from server: %s\n",buffer);
    char *emailContent[]={
        "HELO localhost",
        "FROM : <someone@gmail.com>",
        "RCPT TO:<somehow@gmail.com>",
        "SUBJECT: This is test email",
        "This is how everything",
        "",
        "QUIT"
    };
    for(int i=0;i<(sizeof(emailContent)/sizeof(emailContent[0]));i++){
        send(client,emailContent[i],sizeof(emailContent[i]),0);
        recv(client,buffer,1024,0);
        printf("from server: %s\n",buffer);
    }
    close(client);
}