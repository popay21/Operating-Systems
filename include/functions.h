#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void welcome();
void getLocation();
char **splitArgument(char *str);
void logout(char *str);
void cd(char **args);
void cp(char **args);
void delete(char *str);
void mypipe(char **argv1, char **argv2);
void move(char **args);
void echoppend(char **args);
void echorite(char **args);
void readFile(char **args);
void wordCount(char **args);

#endif // FUNCTIONS_H
