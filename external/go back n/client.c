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
    struct sockaddr_in servAddr, clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    client = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(1345);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (client < 0)
    {
        printf("socket error..\n");
        exit(1);
    }

    int c = connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (c < 0)
    {
        printf("Connection error..\n");
        exit(1);
    }
    int window_size = 4;
    int frame_count = 8;
    int send_frame = 0;
    int next_frame_to_send = 0;
    int ack_frame = 0;
    while (send_frame < frame_count)
    {
        while (next_frame_to_send < window_size + send_frame && next_frame_to_send < frame_count)
        {
            printf("Sending frame: %d\n", next_frame_to_send);
            send(client, &next_frame_to_send, sizeof(next_frame_to_send), 0);
            next_frame_to_send++;
        }
        while (ack_frame <= send_frame)
        {
            int recvd_ack;
            recv(client, &recvd_ack, sizeof(recvd_ack), 0);
            printf("Acknowledgement: %d\n", recvd_ack);
            ack_frame = (recvd_ack + 1) % frame_count;
        }
        send_frame = ack_frame;
        if (send_frame == frame_count - 1)
        {
            break;
        }
    }
    close(client);
}