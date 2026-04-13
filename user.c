#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<time.h>
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
    printf("Enter\n"
    "(1) to display your user profile\n"
    "(2) to issue a Book\n"
    "(3) to return a Book\n"
    "(4) to check the Availability of a Book\n"
    "(5) to calaculate the fine to be paid\n"
    "(6) to check the due date of the book you have borrowed\n"
    "(7) to check your borrow history\n"
    "(8) to notify due Books\n"
    );
    return ;   
}
void displayuser(char* usrname)
{      
      printf("\n----------FUNCTION----DISPLAYING_PROFILE----------\n");
      FILE* fptr = fopen("user.txt" , "r");
      char* line = (char*) malloc(100*sizeof(char));
      while( fgets(line , 100 , fptr) != NULL)
      {  
         char* temp = strtok(line,",");
         if( strcmp( temp , usrname) == 0)
         {
              temp = strtok(NULL , ",");
              temp = strtok(NULL , ",");
              int books = atoi(temp);
              temp = strtok(NULL , "\n");
              int fine = atoi(temp);
              printf("Usrname :  %s\n" , usrname );
              printf("No.of Books issued : %d\n" , books );
              printf("Total_fine : %d\n", fine );
              if( books != 0)
              {
                  printf("%-15s     %-15s\n" , "Book_Name" ,"Issued_Date");
                  while( books != 0)
                  {
                     fgets(line , 100, fptr);
                     temp = strtok(line , ",");
                     temp = strtok(NULL , ",");
                     printf("%-15s     %-15s\n", temp , strtok(NULL, ","));
                     books --;
                  }
                  break;
              }
              else 
              {
                  printf("NO BOOk IS ISSSUED\n"); 
              }
         }
      }    
      fclose(fptr);
      return ; 
}
void checkAvailability()
{
    printf("----------FUNCTION-------CHECKING_AVAILABILITY---------\n");
    char book_name[50];
    printf("Enter the book name : \n");
    char help;
    scanf("%c", &help);
    fgets(book_name , 50 , stdin );
    book_name[strlen(book_name) -1 ] = '\0' ;
    FILE* fptr = fopen("books.txt", "r");
    char* line = (char*) malloc ( 100* sizeof(char));
    int found =0;
    int copies = 0;
    while( fgets( line , 100 , fptr ) != NULL )
    {
          char* temp = strtok(line , ","); 
          temp = strtok(NULL , ",");
          if( strcmp(temp , book_name ) == 0 )
          {
              found = 1; 
              temp = strtok(NULL ,",");
              temp = strtok(NULL , ",");
              temp = strtok(NULL , "\n");
              copies = atoi( temp); 
              break;
          } 
    }
    if( found == 0)
    {
         printf("The book named %s is not available in the library\n" , book_name );
    }
    else if( copies == 0 )
    {
        printf("No book is available , all the copies are issued\n");
    }
    else 
    {
        printf("The book is available\n"); 
    }
    free(line);
    return ; 

}

void issueBook(char* usrname )
{   time_t t;
    time(&t);
    struct tm* current = localtime(&t); 
    printf("\n-----------FUNCTION------ISSUE_BOOK--------\n");
    char book_name[50];
    printf("Enter the book name : ");
    char help;
    scanf("%c", &help );
    fgets( book_name , 50 , stdin ); 
    book_name[strlen(book_name) - 1 ] ='\0';
    FILE* fin= fopen("books.txt","r");
    int found =0;
    int canissue=1;
    FILE* f1 = fopen("user.txt", "r");
    FILE* f2 = fopen("write.txt" , "w");
    int availability=0;
    char* line = (char*) malloc ( 100* sizeof(char));
    FILE* fout = fopen("new.txt" , "w" );
    while( fgets(line , 100, f1 ) != NULL )
    {  
       char* temp = strtok(line , ",");
       if( strcmp(temp , usrname ) == 0)
       {
           char* password = strtok( NULL , ",");
           int books_issued = atoi(strtok(NULL , ","));
           int fine = atoi(strtok(NULL , ","));
           if( books_issued >=5 )
           {
               printf("You have recahed the issue Limit. Please first mind returning the books already taken\n");
               canissue =0;
               break;
           }
           else
           {
             fprintf(f2 , "%s,%s,%d,%d\n", temp ,password , books_issued+1 , fine );
           }
           while( books_issued )
           {
               fgets(line , 100 , f1 );
               fprintf(f2 , "%s", line );
               books_issued --;
           }
           break;
       } 
       else 
       {
           fprintf( f2 , "%s," , temp);
           temp = strtok(NULL , "\n");
           fprintf(f2 , "%s\n", temp);
       }

    }
    if(canissue != 0)
{
    while( fgets(line, 100 , fin  ) != NULL )
    {
        char* temp = strtok( line , ",");
        fprintf(fout , "%s," , temp);
        temp = strtok(NULL , ",");
        if( strcmp(temp , book_name)==0 )
        {   found = 1;
             char*  author_name = strtok( NULL , "," );
             int copies  = atoi(strtok( NULL , ","));
             int available = atoi( strtok(NULL , "\n"));
             if( available != 0)
             {
                  availability = 1;
                  available = available - 1;
                 
             }
              fprintf(fout , "%s,%s,%d,%d\n" , temp , author_name , copies, available );
             
        }
        else 
        {
           fprintf(fout , "%s,", temp );
           temp = strtok(NULL , "\n");
           fprintf(fout,"%s\n" , temp );
        }
    }
    if( found == 0)
    {
        printf("The book is not available in the library\n");
    }
    else if( !availability )
    {
        printf("The copies of the book are not available\n");
    }
    else 
    {
        printf("The Book is issued\n");
    }
}
    fclose(fin);
    fclose(fout);
if ( canissue != 0)
   {
     system("rm books.txt");
     system("mv new.txt books.txt");
   }
if(found == 1 && availability && canissue )
{   
    fprintf(f2,"%s,%s,%02d-%02d-%04d,,%d\n" ,usrname,book_name,current->tm_mday,current->tm_mon+1 , current->tm_year + 1900 , 0);
    while( fgets(line , 100 , f1) != NULL )
    {
        fprintf( f2 , "%s", line ); 
    }   

}
fclose(f1);
fclose(f2);
if( found == 1 && availability && canissue )
{
     system("rm user.txt");
     system("mv write.txt user.txt");
}
free(line);
return ; 

}

void returnBook(char* usrname )
{
    time_t t;
    time(&t);
    struct tm* current = localtime(&t);
    printf("\n----------FUNCION--------RETURN_BOOK--------\n");
    char book_name[50];
    printf("Enter the book name : ");
    char help;
    int fine;
    int late_fine=0;
    scanf("%c", &help);
    fgets(book_name , 50 , stdin);
    book_name[strlen(book_name) - 1 ] = '\0' ;
    FILE* fin = fopen("books.txt" , "r" );
    int found = 0;
    int issued = 0;
    FILE* f1 = fopen("user.txt" , "r");
    FILE* f2 = fopen("write.txt" , "w");
    char* line = (char*) malloc(100*sizeof(char));
    FILE* fout = fopen("new.txt" , "w" );
    while( fgets(line , 100 , f1 ) != NULL )
    {
        char* temp = strtok(line , ",");
          if( strcmp(temp , usrname ) == 0)
       {
           char* password = strtok( NULL , ",");
           int books_issued = atoi(strtok(NULL , ","));
           fine = atoi(strtok(NULL , ","));
           fprintf(f2, "%s,%s,%d,%d\n" , temp, password , books_issued , fine);
           while( books_issued )
           {
               fgets(line , 100 , f1 );
               char* temp = strtok(line , ",");
               temp = strtok(NULL , ",");
               if( strcmp( temp , book_name ) == 0)
               {
                   fprintf(f2 , "%s,%s," , usrname , book_name );
                   int issue_date , issue_month , return_date, return_month;
                   int fine=0;
                   issue_date = atoi(strtok(NULL,"-"));
                   issue_month = atoi(strtok(NULL,"-"));
                   int issue_year = atoi(strtok(NULL , ","));
                   return_date = current->tm_mday ;
                   return_month = current->tm_mon+ 1;
                   int return_year = current->tm_year + 1900;
                   int days = (return_year - issue_year)*356 + (return_month - issue_month)*30 + (return_date - issue_date)*1;
                   late_fine = (days -7 )*5 ;
                   if( late_fine <0) late_fine =0;
                   fprintf( f2 ,"%02d-%02d-%04d,%02d-%02d-%04d,%d\n" , issue_date , issue_month,issue_year , return_date , return_month , return_year, late_fine );
                   found =1;
               }
               else 
               {  char* work = strtok(NULL , "\n");
                  fprintf(f2 , "%s,%s,%s\n" , usrname , temp , work );
               }
               books_issued --;
           }
       } 
       else 
       {
           fprintf( f2 , "%s," , temp);
           temp = strtok(NULL , "\n");
           fprintf(f2 , "%s\n", temp);
       }

    }
    if( found == 1 )
    {
        printf("The book is returned succesfully\n");
        if(late_fine != 0)
        {  
            printf("The fine for the late return of the book is %d\n" , late_fine);   
        }
        else 
        {
            printf("Thanks for returning the Book\n");
            printf("There is no fine for you.You have returned the book in time\n");
        }
        printf("The loop has started\n");
        while( fgets( line , 100 , fin) != NULL)
         {   
            char* temp1= strtok(line , "," );
            char* temp = strtok(NULL , ",");
            if( strcmp(temp , book_name ) == 0)
            {   char* author_name = strtok(NULL ,",");
                int copies = atoi(strtok(NULL , ","));
                int available = atoi(strtok(NULL , "\n"));
                available = available + 1 ; 
                fprintf( fout ,"%s,%s,%s,%d,%d\n" , temp1 , temp ,author_name, copies , available );
                
            }
            else 
            {  
                char* author_name = strtok(NULL ,",");
                int copies = atoi(strtok(NULL , ","));
                int available = atoi(strtok(NULL , "\n"));
                fprintf( fout ,"%s,%s,%s,%d,%d\n" , temp1 , temp ,author_name, copies , available );
            }
            
        }
        fclose(fin);
        fclose(fout);
        fclose(f1);
        fclose(f2);
        system("rm books.txt");
        system("mv new.txt books.txt");
        system("rm user.txt");
        system("mv write.txt user.txt");
        return ; 
    }
    else 
    {
        fclose(fin);
        fclose(fout);
        fclose(f1);
        fclose(f2);
        system("rm new.txt");
        system("rm write.txt");
        printf("There is no Book found with that name\n");
    }
    
    return ; 

}
