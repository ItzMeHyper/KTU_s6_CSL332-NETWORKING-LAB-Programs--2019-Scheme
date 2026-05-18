#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>

int main(int argc, char* argv[]) {
    int sockfd;
    struct sockaddr_in server, client;
    char buffer[100];

    if (argc != 3)
        printf("Input format not correct");

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[2]));

    while(1){
        printf("Enter a number: ");
        fgets(buffer, 100, stdin);

        sendto(sockfd, buffer, sizeof(buffer), 0,
               (struct sockaddr*)&server, sizeof(server));

        if (strncmp(buffer, "exit", 4) == 0){
            printf("Exitted Successfully!\n");
            break;
        }

        socklen_t server_len = sizeof(server);

        recvfrom(sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr*)&server, &server_len);

        printf("%s\n", buffer);
    }

    return 0;
}