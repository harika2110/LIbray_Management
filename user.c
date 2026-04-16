#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<time.h>
#include "fun.h"
int isLeap(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return 1;
    return 0;
}

int daysInMonth(int month, int year) {
    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (month == 2 && isLeap(year))
        return 29;

    return days[month - 1];
}

int totalDays(int d, int m, int y) {
    int days = d;

    for (int i = 1; i < m; i++) {
        days += daysInMonth(i, y);
    }

    for (int i = 0; i < y; i++) {
        days += isLeap(i) ? 366 : 365;
    }

    return days;
}
int checkuser( FILE* fptr , char* name, unsigned long hash ) 
{ 
    char line[200];
    int found=0;
    while( fgets( line , 200 , fptr) != NULL )
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
     char* line = (char*)malloc( 200*sizeof(char) );
     int found =0;
     while(fgets(line , 200, fptr ) != NULL)
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
    printf("\nEnter-----\n"
    "(1) to display your user profile\n"
    "(2) to display_available_books\n"
    "(3) to check the Availability of a Book\n"
    "(4) to issue a Book\n"
    "(5) to return a Book\n" 
    "(6) to renew a book\n"
    "(7) to display the due books\n"
    "(8) to logout\n"
    );
    return ;   
}
void displayuser(char* usrname)
{      
      printf("\n----------FUNCTION----DISPLAYING_PROFILE----------\n");
      FILE* fptr = fopen("user.txt" , "r");
      char* line = (char*) malloc(200*sizeof(char));
      while( fgets(line , 200 , fptr) != NULL)
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
              printf("Total_fine to be paid : %d\n\n", fine );
              printf("---------------DISPLAYING THE BOOKS HISTORY--------------\n");
              if( books != 0)
              {
                  printf("%-50s     %-40s     %-10s     %-10s\n" , "Book_Name" ,"Issued_Date" , "Return_Date" , "FINE");
                  while( books != 0)
                  {
                     fgets(line , 100, fptr);
                     temp = strtok(line , ",");
                     temp = strtok(NULL , ",");
                     char* issue_date = strtok(NULL,",");
                     char* return_date = strtok(NULL,",");
                     int p_fine = atoi(strtok(NULL,"\n"));
                     if( strcmp(return_date , " " ) == 0)
                    {  
                        printf("%-50s     %-40s     %-10s     %-10d\n",  temp , issue_date , "-" ,p_fine); }
                    else 
                    { 
                        printf("%-50s     %-40s     %-10s     %-10d\n", temp , issue_date , return_date , p_fine);
                    }
                      books --;
                  }
                  break;
              }
              else 
              {
                  printf("NO BOOK IS ISSSUED\n"); 
              }
         }
      }    
      free(line);
      fclose(fptr);
      return ; 
}
void checkAvailability()
{
    printf("----------FUNCTION-------CHECKING_AVAILABILITY---------\n");
    char book_name[20];
    char* line = (char*) malloc ( 100* sizeof(char));
    label :
    printf("Enter the book name : \n");
    char help;
    scanf("%c", &help);
    fgets(book_name , 20 , stdin );
    book_name[strlen(book_name) -1 ] = '\0' ;
    FILE* fptr = fopen("books.txt", "r"); 
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
    printf("Do you want to check the availability of any other book [y/n] ? ");
    scanf(" %c",&help);
    if( help == 'y')
    {
        goto label;
    }
    free(line);
    fclose(fptr);
    return ; 

}

void issueBook(char* usrname )
{   time_t t;
    time(&t);
    struct tm* current = localtime(&t); 
    printf("\n-----------FUNCTION------ISSUE_BOOK--------\n");
    char* line = (char*) malloc ( 200* sizeof(char));
    char book_name[50];
    label : 
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
    FILE* fout = fopen("new.txt" , "w" );
    while( fgets(line , 100, f1 ) != NULL )
    {  
       char* temp = strtok(line , ",");
       if( strcmp(temp , usrname ) == 0)
       {
           char* password = strtok( NULL , ",");
           int books_issued = atoi(strtok(NULL , ","));
           int fine = atoi(strtok(NULL , ","));
           
           
             fprintf(f2 , "%s,%s,%d,%d\n", temp ,password , books_issued+1 , fine );
           
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
    while( fgets(line, 200 , fin  ) != NULL )
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
    fprintf(f2,"%s,%s,%02d-%02d-%04d, ,%d\n" ,usrname,book_name,current->tm_mday,current->tm_mon+1 , current->tm_year + 1900 , 0);
    while( fgets(line , 200 , f1) != NULL )
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
printf("Do you want to take any other book [y/n] ? ");
scanf(" %c" , &help );
if(help == 'y')
{
    goto label;
}
free(line);
return ; 

}

void returnBook(char* usrname )
{
    time_t t;
    time(&t);
    struct tm* current = localtime(&t);
    char* line = (char*) malloc(200*sizeof(char));
    printf("\n----------FUNCION--------RETURN_BOOK--------\n");
    char book_name[50];
    label : 
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
               fgets(line , 200 , f1 );
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
                   int days = totalDays( return_date , return_month , return_year) - totalDays(issue_date , issue_month , issue_year);
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
    printf("Do you want to return any other book [y/n] ? ");
    scanf(" %c" , &help);
    if( help == 'y')
    {
        goto label ; 
    }
    free(line);
    
    return ; 

}
void updateuserprofile(char* usrname )
{    time_t t;
    time(&t);
    struct tm* current = localtime(&t);
    FILE* fptr = fopen("user.txt" , "r" );
    int total_fine =0;
    int books_taken;
    char* line = (char*)malloc(100*sizeof(char*));
    while( fgets(line, 100 , fptr ) != NULL )
    {    
          char* temp= strtok(line , ",");
          if( strcmp(temp , usrname) == 0 )
          {   
              temp = strtok(NULL,",");  //password 
              books_taken = atoi(strtok(NULL,",")); //books_taken 
              int i=books_taken;

              while(i )
              {  fgets(line , 100 , fptr );
                 char* temp = strtok(line, ",");  //usrname
                 temp = strtok(NULL,",");  //book_name 
                 char* issue_date = strtok(NULL,",");  //issue_date 
                 char* return_date = strtok(NULL,",");  //return_date
                 if( strcmp(return_date , " ") != 0  )
                 {
                     total_fine += atoi(strtok(NULL,"\n"));   // adding_fine 
                 } 
                 else 
                 {
                      int i_date = atoi(strtok( issue_date , "-"));
                      int i_month =atoi( strtok( NULL , "-"));
                      int i_year = atoi(strtok(NULL , "\0")); 
                      int p_date =  current->tm_mday;
                      int p_month = current->tm_mon+1;
                      int p_year =  current->tm_year + 1900;
                      int late_fine = totalDays(p_date , p_month , p_year) - totalDays(i_date , i_month , i_year);
                      late_fine = (late_fine - 7)* 5;
                      if( late_fine  > 0)
                      {  
                         total_fine += late_fine ;
                      }

                 }
                 i --;

              }
            

          }
          

    }
     rewind(fptr);
     FILE* fout = fopen("write.txt" , "w");
     while( fgets(line , 200  , fptr ) != NULL  )
     {
        char* temp = strtok(line , ",");
        if( strcmp(temp , usrname ) ==0 )
        {
            temp = strtok(NULL , ","); //password
            fprintf( fout , "%s,%s,%d,%d\n" , usrname , temp , books_taken , total_fine );
             while(books_taken )
              {  fgets(line , 200 , fptr );
                 char* temp = strtok(line, ",");  //username 
                 temp = strtok(NULL,",");  //book_name
                 char* issue_date = strtok(NULL,",");  
                 char* return_date = strtok(NULL,",");
                 char* fine_paid = strtok(NULL,"\n");
                 if( strcmp(return_date , " ") != 0   )
                 {
                    fprintf(fout , "%s,%s,%s,%s,%s\n", usrname , temp , issue_date , return_date , fine_paid);
                 } 
                 else 
                 {
                      int i_date = atoi(strtok( issue_date , "-"));
                      int i_month = atoi(strtok( NULL , "-"));
                      int i_year = atoi(strtok(NULL , "\0"));
                      int p_date =  current->tm_mday;
                      int p_month = current->tm_mon+1;
                      int p_year =  current->tm_year + 1900;
                      int late_fine = totalDays(p_date , p_month , p_year) - totalDays(i_date , i_month , i_year);
                      late_fine = (late_fine - 7)* 5;
                      if( late_fine  < 0)
                      {
                         late_fine =0;
                      }
                      fprintf(fout ,"%s,%s,%02d-%02d-%04d, ,%d\n" , usrname , temp , i_date , i_month,i_year , late_fine);

                 }
            
                 books_taken --;

              }
          }
          else 
          {
              fprintf( fout , "%s," , temp);
              temp = strtok(NULL , "\n");
              fprintf( fout , "%s\n", temp );
          }

     }
     fclose(fptr);
     fclose(fout);
     system("rm user.txt");
     system("mv write.txt user.txt");
     free(line);
     return ; 
}

void display_available_books(){
    char* line = (char*)malloc(200*sizeof(char));
    FILE* fptr = fopen("books.txt", "r");
    printf("----------------PRINTING_AVAILABLE_BOOKS----------------\n");
    int book=0;
    while(fgets(line , 200 , fptr )!= NULL )
    {   char* temp = strtok(line , ",");
        char* book_name = strtok(NULL , ",");
        char* author_name = strtok(NULL , ",");
        char* copies = strtok(NULL , ",");
        char* available = strtok(NULL,"\n" );
        if( strcmp( copies , "0") != 0)
        {   book++;
            if(book == 1 )
            {
                 printf("%-50s     %-40s\n" , "BOOK_NAME" , "AUTHOR_NAME ");
            }
            printf("%-50s     %-40s\n" , book_name , author_name);  
        }
    }
    if( book == 0)
    {
        printf("No Books are available\n");
    }
    free(line);
    fclose(fptr);
}
void renewBook(char* usrname )
{   printf("------------FUNCTION--------RENEW_BOOK-------------\n");
    char help;
    char* line = (char*)malloc(200*sizeof(char));
    label :
    scanf("%c", &help);
    time_t t;
    time(&t);
    struct tm* current = localtime(&t); 
    printf("Please enter the Book_name : ");
    char book_name[50];
    fgets(book_name , 50 , stdin );
    book_name[strlen(book_name) - 1] = '\0' ;
    int found =0;
    FILE* fptr = fopen("user.txt" , "r");
    FILE* fout = fopen("write.txt" , "w");
    while( fgets( line , 200 , fptr  ) != NULL )
    {
          char* temp = strtok(line , "," );
          char* book = strtok( NULL , ",");
          if( strcmp(temp , usrname) == 0  && strcmp(book, book_name) ==0 )
          {    found = 1;
               fprintf(fout,"%s,%s,%02d-%02d-%04d, ,0\n" , temp , book ,current->tm_mday , current->tm_mon+1 , current->tm_year + 1900 );
          }
          else 
          {
               fprintf(fout,"%s,%s,%s\n" , temp , book , strtok(NULL , "\n"));
          }
    }
    if( found != 1 )
    {
        printf("No Book with that name is issued to you\n");

    }
    else 
    {
        printf("The Book is renewed successfully\n");
    }
   
    fclose(fptr);
    fclose(fout);
    system("rm user.txt");
    system("mv write.txt user.txt");
    printf("Do you want to renew any other Book [y/n] ? ");
    scanf(" %c", &help);
    if( help == 'y')
    {
        goto label;
    }
    
    free(line);
}
void displayDueBooks(char* usrname)
{   printf("--------------FUNCTION--------DISPLAYING_DUE_BOOKS-------\n");
    FILE* fptr = fopen("user.txt","r");
    int value =0;
    char* line = (char*) malloc(200*sizeof(char));
    while( fgets(line , 200 , fptr) !=NULL)
    {
        char* temp = strtok(line  , ",");
        char* passowrd = strtok(NULL , ",");
        int books_taken = atoi(strtok(NULL , ","));
        if( strcmp( temp , usrname ) == 0)
       {   while( books_taken)
        {
            fgets(line , 200 , fptr );
            temp = strtok(line , ",");//usrname 
            char* book = strtok(NULL , ",");
            char* issue_day = strtok(NULL , ",");  //issue_date
            temp = strtok(NULL , ",");  //return_date 
            int fine  = atoi(strtok(NULL , "\n"));  //fine
        //    printf("The return date is %s and fine is %d\n", temp , fine );
            if( strcmp(temp , " ") == 0   )
            {
                if(value == 0)
                {
                    printf("%-50s     %s     %-15s\n" ,"BOOK_NAME" , "ISSUE_DATE" , "DUE_DATE");
                }

                    int issue_date =  atoi(strtok(issue_day , "-") );  
                    int issue_month = atoi(strtok(NULL , "-"));
                    int issue_year = atoi(strtok(NULL , "\n"));
                int carry = 0;
                int return_date , return_month , return_year; 
                if( return_month % 2 !=0  )
               { 
                      if( issue_date + 7 + carry > 31)
                      { 
                         return_date = issue_date + 7 - 31;
                        carry = 1;
                    
                      }
                 else {   return_date = issue_date + 7 ;   carry=0;}
               }
               else if( return_month != 2 )
               {
                     if(  isLeap(issue_year)  )
                     {
                          if( issue_date + 7 + carry > 29 )
                          {
                             return_date = issue_date + 7 - 29 ;
                             carry = 1;
                          }
                          else 
                          {
                              return_date = issue_date + 7 ;   carry=0;       
                          }
                     } 
                     else 
                     {
                          if( issue_date + 7 + carry > 28 )
                          {
                             return_date = issue_date + 7 - 28 ;
                             carry = 1;
                          }
                          else 
                          {
                              return_date = issue_date + 7 ;   carry=0;       
                          }
                     }

               }
               else 
               {
                   if( issue_date + 7 + carry > 30)
                      { 
                         return_date = issue_date + 7 - 30;
                        carry = 1;
                    
                      }
                 else {   return_date = issue_date + 7 ;   carry=0;}
                  

               }
                if( issue_month + carry > 12 )
                {
                    return_month = issue_month + 1 - 12;
                    carry = 1;
                }
                else { return_month = issue_month + carry ;    carry=0;}
                return_year = issue_year + carry ; 
                printf("%-50s     %02d-%02d-%04d     %02d-%02d-%04d\n" , book , issue_date , issue_month , issue_year , return_date , return_month, return_year);
                value ++;

            }
            books_taken --;

        }
        break ; 
    }
}
    if(value == 0)
    {
        printf("There are no due books\n"); 
    }
    fclose(fptr);
    free(line);
    return ; 
}