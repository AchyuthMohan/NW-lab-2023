#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int client;
    char buffer[1024];
    struct sockaddr_in servAddr;

    client = socket(AF_INET, SOCK_DGRAM, 0);

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6565);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        printf("Enter the content to be sent to the server (type 'exit' to quit): ");
        scanf("%s", buffer);
        if (strcmp(buffer, "exit") == 0) {
            break;
        }
        sendto(client, buffer, strlen(buffer), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
        recvfrom(client, buffer, 1024, 0, NULL, NULL);
        printf("Message from server: %s\n", buffer);
    }

    close(client);
    return 0;
}
