# MyShell Project

This project is a simple shell implementation for the Operating Systems course.

## Structure

- **include/**: Contains header files.
  - `functions.h`: Declarations for all functions.

- **src/**: Contains source files.
  - `main.c`: Main program file.
  - `welcome.c`: Prints the welcome message.
  - `getLocation.c`: Prints the current working directory.
  - `splitArgument.c`: Splits a string into an array of words.
  - `logout.c`: Logs out from the shell.
  - `cd.c`: Changes the current working directory.
  - `cp.c`: Copies a file.
  - `delete.c`: Deletes a file.
  - `mypipe.c`: Executes two commands with a pipe.
  - `move.c`: Moves (renames) a file.
  - `echoppend.c`: Appends a string to a file.
  - `echorite.c`: Overwrites a file with a string.
  - `read.c`: Reads and prints the contents of a file.
  - `wordCount.c`: Counts the words in a file.

- **Makefile**: Builds the project.
- **README.md**: This file.
- Sample files for testing: `source.txt`, `destination.txt`, `oldname.txt`, `newname.txt`, `file.txt`.

## Building the Project

To build the project, run:

```sh
make

To run the project, use:
./main

To clean the build files, run:
make clean
# Operating-Systems-pro
