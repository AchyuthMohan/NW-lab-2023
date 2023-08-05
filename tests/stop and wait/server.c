#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int server,k=10,m=1,newSock;
    char buffer[1024];
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);

    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(5600);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Error \n");
        exit(1);
    }
    newSock=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    if(newSock==-1){
        printf("Error in accepting connection\n");
        exit(1);
    }
    while(k!=0){
        int y=recv(newSock,buffer,1024,0);
        if(y==-1){
            printf("Error in receiving \n");
            exit(1);
        }
        if(strncmp(buffer,"frame",5)==0){
            printf("Received frame %d successfully\n",m);
        }
        if(m%2==0){
            strcpy(buffer,"ack");
        }
        else{
            printf("ack not found\n");
            strcpy(buffer,"kca");
            printf("Retransmitting ack in: \n");
            for(int i=1;i<=3;i++){
                printf("Retransmitting in %d seconds\n",i);
            }
            strcpy(buffer,"ack");
            printf("retransmiting\n");
            sleep(3);
        }
        int z=send(newSock,buffer,19,0);
        if(z==-1){
            printf("Error in sending \n");
            exit(1);
        }
        else{
            printf("Sent successfully..\n");
        }
        m++;
        k--;
    }
}