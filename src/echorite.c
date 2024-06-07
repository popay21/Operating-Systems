#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

// פונקציה להחלפת תוכן הקובץ במחרוזת
void echorite(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "echorite: expected string and file arguments\n");
        return;
    }

    // פתיחת הקובץ במצב כתיבה (יצירה אם לא קיים, מחיקה אם קיים)
    int fd = open(args[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("echorite: open file");
        return;
    }

    // כתיבת המחרוזת לקובץ
    if (write(fd, args[1], strlen(args[1])) == -1) {
        perror("echorite: write to file");
    } else {
        printf("Overwritten %s with \"%s\" successfully\n", args[2], args[1]);
    }

    // סגירת הקובץ
    close(fd);
}
