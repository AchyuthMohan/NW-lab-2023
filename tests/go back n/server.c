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
    int frame_count=8;
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(1234);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(server<0){
        printf("Error in socket..\n");
        exit(1);
    }
    else{
        printf("Socket created successfully..\n");
    }
    int b=bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
    if(b<0){
        printf("Error in binding..\n");
        exit(1);
    }
    else{
        printf("Binding done..\n");
    }
    if(listen(server,5)==0){
        printf("Listening..\n");
    }
    else{
        printf("Error in listening..\n");
        exit(1);
    }
    client=accept(server,(struct sockaddr *)&clientAddr,&clientAddrSize);
    if(client<0){
        printf("Error in accept..\n");
        exit(1);
    }
    else{
        printf("Connected succesfully..\n");
    }
    int expected_frame=0;
    while(expected_frame<frame_count){
        int received_frame;
        recv(client,&received_frame,sizeof(received_frame),0);
        if(received_frame==expected_frame){
            printf("Frame received: %d\n",received_frame);
            printf("Sending acknowledgement for %d\n",expected_frame);
            send(client,&expected_frame,sizeof(expected_frame),0);
            expected_frame=(expected_frame+1)%frame_count;
        }
        else{
            printf("Discarding..%d\n",received_frame);
        }
        if(received_frame==frame_count-1){
            break;
        }
    }
    close(client);
    close(server);
}