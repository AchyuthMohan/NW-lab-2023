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
    int frame_count = 8;
    client = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(1234);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (client < 0)
    {
        printf("Error in socket..\n");
        exit(1);
    }
    else
    {
        printf("Socket created successfully..\n");
    }
    int c = connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (c < 0)
    {
        printf("Connect request error..\n");
        exit(1);
    }
    else
    {
        printf("Connection success..\n");
    }
    int send_frame = 0;
    int windw_size = 4;
    int nextframe_to_send = 0;
    int ack_frame = 0;
    while (send_frame < frame_count)
    {
        while (nextframe_to_send < frame_count && nextframe_to_send < send_frame + windw_size)
        {
            printf("Sending frame: %d\n", nextframe_to_send);
            send(client, &nextframe_to_send, sizeof(nextframe_to_send), 0);
            nextframe_to_send++;
        }

        while (ack_frame <= send_frame)
        {
            int recved_ack;
            recv(client, &recved_ack, sizeof(recved_ack), 0);
            printf("Acknowledgement: %d\n", recved_ack);
            ack_frame = (recved_ack + 1) % frame_count;
        }
        send_frame = ack_frame;
        if (send_frame == frame_count - 1)
        {
            break;
        }
    }
    close(client);
    exit(0);
}
