#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "functions.h"

// פונקציה לקריאת תוכן הקובץ והדפסתו
void readFile(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "read: expected file argument\n");
        return;
    }

    int fd = open(args[1], O_RDONLY);
    if (fd == -1) {
        perror("read: open file");
        return;
    }

    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) == -1) {
            perror("read: write to stdout");
            close(fd);
            return;
        }
    }

    if (bytesRead == -1) {
        perror("read: read file");
    }

    close(fd);
}
