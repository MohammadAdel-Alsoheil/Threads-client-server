\
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>

typedef struct movies{
    int id;
    char name[100];
    char date[20];
    float rating;

}Movie;

int main(){


    Movie* M = (Movie*) mmap(NULL,sizeof(Movie)*5,PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS, -1,0);


    printf("Enter details for 5 movies:\n");


    for(int i = 0;i<5;i++){
        printf("Movie %d\n",i+1); 

        printf("ID: ");
        scanf("%d",&M[i].id);

        printf("Name: ");
        scanf("%99s",M[i].name);
       
        printf("Date: ");
        scanf("%19s",M[i].date);

        printf("Rating: ");
        scanf("%f",&M[i].rating);
	printf("\n");

    }

    pid_t child = fork();

    if(child<0){
        printf("ERROR");
        return 1;
    }
    else if(child==0){

        int highest = M[0].rating;
        Movie bestMovie = M[0];
        for(int i = 1;i<5;i++){
            if(M[i].rating>highest){
                highest = M[i].rating;
                bestMovie = M[i];
            }
        }
        printf("Movie with highest rating\n");
        printf("ID: %d\n",bestMovie.id);
        printf("Name: %s\n",bestMovie.name);
        printf("Date: %s\n",bestMovie.date);
        printf("Rtaing: %.2f\n",bestMovie.rating);

    }
    else{
        wait(NULL);
    }

    munmap(M,sizeof(Movie)*5);
    return 0;

}
