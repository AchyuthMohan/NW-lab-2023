// client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main() {
    int client;
    struct sockaddr_in servAddr;
    char buffer[1024];

    client = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(6655);

    if (client < 0) {
        printf("Error\n");
        exit(1);
    }

    if (connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        printf("Error\n");
        exit(1);
    }

    while (1) {
        printf("Enter the message: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(client, buffer, sizeof(buffer), 0);
    }

    close(client);
    return 0;
}
