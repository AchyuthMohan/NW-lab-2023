#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server;
    char buffer[1024];
    struct sockaddr_in servAddr, clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    server = socket(AF_INET, SOCK_DGRAM, 0);

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6565);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    if (server == -1) {
        printf("Socket error..\n");
        exit(1);
    } else {
        printf("Socket created successfully..\n");
    }
    int x=bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr));

    if (x == -1) {
        printf("Binding error..\n");
        exit(1);
    } else {
        printf("Binding successful..\n");
    }

    while (1) {
        recvfrom(server, buffer, 1024, 0, (struct sockaddr*)&clientAddr, &clientAddrSize);
        printf("From client: %s\n", buffer);
        printf("Enter the content to send to client: ");
        scanf("%s", buffer);
        if (strcmp(buffer, "exit") == 0) {
            printf("bye..\n");
            break;
        }
        sendto(server, buffer, strlen(buffer), 0, (struct sockaddr*)&clientAddr, clientAddrSize);
    }

    close(server);
    return 0;
}
