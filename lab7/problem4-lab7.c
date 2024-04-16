#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

#define string_size 50

int main(int argc, char* argv[]){

    if(argc<2){
        return 1;
    }




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
        close(fd[1]);
        close(fd2[0]);
        
        char S[string_size];
        int counter = 0; 
        int idx = 0;
        int countOfC = 0;
        char x;
        char c;

	read(fd[0],&x,1);

        while(x!='*'){
              S[idx]=x;
              idx++;
              counter++;
	      read(fd[0],&x,1);
       }
	printf("Child: Read = %d\n",counter);
	read(fd[0],&c,1);
		
        for(int i = 0;S[i]!='\0';i++){
            if(S[i]==c){
                countOfC++;
            }
        }

        write(fd2[1],&countOfC,sizeof(int));

        

    } 
    else{
        close(fd[0]);
        close(fd2[1]);

        printf("Parent: Sending the characters and then * to end\n");

        char *str = argv[1];
	char star = '*';

        for(int i = 0;str[i] != '\0';i++){
            write(fd[1],&str[i],sizeof(char));
        }
	write(fd[1],&star,sizeof(char));
        char c;

       	printf("Parent: please enter character c:\n");
        scanf("%c",&c);
	
        write(fd[1],&c,sizeof(char));

        int count;

        read(fd2[0],&count,sizeof(int));

        printf("Parent ==> Occurrence of letter '%c' received from Child = %d",c,count);
        
    }

    return 0;
}
