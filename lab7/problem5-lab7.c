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

        int n;

        printf("Please enter the number of the country you want to learn about:\n");
        printf("1. Lebanon\n");
        printf("2. Egypt\n");
        printf("3. Tunis\n");
        printf("4. Morocco\n");
        printf("5. Jordan\n");

        printf("Enter the corresponding number: ");
        scanf("%d",&n);

        if(n>5 || n<1){
            printf("Invalid choice. Please try again.");
            return 1;
        }
        write(fd[1],&n,sizeof(int));

        char str[100];

        read(fd2[0],&str,sizeof(str));

        if(n==1){
            printf("Child: The capital of Lebanon is %s",str);
        }
        else if(n==2){
            printf("Child: The capital of Egypy is %s",str);
        }
        else if(n==3){
            printf("Child: The capital of Tunis is %s",str);
        }
        else if(n==4){
            printf("Child: The capital of Morocoo is %s",str);;
        }
        else if(n==5){
            printf("Child: The capital of Jordan is %s",str);
        }



    }
    else{
        close(fd[1]);
        close(fd2[0]);

        int n;
        read(fd[0],&n,sizeof(int));

        char str[100];

        if(n==1){
            snprintf(str,sizeof(str),"Beirut");
        }
        else if(n==2){
            snprintf(str,sizeof(str),"Cairo");
        }
        else if(n==3){
            snprintf(str,sizeof(str),"Tunis");
        }
        else if(n==4){
            snprintf(str,sizeof(str),"Rabat");
        }
        else if(n==5){
            snprintf(str,sizeof(str),"Amman");
        }

        write(fd2[1],&str,strlen(str)+1);



    }
    close(fd[0]);
    close(fd[1]);
    close(fd2[0]);
    close(fd2[1]);
   

    return 0;
}
