#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<string.h>
#include<unistd.h>

int main(){
    int client, k = 10, m = 1;
    char buffer[1024];
    struct sockaddr_in servAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);

    client=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(5600);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    int x=connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(x==-1){
        printf("Error in connection..\n");
        exit(1);
    }
    else{
        printf("Connection established..\n");
    }
    while(k!=0){
        if(m<=10){
            printf("Sending..%d\n",m);
        }
        if(m%2==0){
            strcpy(buffer,"frame");
        }
        else{
            strcpy(buffer,"error");
            printf("Sending in :\n");
            for(int i=1;i<=3;i++){
                printf("resending in %d\n",i);
            }
            strcpy(buffer,"frame");
            printf("Resending..\n");
            sleep(3);
        }
        int z=send(client,buffer,19,0);
        if(z==-1){
            printf("Error in sending..\n");
            exit(1);
        }
        else{
            printf("sent %d successfully\n",m-1);
        }
        k--;
        m++;
        int y=recv(client,buffer,19,0);
        if(y==-1){
            printf("Ack lost\n");
        }
        else{
            printf("Acknowledged..\n");
        }
    }
    close(client);

}