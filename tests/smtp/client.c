#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int main(){
    int client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    client=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(7000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(client<0){
        printf("Error..\n");
        exit(1);
    }
    else{
        printf("socket created..\n");
    }
    int z=connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(z<0){
        printf("Error..\n");
        exit(1);
    }
    else{
        printf("Connnection accepted\n");
    }
    recv(client,buffer,1024,0);
    printf("From server: %s\n",buffer);
    char *emailCommands[]={
        "HELO localhost\r\n",
        "MAIL FROM: <someone@gmail.com>\r\n",
        "RCPT TO: <somehow@gmail.com>\r\n",
        "DATA\r\n",
        "SUBJECT: Test mail\r\n",
        "This is a test email\r\n",
        "\r\n",
        "QUIT\r\n"
};
    for(int i=0;i<sizeof(emailCommands)/sizeof(emailCommands[0]);i++){
        send(client,emailCommands[i],strlen(emailCommands[i]),0);
        recv(client,buffer,1024,0);
        printf("From server: %s\n",buffer);
    }
    close(client);
}
