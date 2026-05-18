#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 100

int main() {
    int sockfd, connfd;
    struct sockaddr_in server, client;
    char buffer[MAX], result[MAX];
    int n, first, last;

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

        n = atoi(buffer);

        last = n % 10;

        while (n >= 10)
            n = n / 10;

        first = n;

        sprintf(result, "First Digit = %d , Last Digit = %d", first, last);
        write(connfd, result, MAX);
    }

    close(connfd);
    close(sockfd);
}