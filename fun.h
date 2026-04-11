#include<stdio.h> 
void loginusrname(char* name );
void loginpassword(char* password , char* password2 , int j); 
unsigned long hashPassword(char* str ) ;
void clearing(char* str);
int checkadmin( FILE* fptr , char* name, unsigned long hash ) ;
int checkuser(FILE* fptr , char*name , unsigned long hash);
int checkusrname(FILE* fptr ,  char* name );
void addBook();
void removeBook();
void updateBookdetails();
void listOverdueBooks();
void listIssuedBooks(); 
void listadminfunctions();