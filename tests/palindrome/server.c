#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int isPalindrom(char buffer[]){
    int start=0;
    int end=strlen(buffer)-1;
    while(start<end){
        if(buffer[start]!=buffer[end]){
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}
int main(){
    int server,client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servAddr.sin_port=htons(6656);
    if(server<0){
        printf("Error\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Error in listening..\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    if(client<0){
        printf("Error in accept..\n");
        exit(1);
    }
    else{
        printf("Accepted..\n");
    }
    recv(client,buffer,1024,0);
    int x=isPalindrom(buffer);
    if(x==0){
        strcpy(buffer,"No");
    }
    else{
        strcpy(buffer,"Yes");
    }
    send(client,buffer,sizeof(buffer),0);
    close(server);
    close(client);
    return 0;
}