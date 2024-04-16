#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>


int main(int argc, char** argv){

    int N;

    if(argc>1){
        N = atoi(argv[1]);
    }
    else{
        return 1;
    }

    int *arr = (int *) mmap(NULL,N*sizeof(N),PROT_READ | PROT_WRITE ,MAP_SHARED | MAP_ANONYMOUS,-1,0);

    pid_t child = fork();

    if(child<0){
        printf("ERROR");
        return 1;
    }
    else if(child==0){

        printf("From child please enter %d integers:\n",N);

        for(int i = 0;i<N;i++){
            int x;
	    scanf("%d",&x);
            arr[i] = x;
        }
        int sum = 0;
        printf("child: array elements: ");
        for(int i = 0;i<N;i++){
            printf("%d ",arr[i]);
            sum = sum + arr[i];
        }
	printf("\n");
        printf("child: Sum = %d",sum);

        exit(0);
    }
    else {
        int status;
        wait(&status);

        printf("\nFrom parent, please enter a:\n");

        int a;
        scanf("%d",&a);

       
        for(int i = 0;i<N;i++){
            arr[i] = arr[i] * a;
        }

        printf("parent: array elements: ");
        for(int i = 0;i<N;i++){
            printf("%d ",arr[i]);
        }
    }
     munmap(arr,sizeof(N)*N);

   


   
    return 0;
}



