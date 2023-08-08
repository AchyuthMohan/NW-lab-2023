#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){
    int client;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    client=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(5566);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(client<0){
        printf("Error in socket creation..\n");
        exit(1);
    }
    else{
        printf("Socket created..\n");
    }
    int c=connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(c<0){
        printf("Connection error..\n");
        exit(1);
    }
    else{
        printf("Connected..\n");
    }
    int k=10,m=1;
    while(k!=0){
        if(m<=10){
            printf("sending frame: %d\n",m);
        }
        if(m%2==0){
            strcpy(buffer,"frame");
        }
        else{
            strcpy(buffer,"error");
            printf("Retransmission required..\n");
            for(int i=1;i<=3;i++){
                printf("waiting for %d seconds\n",i);
            }
            printf("retransmiting.\n");
            strcpy(buffer,"frame");
            sleep(3);
        }
        send(client,buffer,sizeof(buffer),0);
        recv(client,buffer,1024,0);
        if(strcmp(buffer,"ack")==0){
            printf("Acknowledgement: %d\n",m);
        }
        else{
            printf("Error in acknowledgement\n");
        }
        k--;
        m++;
    }
    close(client);
}