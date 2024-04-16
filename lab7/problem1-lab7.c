
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>



int main(){


    int* N = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    printf("Parent ==> Enter N the number of integers in the list:\n");
    scanf("%d",N);
    printf("Parent ==> sending N=%d\n",*N);

    int fd[2];
    int fd2[2];
    pipe(fd);
    pipe(fd2);

    

    pid_t child = fork();

    if(child<0){
        printf("ERROR");
        return 1;
    }   
    else if(child==0){
        close(fd[0]);
        close(fd2[1]);

        int array[*N];
        printf("Child ==> Enter %d integers:\n",*N);

        for(int i = 0;i<*N;i++){
            int x;
            scanf("%d",&x);
            array[i] = x;
        }
         for(int i = 0;i<*N;i++){
            write(fd[1], &array[i],sizeof(int));
        }
        int numOfPositive;
        read(fd2[0],&numOfPositive,sizeof(int));
        printf("Child ==> The number of positive integers is %d",numOfPositive);


    } 
    else{
        close(fd[1]);
        close(fd2[0]);
        int numberOfpositive = 0;

        printf("Parent ==> The parent received: ");
        for(int i = 0;i<*N;i++){
            int y;
            read(fd[0],&y,sizeof(int));
            if(y>0){
                ++numberOfpositive;
            }
            printf("%d ",y);
        }
	printf("\n");

        printf("Parent ==> the number of positive integers is %d\n",numberOfpositive);
        write(fd2[1],&numberOfpositive, sizeof(numberOfpositive));



    }

    return 0;
}

