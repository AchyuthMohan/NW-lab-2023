// server.c (Multi-Client Chat Server)
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAX_CLIENTS 10

int main() {
    int server, client;
    struct sockaddr_in servAddr, clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clients[MAX_CLIENTS];
    fd_set read_fds;
    int max_fd;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i] = -1; // Initialize client socket descriptors
    }

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        printf("Error in socket creation..\n");
        exit(1);
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(6655);

    if (bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        printf("Error in binding..\n");
        exit(1);
    }

    if (listen(server, MAX_CLIENTS) == 0) {
        printf("Listening..\n");
    } else {
        printf("Listening error..\n");
        exit(1);
    }

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(server, &read_fds);
        max_fd = server;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] != -1) {
                FD_SET(clients[i], &read_fds);
                if (clients[i] > max_fd) {
                    max_fd = clients[i];
                }
            }
        }

        select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (FD_ISSET(server, &read_fds)) {
            client = accept(server, (struct sockaddr *)&clientAddr, &clientAddrSize);
            if (client < 0) {
                printf("Accept error\n");
                exit(1);
            }

            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i] == -1) {
                    clients[i] = client;
                    printf("Client %d connected.\n", client);
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] != -1 && FD_ISSET(clients[i], &read_fds)) {
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));

                int bytes_received = recv(clients[i], buffer, sizeof(buffer), 0);
                if (bytes_received <= 0) {
                    printf("Client %d disconnected.\n", clients[i]);
                    close(clients[i]);
                    clients[i] = -1;
                } else {
                    printf("From client %d: %s\n", clients[i], buffer);
                    // Broadcast the message to other clients
                    for (int j = 0; j < MAX_CLIENTS; j++) {
                        if (clients[j] != -1 && clients[j] != clients[i]) {
                            send(clients[j], buffer, bytes_received, 0);
                        }
                    }
                }
            }
        }
    }

    close(server);
    return 0;
}
