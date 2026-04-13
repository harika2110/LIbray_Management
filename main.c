#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<curses.h>
#include "fun.h" 
int main(){
    char usrname [50];
    char password[10];
    char password2[10];
    int n=1;
    printf("Enter-----\n(1) to login as Admin\n(2) to login as a User\n(3) to sign up\n(4) to exit \n");
    printf("\n");
    scanf("%d", &n); 
  while( n!= 4 ) 
{ 
     clearing(usrname );
     clearing(password);
     if( n==1) //admin login
   { 
      int j=1;
      loginusrname(usrname );
      initscr();
      clear();
      loginpassword( password ,password2 , j );
      endwin(); 
      unsigned long hash = hashPassword( password); 
       FILE* fptr = fopen("admin.txt" , "r");
      if( ! checkadmin ( fptr , usrname , hash ) ) 
      {    
           printf("Failed to login ----------- Wrong Username or Password\n");
           printf("\nEnter-----\n(1) to login as Admin\n(2) to login as a User\n(3) to sign up\n(4) to exit \n");
           printf("\n");
           scanf("%d", &n);
           continue ;  
      }
      else 
      { 
          printf("Logined Successfully\n");
          adminmenu : 
          listadminfunctions();
          int num;
          scanf("%d", &num );
          if(num ==1 )
          {
             addBook();
          }
          else if(num == 2 )
          {
              removeBook();
          }
          else if(num == 3 )
          {
              updateBookdetails();
          }
          else if(num == 4)
         {
            listIssuedBooks();
         }
         if(num != 5)
         {
            goto adminmenu ; 
         }   

      }
      fclose(fptr);
   }
   if(n==2) //usr login
   {  
      int j=1;
      loginusrname(usrname);
      initscr();
      clear();
      loginpassword(password , password2 ,j);
      endwin();
      unsigned long hash = hashPassword( password); 
      FILE* fptr = fopen("user.txt", "r" );
      if( !checkuser( fptr , usrname , hash ))
      {  
         printf("Failed to login ----- No user exists with that Username and Password\n");
         printf("\nEnter-----\n(1) to login as Admin\n(2) to login as a User\n(3) to sign up\n(4) to exit \n");
         printf("\n");
         scanf("%d", &n);
         continue ; 
      }
      else
      {
         printf("Hurray you have logged in\n");
         usrmenu : 
         updateuserprofile(usrname);
         listusrfunctions();
         int num;
         scanf("%d",&num);
         if(num == 1 )
         {
            displayuser(usrname);
         }
         else if(num == 4 )
         {
            checkAvailability(); 
         }
         else if(num == 2)
         {
            issueBook(usrname );
         }
         else if( num == 3)
         {
            returnBook(usrname);
         }
         else if(num == 5 )
         {
            display_available_books(); 
         }
         else if(num == 6)
         {
            renewBook(usrname);
         }
         else if(num == 7)
         {
            displayDueBooks(usrname);
         }
         if(num != 8)
         {
            goto usrmenu;
         }
      }
      fclose(fptr);

    }
    if( n == 3 )  //usr signup 
    {   FILE* fptr = fopen("user.txt", "a+");
        char usrname[50];
        printf(" ------------ Creating Account ----------\n");
        char k;
        scanf("%c", &k);
        int found = 1;
        while( found )
        {   clearing(usrname);
            printf("Enter Username : ");
            fgets( usrname , 50 , stdin );
            usrname[strlen(usrname) -1] = '\0' ; 
            found = checkusrname(fptr , usrname );
            if( found == 1 )
            {
                printf("Username already exists. Please try other username\n");
            }
            else 
            {   int ok=0;
                while( !ok )
               { 
                 clearing(password2);
                 clearing(password);
                 int j=2 ;   
                 initscr();
                 clear();
                 loginpassword(password , password2 , j );
                 endwin();

                 if( strcmp(password , password2 ) !=0)
                   {  
                      ok = 0;
                   }    
                 else 
                   {  
                      ok = 1 ; 
                   }  
               }
               int k=0;
               fprintf(fptr , "%s,%lu,%d,%d\n", usrname , hashPassword(password),k,k );
               printf("Signed Up Successfully\n" ); 
               
               
                              
            }

        }
        fclose(fptr);
    }


    printf("\nEnter-----\n(1) to login as Admin\n(2) to login as a User\n(3) to sign up\n(4) to exit \n\n");
    scanf("%d",&n);

}
printf("Exited\n" );
   
}