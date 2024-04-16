#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char** argv){

    char **arr = (char **) mmap(NULL, 4*sizeof(char*), PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for(int i = 0;i<4;i++){

        arr[i] = mmap(NULL, 20*sizeof(char), PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    }


    pid_t child = fork();

    if(child<0){
        printf("ERROR");
        return 1;
    }
    else if(child==0){
        char S[20];
        int ch;

        printf("From child:\n");

        for(int i = 0;i<4;i++){

            printf("please enter a string %d:\n",i+1);

            if(fgets(S,sizeof(S),stdin)==NULL){
            return 1;
            }
            if(S[strlen(S)-1] != '\n'){
                while(((ch = getchar()) != '\n') && (ch != EOF));
            }
            strtok(S,"\n");
            strcpy(arr[i],S);
            
        }

        exit(1);
    }
    else {
        int status;
        wait(&status);


        int get_number_of_letters(char S[]){
            int i = 0;
            int counter = 0;
            while(S[i]!='\0'){
                if(isalpha(S[i])){
                    counter++;
                }
                i++;
            }
            return counter;
        }
        int get_number_of_upper(char S[]){
            
            int i = 0;
            int counter = 0;
            while(S[i]!='\0'){
                if(isupper(S[i])){
                    counter++;
                }
                i++;
            }
            return counter;
        }
        int get_number_of_lower(char S[]){
            int i = 0;
            int counter = 0;
            while(S[i]!='\0'){
                if(islower(S[i])){
                    counter++;
                }
                i++;
            }
            return counter;
        }
        int get_number_of_integers(char S[]){
            int i = 0;
            int counter = 0;
            while(S[i]!='\0'){
                if(isdigit(S[i])){
                    counter++;
                }
                i++;
            }
            return counter;
        }
        int get_number_of_special(char S[]){
            int i = 0;
            int counter = 0;
            while(S[i]!='\0'){
                if(!isspace(S[i]) && !isdigit(S[i]) && !isalpha(S[i])){
                    counter++;
                }
                i++;
            }
            return counter;
        }
        void transform_to_upper(char S[]){
            int i = 0;
            while(S[i]!='\0'){
                S[i] = toupper(S[i]);
                i++;
            }
        }

        printf("From parent:\n");

        for(int i = 0;i<4;i++){
            
            printf("*** String %d ***\n",i+1);
            printf("%s\n",arr[i]);
            printf("Length = %d\n",get_number_of_letters(arr[i]));
            printf("The number of letters is: %d\n",get_number_of_letters(arr[i]));
            printf("The number of uppercase letters is: %d\n",get_number_of_upper(arr[i]));
            printf("The number of lowercase letters is: %d\n",get_number_of_lower(arr[i]));
            printf("The number of integers is: %d\n",get_number_of_integers(arr[i]));
            printf("The number of special characters is: %d\n",get_number_of_special(arr[i]));
            printf("Transform to upper case:\n");
            transform_to_upper(arr[i]);
            printf("%s\n",arr[i]);


        }

        
    }

    for(int i = 0;i<4;i++){
       munmap(arr[i],20*sizeof(char));
    }
    munmap(arr,4*sizeof(char*));

    return 0;
}


