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

    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET,
    servAddr.sin_port=htons(6655);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(server<=0){
        printf("socket error\n");
        exit(1);
    }
    else{
        printf("Socket created.\n");
    }
    int b=bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));
    if(b<0){
        printf("binding error\n");
        exit(1);
    }
    else{
        printf("Binded successfully..\n");
    }
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Listening error..\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    if(client<0){
        printf("accept error \n");
        exit(1);
    }
    else{
        printf("accepted..\n");
    }
    int expected_frame=0;
    int frame_count=10;
    while(expected_frame<frame_count){
        int recvd_frame;
        recv(client,&recvd_frame,sizeof(recvd_frame),0);
        if(recvd_frame==expected_frame){
            printf("received frame: %d\n",recvd_frame);
            printf("sending acknowledgement %d\n",expected_frame);
            send(client,&expected_frame,sizeof(expected_frame),0);
            expected_frame++;
        }
        else{
            printf("Discarding..frame : %d\n",expected_frame);
        }
        if(expected_frame==frame_count-1){
            break;
        }
    }
    close(server);
    close(client);
}