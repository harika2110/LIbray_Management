#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include "fun.h"
int checkuser( FILE* fptr , char* name, unsigned long hash ) 
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
int checkusrname(FILE* fptr , char* name )
{
     char* line = (char*)malloc( 1000*sizeof(char) );
     int found =0;
     while(fgets(line , 1000 , fptr ) != NULL)
     {
        char* temp = strtok(line , ",");
        if( strcmp(temp , name) ==0)
        {
            found = 1;
            break;
        }
     }
     return found;

}
void listusrfunctions(){
    
}