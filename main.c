#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<curses.h>
#include "fun.h" 
struct admin{  
    char name[50];
    char password[10];
};
struct user{
     char name[50];
     char password[10];
    
};
int main(){
    int n=1;
    printf("Enter\n(1) to login as Admin\n(2) to login as a User\n(3) to sign up\n(4) to exit \n");
    scanf("%d", &n); 
  while( n!= 4 ) 
{
   char name[50];
   char password[10];
   login(name , password); 
   unsigned long hash = hashPassword( password); 
   if( n==1)
   {
       FILE* fptr = fopen("admin.txt" , "r");
      if( ! checkadmin ( fptr , name , hash ) ) 
      {
           printf("Wrong username or password\n");
           printf("Enter (1) to login as Admin and (2) to login as a User and (3) to exit : \n");
           scanf("%d", &n);
           continue ;  
      }
      else 
      {
           
      }
   }
   
   printf("Enter (1) to login as Admin and (2) to login as a User and (3) to exit : \n");
   scanf("%d", &n); 
}
printf("Exited\n");
   
}