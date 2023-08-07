#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 7000
#define BUFFER_SIZE 1024

int main() {
    int client;
    struct sockaddr_in serverAddr,clientAddr;
    socklen_t clientAddrSize=sizeof(clientAddr);
    char buffer[BUFFER_SIZE];
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    int y=connect(client,(struct sockaddr *)&serverAddr,clientAddrSize);
    if (y< 0) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    recv(client, buffer, BUFFER_SIZE, 0);
    printf("Server: %s", buffer);
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
        send(client, emailCommands[i], strlen(emailCommands[i]), 0);
        recv(client, buffer, BUFFER_SIZE, 0);
        printf("Server: %s", buffer);
    }
    close(client);

    return 0;
}
