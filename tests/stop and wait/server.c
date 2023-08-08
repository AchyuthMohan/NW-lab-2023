#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int main(){
    int server,client;
    int k=10,m=1;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(5566);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(server<0){
        printf("Error in socket..\n");
        exit(1);
    }
    else{
        printf("Socket created.\n");
    }
    bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Error in listening..\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    if(client<0){
        printf("Accept error..\n");
        exit(1);
    }
    else{
        printf("Accepted..\n");
    }
    while(k!=0){
        recv(client,buffer,1024,0);
        if(strcmp(buffer,"frame")==0){
            printf("Received frame: %d",m);
        }
        else{
            printf("Error in frame..\n");
            exit(1);
        }
        if(m%2==0){
            strcpy(buffer,"ack");
        }
        else{
            strcpy(buffer,"kca");
            printf("Retransmitting..\n");
            for(int i=1;i<=3;i++){
                printf("Waiting for %dseconds\n",i);
            }
            strcpy(buffer,"ack");
            printf("retransmitting..\n");
            sleep(3);
        }
        send(client,buffer,sizeof(buffer),0);
        printf("Sent ack..\n");
        k--;
        m++;
    }
    close(client);
    close(server);
    return 0;
}

