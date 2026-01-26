#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
    struct sockaddr_in server, client;

    if (argc != 2)
        printf("Input format not correct");

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        printf("Error in socket();");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
        printf("Error in blind()! \n");

    char buffer[100];
    socklen_t server_len = sizeof(server);

    while (1) {
        printf("server waiting.....\n");

        if (recvfrom(sockfd, buffer, 100, 0, (struct sockaddr*)&server, &server_len) < 0)
            printf("Error in recvfrom()!");

        printf("Got a datagram: %s", buffer);

        if (strncmp(buffer, "exit", 4) == 0){
            printf("Exitted Successfully!\n");
            break;
        }       

        printf("Enter a message to be sent to server: ");
        fgets(buffer, 100, stdin);

        if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
            printf("Error in sendto");
        }
    }
    return 0;
}