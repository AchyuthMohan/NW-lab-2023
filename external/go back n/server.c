#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define WINDOW_SIZE 4
#define PACKET_SIZE 10

void processFrame(char frame[]) {
    printf("Received Frame: %s\n", frame);
}

int main() {
    struct sockaddr_in server, client;
    int sockfd, newsockfd, n;
    socklen_t clilen;
    char buffer[PACKET_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    bzero((char*)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(6500);

    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Binding failed");
        exit(1);
    }

    listen(sockfd, 1);
    clilen = sizeof(client);
    newsockfd = accept(sockfd, (struct sockaddr*)&client, &clilen);
    if (newsockfd < 0) {
        perror("Error on accept");
        exit(1);
    }

    printf("TCP Connection Established.\n");

    int expected_seq = 0;

    while (1) {
        n = read(newsockfd, buffer, PACKET_SIZE);
        buffer[n] = '\0';

        int received_seq = atoi(buffer);

        if (received_seq == expected_seq) {
            processFrame(buffer);
            expected_seq = (expected_seq + 1) % WINDOW_SIZE;
        }

        // Acknowledge the received frame (sequence number) back to the client
        char ack[2];
        sprintf(ack, "%d", expected_seq);
        write(newsockfd, ack, strlen(ack));
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
