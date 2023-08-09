#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
int main()
{
    int client;
    struct sockaddr_in servAddr, clientAddr ;
    socklen_t clientAddrSize = sizeof(clientAddr);

    client = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET,
    servAddr.sin_port = htons(6655);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (client <= 0)
    {
        printf("socket error\n");
        exit(1);
    }
    else
    {
        printf("Socket created.\n");
    }
    int c = connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (c < 0)
    {
        printf("Connection error\n");
        exit(1);
    }
    else
    {
        printf("Connected..\n");
    }
    int window_size = 4;
    int frame_count = 10;
    int send_frame = 0;
    int ack_frame = 0;
    int next_frame_to_send = 0;
    while (send_frame < frame_count)
    {
        while (next_frame_to_send < frame_count && next_frame_to_send < window_size + send_frame)
        {
            printf("sending the next frame %d\n", next_frame_to_send);
            send(client, &next_frame_to_send, sizeof(next_frame_to_send), 0);
            next_frame_to_send ++ ;
        }
        while (ack_frame <= send_frame)
        {
            int recvd_frame;
            recv(client, &recvd_frame, sizeof(recvd_frame), 0);
            printf("Acknowledgement: %d\n", recvd_frame);
            ack_frame = (recvd_frame + 1) % frame_count;
        }
        send_frame=ack_frame;
        if(send_frame==frame_count-1){
            break;
        }
    }
    close(client);
}