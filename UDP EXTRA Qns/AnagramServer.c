#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>

void sort(char str[]) {
    int i, j;
    char temp;

    for(i = 0; str[i] != '\0'; i++) {
        for(j = i + 1; str[j] != '\0'; j++) {
            if(str[i] > str[j]) {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int sockfd;
    struct sockaddr_in server, client;
    char str1[100], str2[100], result[100];
    
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

        recvfrom(sockfd, str1, 100, 0,
                 (struct sockaddr*)&server, &server_len);

        recvfrom(sockfd, str2, 100, 0,
                 (struct sockaddr*)&server, &server_len);

        if (strncmp(str1, "exit", 4) == 0){
            printf("Exitted Successfully!\n");
            break;
        }

        str1[strcspn(str1, "\n")] = '\0';
        str2[strcspn(str2, "\n")] = '\0';

        sort(str1);
        sort(str2);

        if(strcmp(str1, str2) == 0)
            strcpy(result, "Given words are Anagrams");
        else
            strcpy(result, "Given words are not Anagrams");

        sendto(sockfd, result, sizeof(result), 0,
               (struct sockaddr*)&server, sizeof(server));
    }

    return 0;
}