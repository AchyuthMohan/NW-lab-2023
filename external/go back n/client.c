#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define WINDOW_SIZE 4
#define PACKET_SIZE 10

char frames[WINDOW_SIZE][PACKET_SIZE];
int frame_status[WINDOW_SIZE];

void sendFrames(int sockfd, struct sockaddr_in server) {
    int base = 0;
    int next_seq_num = 0;

    while (base < WINDOW_SIZE) {
        int i;
        for (i = base; i < WINDOW_SIZE; i++) {
            if (frame_status[i] == 0) {
                char frame[PACKET_SIZE];
                sprintf(frame, "%d", next_seq_num);
                strcat(frame, frames[i]);
                write(sockfd, frame, strlen(frame));
                frame_status[i] = 1;
                next_seq_num = (next_seq_num + 1) % WINDOW_SIZE;
            }
        }

        int ack_num;
        char ack[2];
        int n = read(sockfd, ack, sizeof(ack));
        ack[n] = '\0';
        ack_num = atoi(ack);

        while (base < WINDOW_SIZE && frame_status[base] == 1) {
            if (base == ack_num) {
                frame_status[base] = 0;
                base = (base + 1) % WINDOW_SIZE;
            } else {
                break;
            }
        }
    }
}

int main() {
    struct sockaddr_in server;
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    bzero((char*)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(6500);

    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    printf("TCP Connection Established.\n");

    strcpy(frames[0], "Frame 0"); // Make sure strings fit in PACKET_SIZE
    strcpy(frames[1], "Frame 1");
    strcpy(frames[2], "Frame 2");
    strncpy(frames[3], "Frame 3 Data", PACKET_SIZE - 1); // Use strncpy to limit copying

    sendFrames(sockfd, server);

    close(sockfd);
    return 0;
}
