#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define FRAME_COUNT 8

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0)
    {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening...\n");
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    while (1)
    {
        // Accept client connection

        if (client_fd < 0)
        {
            perror("Accepting connection failed");
            continue;
        }

        printf("Client connected\n");

        int expected_frame = 0;

        while (expected_frame < FRAME_COUNT)
        {
            int received_frame;
            recv(client_fd, &received_frame, sizeof(received_frame), 0);

            printf("Received frame: %d\n", received_frame);

            if (received_frame == expected_frame)
            {
                printf("Sending acknowledgment for frame %d\n", expected_frame);
                send(client_fd, &expected_frame, sizeof(expected_frame), 0);
                expected_frame = (expected_frame + 1) % FRAME_COUNT;
            }
            else
            {
                printf("Discarding frame %d\n", received_frame);
            }
        }
    }
    close(client_fd);
    close(server_fd);
    return 0;
}
