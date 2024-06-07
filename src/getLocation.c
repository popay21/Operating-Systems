#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

// פונקציה לקבלת המיקום הנוכחי והדפסתו
void getLocation() {
    char cwd[1024];
    char *username = getenv("USER");
    char hostname[1024];

    gethostname(hostname, sizeof(hostname));
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("\033[1m%s@%s\033[0m:\033[1;34m%s\033[0m\n", username, hostname, cwd);
    } else {
        perror("getcwd() error");
    }
}
