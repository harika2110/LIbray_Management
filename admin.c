#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#include "fun.h"
int checkadmin( FILE* fptr , char* name, unsigned long hash ) 
{ 
    char* line = (char*)malloc(100*sizeof(char));
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
    free(line);
    return found ; 
}
void listadminfunctions(){
    printf("\nEnter-----\n"
    "(1) to add any Book\n"
    "(2) to remove any Book\n"
    "(3) to update details of any Book\n"
    "(4) to list Issued Books ( in alphabetical order )\n"
    "(5) to logout\n"
     );
    return ; 
   
}
void addBook()
{
    printf("--------FUNCTION -------ADDING_BOOK-------\n");
    FILE* fptr = fopen("books.txt", "a+");
    int id=1;
    char* line = (char*)malloc(100*sizeof(char));
   
    char help;
    char book_name[20];
    char author_name[20];  int found;
    int copies;
    label : 
    found =0;
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
     while( fgets(line , 100 , fptr) != NULL )
    {   
        char* temp = strtok(line , ",");
        temp = strtok(NULL , ",");
        if( strcmp(book_name , temp ) == 0)
        {
             found = 1;
        }
        id++;
    }
    scanf(" %c", &help);
    if( help == 'y' && found != 1 )
    { 
        fprintf(fptr , "%d,%s,%s,%d,%d\n" , id, book_name , author_name , copies , copies );
    }
    else 
    {
        clearing(book_name);
        clearing(author_name);
        if( found == 1 )
        {
            printf("The book already exists\n");
        }
        printf("Do you want to try adding book again [y/n]? ");
        char k;
        scanf(" %c" , &k);
        if( k=='y')  
        {
            goto label ; 
        }
    }
    printf("Book added Successfully\n\n");
    
    fclose(fptr);
    free(line);
    return ;
}
void removeBook(){

    printf("-----------FUNCTION------REMOVING_BOOK-------\n");
    
    int found = 0;
    char book_name[20];
    char help;
    int num=1;
    char* line = (char*) malloc( 100*sizeof(char)); 
    label :
    scanf("%c", &help);
    num=1;
    printf("Enter the name of the Book : ");
    fgets( book_name , 20 , stdin );
    book_name[strlen(book_name)-1] = '\0' ; 
    printf("Do you really want to delete the book named %s [y/n] ? " , book_name );
    scanf(" %c", &help); 
    if( help == 'n' )
    {   clearing(book_name);
        printf("Do you want to try deleting any other book [y/n] ? ");
        scanf(" %c", &help);
        if( help == 'y')
        {  goto label; }
        else 
        {
            free(line);
            return ; 
        }
    }
    else 
    {   
        FILE* fin = fopen("books.txt" , "r");
        FILE* fout = fopen("new.txt" , "w" );
        while( fgets( line , 100, fin ) != NULL)
        {  
            char* temp = strtok(line,",");
                  temp = strtok(NULL , ",");
            if( strcmp(temp,book_name) == 0)
            {    
                 found = 1;
            }
            else 
            {              
               fprintf(fout , "%d,%s,",num, temp);
               temp = strtok(NULL , "\n");
               fprintf(fout , "%s\n" , temp ); 
               num ++;
            }
        }
        fclose(fin);
        fclose(fout);
        system("rm books.txt");
        system("mv new.txt books.txt");     
    }
    if( found != 1 )
    {
        printf("No book exists with that title\n");
        printf("Do you want to try deleting any other book [y/n] ? ");
        scanf(" %c", &help);
        if( help == 'y')
        {  goto label; }
    }
    else 
    {
        printf("Book is removed Successfully\n");
    }
    free(line);
    return ; 
     
}
void updateBookdetails()
{
    printf("-----------FUNCTION------UPDATING_BOOK_DETAILS--------\n");
    int found = 0;
    char book_name[20];
    char author_name[20];
    int copies;
    int available;
    char help;
    int num=1;
   
    label :
    scanf("%c", &help);
    printf("Enter the name of the Book : ");
    fgets( book_name , 20 , stdin );
    book_name[strlen(book_name)-1] = '\0' ; 
    printf("Enter the name of the Author : ");
    fgets(author_name , 20 , stdin );
    author_name[strlen(author_name)-1] = '\0';
    printf("Enter the total no.of copies : ");
    scanf("%d",&copies);
    printf("Enter the available no.of copies : ");
    scanf("%d", &available);
    printf("Do you really want to update the details of the book named %s [y/n] ? " , book_name );
    scanf(" %c", &help); 
    num = 1;
    if( help == 'n' )
    {   clearing(book_name);
        printf("Do you want to try updating again [y/n] ? ");
        scanf(" %c", &help);
        if( help == 'y')
        {  goto label; }
    }
    else 
    {   char* line = (char*) malloc( 100*sizeof(char)); 
        FILE* fin = fopen("books.txt" , "r");
        FILE* fout = fopen("new.txt" , "w" );
        while( fgets( line , 100, fin ) != NULL)
        {  
            char* temp = strtok(line,",");
                  temp = strtok(NULL , ",");
            if( strcmp(temp,book_name) == 0)
            {    fprintf(fout,"%d,%s,%s,%d,%d\n" ,num ,book_name , author_name , copies , available);
                 num++;
                 found = 1;
            }
            else 
            {              
               fprintf(fout , "%d,%s,",num, temp);
               temp = strtok(NULL , "\n");
               fprintf(fout , "%s\n" , temp ); 
               num ++;
            }
        }
        fclose(fin);
        fclose(fout);
        free(line);
        system("rm books.txt");
        system("mv new.txt books.txt");     
    }
    if( found != 1 )
    {
        printf("No book exists with that title\n");
        printf("Do you want to try deleting any other book [y/n] ? ");
        scanf(" %c", &help);
        if( help == 'y')
        {  goto label; }
    }
    else 
    {
        printf("Bookdetails are updated Successfully\n");
    }
    return ; 
}
void listIssuedBooks(){
    printf("---------------FUNCTION----LISTING_ISSUED_BOOKS-----------\n");
    char* line = (char*)malloc(100*sizeof(char));
    FILE* fin = fopen("books.txt", "r");
    FILE* fout = fopen("write.txt" , "w");
    int num=0;
    while( fgets(line ,100, fin) != NULL )
    { 
        int copies; 
        int available ;
        char book_name[20];
        char*temp = strtok( line , ",");
        temp = strtok(NULL , ",");
        strcpy(book_name , temp);
        temp = strtok(NULL,",");
        temp = strtok(NULL ,",");
        copies = atoi(temp);
        temp = strtok(NULL , ",");
        available = atoi(temp);
        if(copies != available )
        {  
             num++;
            fprintf(fout , "%s\n", book_name);           
        }

    }
    if( !num )
    {
        printf("No Book is Issued\n");
    }
    fclose(fin);
    fclose(fout);
    if(num)
    {
        system("sort -t, -k 1 write.txt");
    }
    free(line);
    return ; 
}
