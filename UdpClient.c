#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
    struct sockaddr_in server, client;

    if (argc != 3)
        printf("Input format not correct");

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        printf("Error in socket();");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[2]));

    char buffer[100];
    while(1){
        printf("Enter a message to be sent to server: ");
        fgets(buffer, 100, stdin);

        if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
            printf("Error in sendto");
        }
        
        // Exit condition
        if (strncmp(buffer, "exit", 4) == 0){
            printf("Exitted Successfully!\n");
            break;
        }

        socklen_t server_len = sizeof(server);

        if (recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, &server_len) < 0) {
            perror("Error in recvfrom");
        }

        printf("Got a datagram: %s", buffer);
    }
    return 0;
}