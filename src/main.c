#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
    welcome();     // קריאה לפונקציה שמדפיסה את הודעת הפתיחה
    getLocation(); // קריאה לפונקציה שמדפיסה את המיקום הנוכחי

    // בדיקת פונקציה לפיצול מחרוזת
    char str[] = "cd OneDrive - Ariel University";
    char **args = splitArgument(str);
    for (int i = 0; args[i] != NULL; i++)
    {
        printf("args[%d]: %s\n", i, args[i]);
    }

    // בדיקת פונקציית logout
    logout("Goodbye!");

    // בדיקת פונקציית cd
    char *cdArgs[] = {"cd", "/tmp", NULL};
    cd(cdArgs);

    // בדיקת פונקציית cp
    char *cpArgs[] = {"cp", "source.txt", "destination.txt", NULL};
    cp(cpArgs);

    // בדיקת פונקציית delete
    delete ("destination.txt");

    // בדיקת פונקציית mypipe
    char *mypipeArgs1[] = {"ls", "-l", NULL};
    char *mypipeArgs2[] = {"grep", ".c", NULL};
    mypipe(mypipeArgs1, mypipeArgs2);

    // בדיקת פונקציית move
    char *moveArgs[] = {"move", "oldname.txt", "newname.txt", NULL};
    move(moveArgs);

    // בדיקת פונקציית echoppend
    char *echoppendArgs[] = {"echoppend", "Hello, World!", "file.txt", NULL};
    echoppend(echoppendArgs);

    // בדיקת פונקציית echorite
    char *echoriteArgs[] = {"echorite", "Overwritten content", "file.txt", NULL};
    echorite(echoriteArgs);

    // בדיקת פונקציית readFile
    char *readArgs[] = {"read", "file.txt", NULL};
    readFile(readArgs);

    // בדיקת פונקציית wordCount
    char *wordCountArgs[] = {"wordCount", "file.txt", NULL};
    wordCount(wordCountArgs);

    free(args);  // שחרור הזיכרון המוקצה
    return 0;
}
