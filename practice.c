XY

#include <stdio.h> 
#include <unistd.h> 
int main() 
{ 
   fork() || fork(); 
  
   printf("forked\n"); 
   return 0; 
} 
