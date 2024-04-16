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


void* server_handler(void*);
    

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

        pthread_t t;

        pthread_attr_t attr;

        pthread_attr_init(&attr);

        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

        int client_sock = client_socket;
        pthread_create(&t,&attr,server_handler, (void*) &client_sock);
    }

    close(server_socket);
    



    return 0;
}

void * server_handler(void* arg){
    int conn = *((int*)arg);

    char buff[MAXLINE];

    int buff2[MAXLINE];

    char message[] = "Hello client\n";

    int n = read(conn,buff, sizeof(buff) );

    if(n<0){
        perror("Reading error");
    }
    else{
        buff[n]='\0';
    }
    printf("Received %s\n",buff);


    if(write(conn,message,sizeof(message))<0){
            perror("Writing Error");
        }

    printf("Waiting for client to send array\n");
    
     n = read(conn,buff2,sizeof(buff2));
 
        if(n<0){
            perror("Reading Error");
        }
 
        printf("Number of bytes read = %d; thus %d is the size of the array ",n,n/sizeof(int));
 
        for(int i = 0;i<n/sizeof(int);i++){
            printf("%d ",buff2[i]);
        }

        printf("\n");
        printf("finished reading\n");
        printf("computing sum\n");
 
        
        int sum = 0;
 
        for(int i = 0;i<n/sizeof(int);i++){
            sum = sum + buff2[i];
        }
 
        printf("Sum: %d\n", sum);

        if(write(conn,&sum, sizeof(sum))<0){
            perror("Writing Error");
        }
 
        close(conn);
        pthread_exit(NULL);
}
    
