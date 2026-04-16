                                                                      Mini Library Management Project

This is a simple Library Management System implemented in C.
It supports basic functionalities for managing books, users, and admin operations.

Admin Credentials :
Use the following credentials to log in as an admin:
Username: CS25B087
Password: CS1234


Features :
Separate roles for Admin and Users
Book management (issue, return, availability tracking)
Simple terminal-based interface

Requirements :
C Compiler (e.g., gcc)
ncurses library (required for UI)

Running on Linux :
The provided Makefile works directly on Linux.
Steps:
1.Open terminal in the project directory
2.Run:
  make
3.Execute the program:
./a.out

Running on Windows
You need to install the ncurses library manually.
Steps:
1.Install a compatible environment like: MinGW or WSL
2.Download and set up ncurses
3.Compile the code using gcc with ncurses linked:
   gcc your_file.c -lncurses

Note :
Ensure ncurses is properly installed, otherwise the program will not run.
The project is designed primarily for Linux environments.
