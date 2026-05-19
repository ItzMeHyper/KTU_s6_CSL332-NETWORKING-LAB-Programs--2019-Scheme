#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>

int factorial(int n) {
    int fact = 1, i;
    for(i = 1; i <= n; i++)
        fact *= i;
    return fact;
}

int main(int argc, char* argv[]) {
    int sockfd;
    struct sockaddr_in server, client;
    char buffer[100], result[100];

    if (argc != 2)
        printf("Input format not correct");

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    socklen_t server_len = sizeof(server);

    while (1) {
        printf("server waiting.....\n");

        recvfrom(sockfd, buffer, 100, 0, (struct sockaddr*)&server, &server_len);

        int num = atoi(buffer);

        if (strncmp(buffer, "exit", 4) == 0){
            printf("Exitted Successfully!\n");
            break;
        }   

        int temp = num, sum = 0, rem;

        while(temp > 0) {
            rem = temp % 10;
            sum += factorial(rem);
            temp /= 10;
        }

        if(sum == num)
            strcpy(result, "Given number is Strong Number");
        else
            strcpy(result, "Given number is not Strong Number");

        sendto(sockfd, result, sizeof(result), 0, (struct sockaddr*)&server, sizeof(server));
    }

    return 0;
}