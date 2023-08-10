#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int main(){
    FILE *fp;
    int client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);

    client=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(8000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(client<0){
        printf("Socket error\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    char *filename="achyuth.txt";
    int x=connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(x<0){
        printf("Connection failed\n");
        exit(1);
    }
    else{
        printf("Connected.\n");
    }
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("Error in reading file..\n");
        exit(1);
    }
    char data[1024]={0};
    while(fgets(data,1024,fp)!=NULL){
        if(send(client,data,sizeof(data),0)==-1){
            printf("Error\n");
            exit(1);
        }
        bzero(data,1024);
    }
    printf("Successfully sent data file..\n");
    close(client);
    exit(0);
}