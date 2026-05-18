#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 100

int main(){
    int sockfd, connfd;
    struct sockaddr_in server, client;
    char buffer[MAX];
    int sum, temp, rem, n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd, 1);
    printf("Server Waiting..\n");

    connfd = accept(sockfd, NULL, NULL);
    printf("Client Connected\n");

    while(1){
        bzero(buffer, MAX);
        read(connfd, buffer, MAX);

        n = atoi(buffer);

        sum = 0;
        temp = n;

        while(temp>0){
            rem = temp%10;
            sum += rem*rem*rem;
            temp = temp/10;
        }

        if(sum == n){
            strcpy(buffer, "Armstrong Number");
        }else{
            strcpy(buffer, "Not An Armstrong Number");
        }
        write(connfd, buffer, MAX);
    }

    close(sockfd);
    close(connfd);
}