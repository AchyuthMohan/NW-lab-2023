#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 3000
#define BUFFER_SIZE 1024

int main() {
    int server, client;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    // Create socket
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set server address
    // memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server, 1) < 0) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    // Accept client connection
    client = accept(server, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (client < 0) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    // Send welcome message
    char *welcomeMessage = "220 Welcome to SMTP server\r\n";
    send(client, welcomeMessage, strlen(welcomeMessage), 0);

    // Receive and process commands
    while (1) {
        recv(client, buffer, BUFFER_SIZE, 0);
        printf("Client: %s", buffer);

        // Process commands (simplified example)
        if (strstr(buffer, "QUIT") != NULL) {
            char *response = "221 Goodbye\r\n";
            send(client, response, strlen(response), 0);
            break;
        } else {
            char *response = "250 OK\r\n";
            send(client, response, strlen(response), 0);
        }

        memset(buffer, 0, BUFFER_SIZE);
    }

    // Close sockets
    close(client);
    close(server);

    return 0;
}
