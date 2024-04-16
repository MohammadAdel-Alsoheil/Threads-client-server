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
    
    void *status = 0;
    int client_socket;

    struct sockaddr_in servaddr;

    if((client_socket = socket(AF_INET,SOCK_STREAM,0))<0){
        perror("socket error");
        exit(1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);

    if(inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr)<=0){
        perror("ERROR");
        exit(1);
    }

    if(connect(client_socket, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        perror("ERROR");
        exit(1);
    }

    char message[] = "Hello Server";
    char rv[4096];
    char s[50];
    char c;
    int occurences;


    send(client_socket,message, strlen(message),0);

    recv(client_socket, rv, sizeof(rv),0);

    printf("Received: %s\n",rv);


    printf("please Enter a String S:\n");

    if(fgets(s, sizeof(s),stdin)==NULL){
        return 1;
    }
	
    printf("please enter a character c:\n");

    scanf(" %c",&c);
	
    send(client_socket,s,strlen(s),0);
    send(client_socket,&c,sizeof(c),0);


    recv(client_socket,&occurences,sizeof(occurences),0);

    printf("Number of occurences = %d",occurences);

    close(client_socket);

    return 0;
}
