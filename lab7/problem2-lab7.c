#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

#define message_size 50

int main(){

    


    int fd[2];
    pipe(fd);
    int fd2[2];
    pipe(fd2);

    

    pid_t child = fork();

    if(child<0){
        printf("ERROR");
        return 1;
    }   
    else if(child==0){

        close(fd[0]);
        close(fd2[1]);

        char S[message_size];
        int ch;

        printf("enter a string\n");

        if(fgets(S,sizeof(S),stdin)==NULL){
            return 1;
        }
        if(S[strlen(S)-1] != '\n'){
            while(((ch = getchar()) != '\n') && (ch != EOF));
        }
        strtok(S,"\n");

        int bytes_sent = write(fd[1],S,strlen(S));

        printf("Child wrote %s\n",S);
        printf("Child wrote %d bytes\n",bytes_sent);

        int x;
        bool sameBytes = false;
        bool sameChars = false;

        read(fd2[0],&x,sizeof(x));
        printf("Child: Bytes received from parent=%d\n",x);

        if(x==bytes_sent){
            sameBytes = true;
        }

        read(fd2[0],&x,sizeof(x));
        printf("Child: Number of characters received=%d\n",x);

         if(x==strlen(S)){
            sameChars = true;
        }

        if(sameBytes&&sameChars){
            printf("Child ==>Message successfully received!!\n");
        }

    } 
    else{
        close(fd[1]);
        close(fd2[0]);

        char S[message_size];

        int bytes_received = read(fd[0],S, sizeof(S));

        int size = strlen(S);

        printf("Parent reads %s\n",S);
        printf("Parent reads %d bytes\n",bytes_received);

        write(fd2[1],&bytes_received,sizeof(int));
        write(fd2[1],&size,sizeof(int));

    }

    return 0;
}
