#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAX_CLIENTS 10

int main() {
    int server, clients[MAX_CLIENTS], client, max_fd, bytes_received;
    struct sockaddr_in servAddr, clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    fd_set read_fds;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i] = -1;
    }

    server = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(6655);

    bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr));
    listen(server, MAX_CLIENTS);

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(server, &read_fds);
        max_fd = server;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] != -1) {
                FD_SET(clients[i], &read_fds);
                max_fd = (clients[i] > max_fd) ? clients[i] : max_fd;
            }
        }

        select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (FD_ISSET(server, &read_fds)) {
            client = accept(server, (struct sockaddr *)&clientAddr, &clientAddrSize);

            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i] == -1) {
                    clients[i] = client;
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] != -1 && FD_ISSET(clients[i], &read_fds)) {
                char buffer[1024];
                bytes_received = recv(clients[i], buffer, sizeof(buffer), 0);
                if (bytes_received <= 0) {
                    close(clients[i]);
                    clients[i] = -1;
                } else {
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
