                                                                      Mini Library Management Project

# Mini Library Management Project

This is a simple Library Management System implemented in C. It supports basic functionalities for managing books, users, and admin operations.

## Admin Credentials

Use the following credentials to log in as an admin:

- **Username:** CS25B087
- **Password:** CS1234

## Features

- Separate roles for Admin and Users
- Book management (issue, return, and availability tracking)
- Simple terminal-based interface

## Requirements

- C Compiler (e.g., GCC)
- ncurses library (required for the UI)

## Running on Linux

The provided Makefile works directly on Linux.

### Steps

1. Open a terminal in the project directory.
2. Run the following command:

   ```bash
   make
3. Execute the program : 

   ```bash
   ./a.out

4. To remove all the .o files created run the following command :
  
    ```bash  
    make clean

### Running on Windows

You need to install the ncurses library manually.

### Steps:

1. Install a compatible environment like: MinGW or WSL

2. Download and set up ncurses

3. Compile the code using gcc with ncurses linked:
  
   ```bash
   gcc main.c user.c admin.c -lncurses

### Note :

  Ensure ncurses is properly installed, otherwise the program will not run.

The project is designed primarily for Linux environments.
