#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6655
#define BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
        perror("Invalid server address");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    // Read server response
    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    printf("Server: %s", buffer);

    // Send email commands
    char *emailCommands[] = {
        "HELO localhost\r\n",
        "MAIL FROM: <sender@example.com>\r\n",
        "RCPT TO: <receiver@example.com>\r\n",
        "DATA\r\n",
        "Subject: Test Email\r\n",
        "This is a test email sent using SMTP client in C.\r\n",
        ".\r\n",
        "QUIT\r\n"
    };

    for (int i = 0; i < sizeof(emailCommands) / sizeof(emailCommands[0]); i++) {
        send(clientSocket, emailCommands[i], strlen(emailCommands[i]), 0);
        recv(clientSocket, buffer, BUFFER_SIZE, 0);
        printf("Server: %s", buffer);
    }

    // Close the socket
    close(clientSocket);

    return 0;
}
