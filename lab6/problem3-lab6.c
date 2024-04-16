#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>


int main(){
	printf("please enter N the number of integers:\n");
    int N;
	scanf("%d",&N);
    
    int *arr = (int *) mmap(NULL,N*sizeof(N),PROT_READ | PROT_WRITE ,MAP_SHARED | MAP_ANONYMOUS,-1,0);

    pid_t child1 = fork();
	pid_t child3;
	pid_t child2;
    if(child1<0){
        printf("ERROR");
        return 1;
    }
    else if(child1==0){
        child3 = fork();

        if(child3<0){
            printf("ERROR");
            return 1;
        }
        else if(child3==0){

            printf("*** From Child 3 ***\n");
            printf("please enter %d integers\n",N);

            for(int i = 0;i<N;i++){
                int y;
                scanf("%d",&y);
                arr[i] = y;
            }
            for(int i = 0;i<N;i++){
                printf("%d ",arr[i]);
            }
		printf("\n");
        }
        else{
            wait(NULL);
            printf("*** From Child 1: ***\n");

            for(int i = 0;i<N;i++){
                arr[i] = arr[i] *10;
            }
            for(int i = 0;i<N;i++){
                printf("%d ",arr[i]);
            }
            printf("\n");

        }
    }
    else{
        wait(NULL);
        child2= fork();
        if(child2<0){
            printf("ERROR");
            return 1;
        }
        else if(child2==0){
            printf("*** From Child 2: ***\n");

            for(int i = 0;i<N;i++){
                arr[i] = arr[i] -2;
            }
            for(int i = 0;i<N;i++){
                printf("%d ",arr[i]);
            }
            printf("\n");
        }
        else{
		wait(NULL);
            printf("*** From Parent: ***\n");

            int sum = 0;
             for(int i = 0;i<N;i++){
                sum = sum + arr[i];
            }
            arr = mremap(arr, N*sizeof(int), (N+1)*sizeof(int),0); 

            arr[N] = sum;
            

            for(int i = 0;i<=N;i++){
                printf("%d ",arr[i]);
            }
            printf("\n");

        }
	munmap(arr,(N+1)*sizeof(int));

    }

    return 0;

}
