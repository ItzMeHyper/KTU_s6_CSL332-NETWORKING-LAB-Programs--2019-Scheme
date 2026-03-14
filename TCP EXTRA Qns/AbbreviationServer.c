#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd){
    char buff[MAX];
    char result[MAX];
    int i, j;

    for (;;) {
        bzero(buff, MAX);
        bzero(result, MAX);

        read(connfd, buff, sizeof(buff));

        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }

        buff[strcspn(buff, "\n")] = '\0';

        j = 0;

        if (buff[0] != ' ')
            result[j++] = toupper(buff[0]);

        for (i = 1; buff[i] != '\0'; i++) {
            if (buff[i] == ' ' && buff[i+1] != ' ') {
                result[j++] = toupper(buff[i+1]);
            }
        }

        result[j] = '\0';

        write(connfd, result, sizeof(result));
    }
}

int main(){
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        printf("Socket creation failed\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (SA*)&servaddr, sizeof(servaddr));

    listen(sockfd, 5);

    len = sizeof(cli);

    connfd = accept(sockfd, (SA*)&cli, &len);

    func(connfd);

    close(sockfd);
}