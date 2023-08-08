#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int main(){
    int client;
    int k=10,m=1;
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[1024];
    client=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(5566);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(client<0){
        printf("Error in socket..\n");
        exit(1);
    }
    else{
        printf("Socket created.\n");
    }
    int c=connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(c<0){
        printf("Error in connection..\n");
        exit(1);
    }
    else{
        printf("connection established..\n");
    }
    while(k!=0){
        if(m<10){
            printf("Sending frame: %d\n",m);
        }
        if(m%2==0){
            strcpy(buffer,"frame");
        }
        else{
            strcpy(buffer,"error");
            printf("retransmission required\n");
            for(int i=1;i<=3;i++){
                printf("retransmitting in %d seconds\n",i);
            }
            strcpy(buffer,"frame");
            printf("retransmitting..\n");
            sleep(3);
        }
        send(client,buffer,sizeof(buffer),0);
        printf("Sent %d\n",m);
        recv(client,buffer,1024,0);
        if(strcmp(buffer,"ack")==0){
            printf("Ack received %d\n",m);
        }
        else{
            printf("Error in ack\n");
        }
        k--;
        m++;
    }
    close(client);
}