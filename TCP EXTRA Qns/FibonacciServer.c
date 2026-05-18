#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 100

int main() {
    int sockfd, connfd;
    struct sockaddr_in server;
    char buffer[MAX], temp[MAX];
    int n, x = 0, y = 1, z, i;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd, 1);

    connfd = accept(sockfd, NULL, NULL);

    while (1) {
        bzero(buffer, MAX);
        read(connfd, buffer, MAX);

        n = atoi(buffer);

        x = 0;
        y = 1;

        sprintf(buffer, "%d %d ", x, y);

        for (i = 3; i <= n; i++) {
            z = x + y;
            sprintf(temp, "%d ", z);
            strcat(buffer, temp);
            x = y;
            y = z;
        }

        write(connfd, buffer, MAX);
    }
}