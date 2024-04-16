#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>


int main(){

    int fd[2];
    pipe(fd);

    pid_t child = fork();

    if(child<0){
        printf("ERROR");
        return 1;
    }
    else if(child==0){
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);

        char *exp[] = {"pwd",NULL};

        if(execvp("ls",exp)<0){
            perror("Execvp failed from child");
        }
        exit(EXIT_FAILURE);
    }
    else{
        wait(NULL);
        close(0);
        dup(fd[0]);
        close(fd[1]);
        close(fd[0]);

        char* exp[] = {"wc","-l",NULL};

        if(execvp("wc",exp)<0){
            perror("Execvp failed from parent");
        }
        exit(EXIT_FAILURE);

    }

    close(fd[0]);
    close(fd[1]);

    return 0;
}
