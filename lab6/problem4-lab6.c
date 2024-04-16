
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>


int main(){

    int *N = (int*) mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE, MAP_SHARED |MAP_ANONYMOUS, -1,0);

    printf("Enter a postive integer:\n");
    scanf("%d",N);

    if(*N<0){
        printf("Error: The integer should be positive!\n");
        return 1;
    }
    pid_t child = fork();
	int copy = *N;    

    if(child<0){
        printf("ERROR");
        return 1;
    }
    else if(child==0){

        int res = 1;
        for(int i = 1;i<=*N;i++){
            res = res * i;
        }
        *N =res;
    }
    else{
        wait(NULL);
        printf("The factorial of %d is %d\n",copy,*N);

    }
    munmap( N,sizeof(int));

    return 0;

}
