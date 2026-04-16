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
void listIssuedBooks();  // done
void listadminfunctions(); //done
void displayuser(char* usrname);  //done 
void issueBook(char* usrname );  //done
void returnBook(char* usrname); //done 
void checkAvailability();  //done 
void updateuserprofile(char* usrname); //done
void display_available_books(); //done 
void displayDueBooks(char* usrname);  //done
void listusrfunctions();  //done
void renewBook(char* usrname); //done 
int isLeap(int year);
int daysInMonth(int month , int year);
int totaldays(int d , int m , int y);
void display_book_in_library();