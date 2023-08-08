#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int main(){
    int server,client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    int k=10,m=1;
    char buffer[1024];
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(6655);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(server<0){
        printf("Error in socket creating..\n");
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
        printf("Listening error\n");
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
    while(k!=0){
        recv(client,buffer,1024,0);
        if(strcmp(buffer,"frame")==0){
            printf("Received frame: %d\n",m);
        }
        if(m%2==0){
            strcpy(buffer,"ack");
        }
        else{
            strcpy(buffer,"kca");
            printf("Retransmitting: \n");
            for(int i=1;i<=3;i++){
                printf("Retransmitting in %d seconds\n",i);
            }
            printf("retransmitting..\n");
            strcpy(buffer,"ack");
            sleep(3);
        }
        printf("Sending acknowledgement: \n");
        send(client,buffer,sizeof(buffer),0);

        k--;
        m++;
    }
    close(client);
    close(server);
}