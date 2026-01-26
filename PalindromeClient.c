#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
    char buff[MAX];

    for (;;) {
        bzero(buff, MAX);

        printf("Enter the string: ");
        fgets(buff, MAX, stdin);

        // Send string to server
        write(sockfd, buff, sizeof(buff));

        // Exit condition
        if (strncmp(buff, "exit", 4) == 0)
            break;

        bzero(buff, MAX);

        // Read server response
        read(sockfd, buff, sizeof(buff));
        printf("From Server: %s\n", buff);
    }
}

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection failed\n");
        exit(0);
    }

    printf("Connected to server\n");

    func(sockfd);
    close(sockfd);

    return 0;
}
