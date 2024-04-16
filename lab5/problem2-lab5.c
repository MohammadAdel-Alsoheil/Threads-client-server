#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    char command[20];
    int ch;

    printf("Enter a command to execute: ");

    if(fgets(command,sizeof(command),stdin)==NULL){
        return 1;
    }
    if(command[strlen(command)-1] != '\n'){
        while(((ch = getchar()) != '\n') && (ch != EOF));
    }
    strtok(command,"\n");



    pid_t child = fork();

    if(child<0){
        printf("Am ERROR occured");
    }
    else if(child==0){
        printf("Parent process: Created child process with PID: %d\n",getpid());
        fflush(stdout);
        execlp("sh","sh","-c",command,NULL);
        exit(1);
    }
    else{
        wait(NULL);
        printf("Parent process: Child process completed");
       
    }


   
    return 0;
}



