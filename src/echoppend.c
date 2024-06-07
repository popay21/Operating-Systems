#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

// פונקציה להוספת מחרוזת לקובץ
void echoppend(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "echoppend: expected string and file arguments\n");
        return;
    }

    // פתיחת הקובץ במצב append
    int fd = open(args[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("echoppend: open file");
        return;
    }

    // כתיבת המחרוזת לקובץ
    if (write(fd, args[1], strlen(args[1])) == -1) {
        perror("echoppend: write to file");
    } else {
        printf("Appended \"%s\" to %s successfully\n", args[1], args[2]);
    }

    // סגירת הקובץ
    close(fd);
}
