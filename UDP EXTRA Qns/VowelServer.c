#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <netdb.h>
#include <sys/socket.h>


int main(int argc, char* argv[]) {
    int sockfd, count, i;
    struct sockaddr_in server, client;
    char buffer[100];

    if (argc != 2)
        printf("Input format not correct");

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    socklen_t server_len = sizeof(server);

    printf("server waiting.....\n");

    recvfrom(sockfd, buffer, 100, 0, (struct sockaddr*)&server, &server_len);

    count = 0;

    for (i = 0; buffer[i] != '\0'; i++) {
        char ch = tolower(buffer[i]);

        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'){
                count++;
        }
    }

    sprintf(buffer, "%d", count);

    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, sizeof(server));

    return 0;
}