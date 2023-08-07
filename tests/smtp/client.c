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
    servAddr.sin_port=htons(6000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(client<0){
        printf("Error in socket.\n");
        exit(1);
    }
    else{
        printf("Socket created successfully..\n");
    }
    int c=connect(client,(struct sockaddr*)&servAddr,sizeof(servAddr));
    if(c<0){
        printf("Connection error..\n");
        exit(1);
    }
    recv(client,buffer,1024,0);
    printf("From server: %s\n",buffer);
    char *emailCommands[]={
        "HELO localhost\r\n",
        "MAIL FROM: <someone@example.com>\r\n",
        "RCPT TO: <somehow@example.com>\r\n",
        "SUBJECT: Test email\r\n",
        "This is email body\r\n",
        "\r\n",
        "QUIT\r\n"
    };
    int n=sizeof(emailCommands)/sizeof(emailCommands[0]);
    for(int i=0;i<n;i++){
        send(client,emailCommands[i],strlen(emailCommands[i]),0);
        recv(client,buffer,1024,0);
        puts(buffer);
    }
    close(client);
}