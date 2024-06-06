#include <stdio.h>
#include "functions.h"

int main() {
    welcome();  // בדיקת פונקציית welcome
    getLocation();  // בדיקת פונקציית getLocation

    // בדיקת פונקציית splitArgument
    char str[] = "cd OneDrive - Ariel University";
    char **args = splitArgument(str);

    for (int i = 0; args[i] != NULL; i++) {
        printf("Argument[%d]: %s\n", i, args[i]);
    }

    // בדיקת פונקציית cd
    cd(args);

    // בדיקת פונקציית cp
    char *cpArgs[] = {"cp", "source.txt", "destination.txt", NULL};
    cp(cpArgs);

    // בדיקת פונקציית delete
    delete("destination.txt");

    // בדיקת פונקציית mypipe
    char *argv1[] = {"ls", "-l", NULL};
    char *argv2[] = {"grep", "test", NULL};
    mypipe(argv1, argv2);

    // בדיקת פונקציית move
    char *mvArgs[] = {"move", "source.txt", "new_destination.txt", NULL};
    move(mvArgs);

    // בדיקת פונקציית echoppend
    char *echoAppendArgs[] = {"echoppend", "Hello, World!", "output.txt", NULL};
    echoppend(echoAppendArgs);

    // בדיקת פונקציית echorite
    char *echoWriteArgs[] = {"echorite", "Hello, Universe!", "output.txt", NULL};
    echorite(echoWriteArgs);

    // בדיקת פונקציית readFile
    char *readArgs[] = {"read", "output.txt", NULL};
    readFile(readArgs);

    // בדיקת פונקציית wordCount
    char *wordCountArgs[] = {"wordCount", "output.txt", NULL};
    wordCount(wordCountArgs);

    free(args);  // שחרור הזיכרון המוקצה
    return 0;
}
