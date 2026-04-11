#include<stdio.h> 
#include<stdlib.h>
#include<string.h> 
#include<curses.h>
#include "fun.h"
void login( char* name , char* password )
{  
     printf("Please enter your name : ");
     fgets( name , 50 , stdin );
     printf("You have entered %s" , name );
     return ;

}
unsigned long hashPassword(char* str ) 
{
    unsigned long hash = 5381;
    int c;
    while((c=*str++))
    {
        hash = ((hash <<5) + hash ) +c ;
    }
    return hash; 
}
int checkadmin( FILE* fptr , char* name, unsigned long hash ) 
{ 
    char* line ;
    int found=0;
    while( fgets( line , 100 , fptr) != NULL )
    {
        char* temp = strtok( line , ",");
        if( strcmp( temp , name ) == 0 )
        {
            unsigned long number ;
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