#include<stdio.h> 
void loginusrname(char* name ); //done
void loginpassword(char* password , char* password2 , int j); //done
unsigned long hashPassword(char* str ) ; //done
void clearing(char* str);  //done
int checkadmin( FILE* fptr , char* name, unsigned long hash ) ;  //done
int checkuser(FILE* fptr , char*name , unsigned long hash);   //done
int checkusrname(FILE* fptr ,  char* name );   //done
void addBook();  //done  
void removeBook();  //done
void updateBookdetails();  //done
void listOverdueBooks();
void listIssuedBooks();  // done
void listadminfunctions();
