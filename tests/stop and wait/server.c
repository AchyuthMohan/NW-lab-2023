#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
    int server, k = 10, m = 1,newSock;
    char buffer[1024];
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);

    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(5600);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Error in listening ..\n");
    }
    newSock=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    if(newSock==-1){
        printf("Error\n");
    }
    while(k!=0){
        int y=recv(newSock,buffer,1024,0);
        if(y==-1){
            printf("Error in receiving\n");
            exit(1);
        }
        if(strncmp(buffer,"frame",5)==0){
            printf("received frame %d\n",m);
        }
        else{
            printf("frame %d did not receive\n",m);
        }
        if(m%2==0){
            strcpy(buffer,"ack");
        }
        else{
            strcpy(buffer,"kca");
            printf("Retransmitting in : \n");
            for(int i=1;i<=3;i++){
                printf("Waiting for %d seconds\n",i);
            }
            printf("Retransmitting ack\n");
            strcpy(buffer,"ack");
            sleep(3);
        }
        printf("Sending acknowledgement..\n");
        int z=send(newSock,buffer,19,0);
        if(z==-1){
            printf("Error in sending axknowledgement..\n");
            exit(1);
        }
        k--;
        m++;
    }
    close(newSock);
}