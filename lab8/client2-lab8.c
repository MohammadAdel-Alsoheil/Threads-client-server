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

    char message[] = "hello";
    char rv[4096];
    int size;


    send(client_socket,message, strlen(message),0);

    recv(client_socket, rv, sizeof(rv),0);

    printf("Received: %s\n",rv);


    printf("please Enter the size of the array:\n");
    scanf("%d",&size);

    int array[size];

    printf("please enter the %d numbers:\n", size);

    for(int i = 0;i<size;i++){

        scanf("%d",&array[i]);
    }

    send(client_socket, array, sizeof(int)*size,0);


    int sum;


    recv(client_socket, &sum, sizeof(sum),0);

    printf("Sum: %d",sum);

    

    

    close(client_socket);

    return 0;
}
