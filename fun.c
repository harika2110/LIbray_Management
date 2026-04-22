#include<stdio.h> 
#include<stdlib.h>
#include<string.h>  
#include<curses.h>
#include "fun.h"
void loginusrname( char* name )
{    char help;
     scanf("%c" , &help );
     printf("Enter Username : ");
     fgets( name , 50 , stdin );
     name[strlen(name) -1] = '\0' ; 
     return ; 
}
void loginpassword( char* password , char* password2 , int j)
{
    int ch, i = 0;
    int max_len = 50;
    //initscr();      // start curses mod
    //clear();        //clear the curses mode 
    noecho();       // do not show input
    cbreak();       // take input char by char
    addstr("Enter your password : "); 
    refresh();
    while (1)
    {
        ch = getch();
        // enter key
        if (ch == '\n')
        {
            break;
        }
        // backspace handling
        else if (ch == 127 || ch == KEY_BACKSPACE)
        {
            if (i > 0)
            {
                i--;
                password[i] = '\0';
            }
        }
        // Normal character input
        else if (i < max_len - 1)
        {
            password[i++] = ch;
            password[i] = '\0';
        }
    }
    if(j==2 )
    {   addstr("\n");
        addstr("Enter your password again : ");
        refresh();
        i=0;
         while (1)
      {
           ch = getch();
           // enter key
           if (ch == '\n')
            {
                 break;
            }
           // backspace  handling
           else if (ch == 127 || ch == KEY_BACKSPACE)
         {
               if (i > 0)
               {
                   i--;
                   password2[i] = '\0';
               }
           }
           // Normal character input
           else if (i < max_len - 1)
            {
                 password2[i++] = ch;
                 password2[i] = '\0';
            }
        }
        if( strcmp(password , password2) != 0)
        {
            addstr("Passwords don't match . Press enter and try entering again\n");
            ch = getch();
        }

    }
    // endwin();  
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
void clearing( char* str )
{
    while( *str )
    {
         *str = '\0' ; 
         str++; 
    }
    return ;
}
