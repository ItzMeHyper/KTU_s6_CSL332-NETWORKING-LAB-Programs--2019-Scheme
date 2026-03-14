#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 8080
#define MAX 100

int main() {
    int sockfd, connfd;
    struct sockaddr_in server;
    char buffer[MAX], result[MAX];
    int i, j;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd, 1);

    printf("Server waiting...\n");

    connfd = accept(sockfd, NULL, NULL);
    printf("Client connected\n");

    while (1) {
        bzero(buffer, MAX);
        read(connfd, buffer, MAX);

        printf("Client: %s", buffer);

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        bzero(result, MAX);
        j = 0;

        if (buffer[0] != ' ')
            result[j++] = toupper(buffer[0]);

        for (i = 1; buffer[i] != '\0'; i++) {
            if (buffer[i] == ' ' && buffer[i+1] != ' ')
                result[j++] = toupper(buffer[i+1]);
        }

        result[j] = '\0';

        printf("Abbreviation: %s\n", result);

        write(connfd, result, MAX);
    }

    close(connfd);
    close(sockfd);
}