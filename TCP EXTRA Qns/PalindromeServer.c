#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd)
{
    char buff[MAX];
    int i, len, isPal;

    for (;;) {
        bzero(buff, MAX);

        // Read message from client
        read(connfd, buff, sizeof(buff));

        // Exit condition
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
        
        // Remove newline if present
        buff[strcspn(buff, "\n")] = '\0';

        len = strlen(buff);
        isPal = 1;

        for (i = 0; i < len / 2; i++) {
            if (buff[i] != buff[len - i - 1]) {
                isPal = 0;
                break;
            }
        }

        bzero(buff, MAX);

        if (isPal)
            strcpy(buff, "Palindrome\n");
        else
            strcpy(buff, "Not Palindrome\n");

        // Send result to client
        write(connfd, buff, sizeof(buff));
    }
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        exit(0);
    } else {
		printf("Socket successfully created..\n");
    }
    
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
    return 0;
}
