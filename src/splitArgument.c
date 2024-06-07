#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// פונקציה לפיצול מחרוזת למערך של מילים
char **splitArgument(char *str) {
    int bufsize = 64;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "splitArgument: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(str, " ");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "splitArgument: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " ");
    }
    tokens[position] = NULL;
    return tokens;
}
