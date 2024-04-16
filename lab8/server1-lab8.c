#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SERV_PORT 5554
#define BACKLOG 10  
#define MAXLINE 4096


int main(){
    
    int server_socket = 0;

    int client_socket = 0;
    struct sockaddr_in servaddr;

    int client_counter = 0;
 

    server_socket = socket(AF_INET, SOCK_STREAM,0);

    if(server_socket<0){
        exit(1);        
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);


    if(bind(server_socket, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        perror("binding error");
        exit(1);
    }


    if(listen(server_socket, BACKLOG) <0){
        exit(1);
    }

    while(1){
        client_socket = accept(server_socket, (struct sockaddr *) NULL, NULL);

        if(client_socket <0){
            continue;
        }
        client_counter++;

        char buff[MAXLINE];
        char buff2[MAXLINE];
        char message[] = "Hello Client";
        char c;
        int n = read(client_socket, buff, sizeof(buff));
        
        if(n<0){
            perror("Reading Error");
        }
        else{
            buff[n]='\0';
        }

        printf("Recieved: %s\n",buff);

        if(write(client_socket,message,sizeof(message))<0){
            perror("Writing Error");
        }

        printf("waiting for the client to send the string s and character c\n");

        n = read(client_socket,buff2,sizeof(buff2));
	int bytes = n;

        if(n<0){
            perror("Reading Error");
        }
        else{
            buff2[n] = '\0';
        }

        n = read(client_socket,&c,sizeof(c));

        if(n<0){
            perror("Reading Error");
        }
       

        printf("Number of bytes read = %d\n",bytes);
        printf("String received: %s\n",buff2);
        printf("Character received: %c\n",c);

        int i = 0;
        int counter = 0;

        while(buff2[i]!='\0'){
            if(buff2[i]==c){
                counter++;
            }
            i++;
        }

	printf("Count: %d\n",counter);
	
	for(int i =0;i<999;i++){};
	//just to force the cpu to print the count in the server before context switch
        if(write(client_socket,&counter,sizeof(counter))<0){
            perror("Writing Error");
        }

        close(client_socket);
    }

    close(server_socket);
    



    return 0;
}
