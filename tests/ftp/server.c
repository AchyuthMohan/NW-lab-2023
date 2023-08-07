#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int main(){
    FILE *fp;
    int server,client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(8000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(server<0){
        printf("Error in socket\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    int x=bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(x<0){
        printf("binding not done\n");
        exit(1);
    }
    else{
        printf("Binding success..\n");
    }
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Error\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    char *filename="result.txt";
    fp=fopen(filename,"w");
    if(fp==NULL){
        printf("Error in creating file..\n");
        exit(1);
    }
    while(1){
        int n=recv(client,buffer,1024,0);
        if(n<=0){
            break;
        }
        fprintf(fp,"%s",buffer);
        if(strcmp(buffer,"end")==0){
            break;
        }
        bzero(buffer,1024);
    }
    close(client);
    close(server);
}