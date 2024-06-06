# MyShellProject

## Description
This project implements a custom shell with various built-in commands.

## Structure

MyShellProject/
├── include/
│ ├── functions.h
├── src/
│ ├── functions.c
│ ├── main.c
├── build/
├── MyShellProject.sln


## Compilation
To compile the project, run the following command:
```sh
gcc -Iinclude -o build/myshell src/functions.c src/main.c

To run the shell, use: ./build/myshell

Built-in Commands
welcome: Prints a welcome message.
getLocation: Prints the current directory and user info.
splitArgument: Splits a string into arguments.
logout: Logs out of the shell.
cd: Changes the current directory.
cp: Copies a file.
delete: Deletes a file.
mypipe: Executes two commands with a pipe.
move: Moves a file.
echoppend: Appends a string to a file.
echorite: Overwrites a file with a string.
readFile: Reads and prints the contents of a file.
wordCount: Counts the words in a file.
