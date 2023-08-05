#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
int main(){
    int client,k=10,m=1;
    char buffer[1024];
    struct sockaddr_in servAddr;
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
        printf("Connection established\n");
    }
    while(k!=0){
        if(m<=10){
            printf("frame sent");
        }
        if(m%2==0){
            strcpy(buffer,"frame");
        }
        else{
            strcpy(buffer,"error");
            printf("resending frame in :\n");
            for(int i=1;i<=3;i++){
                printf("resending in %d seconds\n",i);
            }
            strcpy(buffer,"frame");
            printf("Resending\n");
            sleep(3);
        }
        int z=send(client,buffer,19,0);
        if(z==-1){
            printf("Error in sending\n");
            exit(1);
        }
        else{
            printf("sent successfully..\n");
        }
        int y=recv(client,buffer,19,0);
        if(strncmp(buffer,"frame",5)==0){
            printf("acknowledgement received..%d\n",m-1);
        }
        else{
            printf("Acknowledgement lost..\n");
        }
        k--;
        m++;
    }
    close(client);

}
