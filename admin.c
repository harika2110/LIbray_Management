#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#include "fun.h"
int checkadmin( FILE* fptr , char* name, unsigned long hash ) 
{ 
    char line[100];
    int found=0;
    while( fgets( line , 100 , fptr) != NULL )
    {
        char* temp = strtok( line , ",");
        if( strcmp( temp , name ) == 0 )
        {  
            unsigned long number ;
            temp = strtok(NULL , "\n");
            sscanf( temp , "%lu", &number);
            if( number == hash ) 
            {
                found = 1;
            }
            else found =0;
        }
        else 
        {
             found =0;
        }
        if( found == 1 )
        {
            break ; 
        }   
    }
    return found ; 
}
void listadminfunctions(){
    printf("Enter\n"
    "(1) to add any Book\n"
    "(2) to remove any Book\n"
    "(3) to update details of any Book\n"
    "(4) to list Overdue Books\n"
    "(5) to list Issued Books\n"
     );
    return ; 
   
}
void addBook()
{
    printf("--------FUNCTION -------ADDING_BOOK-------\n");
    FILE* fptr = fopen("books.txt", "a+");
    int id=1;
    char* line = (char*)malloc(100*sizeof(char));
    while( fgets(line , 100 , fptr) != NULL )
    {
        id++;
    }
    char help;
    char book_name[20];
    char author_name[20];
    int copies;
    label : 
    printf("Enter Book name : ");
    scanf("%c" , &help);
    fgets( book_name , 20 , stdin );
    book_name[strlen(book_name) -1 ] = '\0';
    printf("Enter Author name : ");
    fgets(author_name ,20 , stdin);
    author_name[strlen(author_name) -1]='\0';
    printf("Enter the no.of copies of the book : ");
    scanf("%d",&copies);
    printf("Are all details correct [y/n] ? ");
    scanf(" %c", &help);
    if( help == 'y')
    { 
        fprintf(fptr , "%d,%s,%s,%d,%d\n" , id, book_name , author_name , copies , copies );
    }
    else 
    {
        clearing(book_name);
        clearing(author_name);
        goto label;
    }
    printf("Book added Successfully");
    return ;
}