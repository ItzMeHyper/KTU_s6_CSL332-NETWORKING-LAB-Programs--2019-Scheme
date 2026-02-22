#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
     //fork();
    printf("\nFF\nPID=%d", getpid());
    char *args[] = {"Hello", "ss", "fff", NULL};
    execv("./E2", args);
    printf("\nBackto E1.c\n");
    return 0;
}