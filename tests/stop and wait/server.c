#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){
    int server,client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(5566);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(server<0){
        printf("Error in socket creation..\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    int b=bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(b<0){
        printf("Binding error..\n");
        exit(1);
    }
    else{
        printf("Binded successfully..\n");
    }
    if(listen(server,5)==0){
        printf("listening..\n");
    }
    else{
        printf("listen error\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr*)&clientAddr,&clientAddrSize);
    if(client<0){
        printf("Accept error..\n");
        exit(1);
    }
    int n=10,m=1;
    while(n!=0){
        recv(client,buffer,1024,0);
        if(strcmp(buffer,"frame")==0){
            printf("Received frame: %d\n",m);
        }
        if(m%2==0){
            strcpy(buffer,"ack");
        }
        else{
            strcpy(buffer,"kca");
            printf("retransmission required: \n");
            for(int i=1;i<=3;i++){
                printf("retransmitting in %d seconds\n",i);
            }
            printf("retransmitting..\n");
            strcpy(buffer,"ack");
            sleep(3);
        }
        send(client,buffer,sizeof(buffer),0);
        printf("Acknowledgement sent..%d\n",m);
        n--;
        m++;
    }
    close(server);
    close(client);
    return 0;
}