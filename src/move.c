#include <stdio.h>
#include <unistd.h>
#include "functions.h"

// פונקציה להעברת (שינוי שם) קובץ
void move(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "move: expected source and destination arguments\n");
        return;
    }

    if (rename(args[1], args[2]) != 0) {
        perror("move");
    } else {
        printf("Moved %s to %s successfully\n", args[1], args[2]);
    }
}
