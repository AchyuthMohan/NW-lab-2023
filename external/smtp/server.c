#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 6655
#define BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(serverSocket, 1) < 0) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    // Accept client connection
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket < 0) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    // Send welcome message
    char *welcomeMessage = "220 Welcome to SMTP server\r\n";
    send(clientSocket, welcomeMessage, strlen(welcomeMessage), 0);

    // Receive and process commands
    while (1) {
        recv(clientSocket, buffer, BUFFER_SIZE, 0);
        printf("Client: %s", buffer);

        // Process commands (simplified example)
        if (strstr(buffer, "QUIT") != NULL) {
            char *response = "221 Goodbye\r\n";
            send(clientSocket, response, strlen(response), 0);
            break;
        } else {
            char *response = "250 OK\r\n";
            send(clientSocket, response, strlen(response), 0);
        }

        memset(buffer, 0, BUFFER_SIZE);
    }

    // Close sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
