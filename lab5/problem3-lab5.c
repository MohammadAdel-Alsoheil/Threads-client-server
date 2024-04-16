#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){


    printf("Main Process PID= %d, PPID=%d\n",getpid(),getppid());


    pid_t child = fork();

    if(child<0){
        printf("An ERROR occured\n");
    }
    else if(child==0){
        sleep(5);
	printf("Child process PID= %d , PPID= %d\n",getpid(),getppid());
	printf("Ready to kill my parents!\n");	

        char ppid_str[10]; 
        snprintf(ppid_str, sizeof(ppid_str), "%d", getppid());

        kill(getppid(),SIGINT);
        printf("I am an orphan now\n");
	fflush(stdout);
        
    }
    else{
        wait(NULL);
        printf("I am the parent\n");
       
    }


   
    return 0;
}



