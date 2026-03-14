#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 100

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[MAX];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    connect(sockfd, (struct sockaddr*)&server, sizeof(server));

    printf("Connected to server\n");

    while (1) {
        printf("Client: ");
        fgets(buffer, MAX, stdin);

        write(sockfd, buffer, MAX);

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        bzero(buffer, MAX);
        read(sockfd, buffer, MAX);

        printf("Server (Abbreviation): %s\n", buffer);
    }

    close(sockfd);
}