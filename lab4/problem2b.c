#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    pid_t child1  = fork();

    if(child1<0){
        printf("An Error Occured\n");
    }
    else{
        if(child1==0){
            printf("Child1 Process PID= %d, PPID=%d\n",getpid(),getppid());
        }
        else{
            wait(NULL);
            pid_t child2  = fork();
            if(child2<0){
                printf("An Error Occured\n");
            }
            else{
                if(child2==0){
                    printf("Child2 Process PID= %d, PPID=%d\n",getpid(),getppid());
                }
                else{
                    wait(NULL);
                    printf("Parent Process PID= %d, PPID=%d\n",getpid(),getppid());
                }
            }
            
            
        }
    }

    return 0;
}



