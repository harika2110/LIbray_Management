#include<stdio.h> 
void login(char* name , char* password); 
unsigned long hashPassword(char* str ) ;
int checkadmin( FILE* fptr , char* name, unsigned long hash ) ;