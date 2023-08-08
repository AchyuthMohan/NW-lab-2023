#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 3000
#define WINDOW_SIZE 4
#define FRAME_COUNT 8

int main() {
    int client_fd;
    struct sockaddr_in server_addr;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    int send_frame = 0;
    int next_frame_to_send = 0;
    int ack_frame = 0;

    while (send_frame < FRAME_COUNT) {
        while (next_frame_to_send < send_frame + WINDOW_SIZE && next_frame_to_send < FRAME_COUNT) {
            printf("Sending frame: %d\n", next_frame_to_send);
            send(client_fd, &next_frame_to_send, sizeof(next_frame_to_send), 0);
            next_frame_to_send++;
        }

        while (ack_frame <= send_frame) {
            int received_ack;
            ssize_t bytes_received = recv(client_fd, &received_ack, sizeof(received_ack), 0);

            if (bytes_received <= 0) {
                perror("Receiving acknowledgment failed");
                close(client_fd);
                exit(1);
            }

            printf("Received acknowledgment for frame: %d\n", received_ack);
            ack_frame = (received_ack + 1) % FRAME_COUNT;
        }

        send_frame = ack_frame;
    }

    close(client_fd);
    return 0;
}
