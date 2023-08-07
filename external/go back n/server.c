#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define WINDOW_SIZE 4
#define FRAME_COUNT 8

int main() {
    int server, client;
    struct sockaddr_in servAddr, clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    // Create socket
    server = socket(AF_INET, SOCK_DGRAM, 0);
    if (server < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(12345);

    if (bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening...\n");

    int expected_frame = 0;

    while (1) {
        int received_frame;
        recvfrom(server, &received_frame, sizeof(received_frame), 0, (struct sockaddr *)&clientAddr, &clientAddrSize);

        printf("Received frame: %d\n", received_frame);

        if (received_frame == expected_frame) {
            printf("Sending acknowledgment for frame %d\n", expected_frame);
            sendto(server, &expected_frame, sizeof(expected_frame), 0, (struct sockaddr *)&clientAddr, clientAddrSize);
            expected_frame = (expected_frame + 1) % FRAME_COUNT;
        } else {
            printf("Discarding frame %d\n", received_frame);
        }
    }

    close(server);
    return 0;
}
