#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "functions.h"

// פונקציה לספירת מילים בקובץ
void wordCount(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "wordCount: expected file argument\n");
        return;
    }

    int fd = open(args[1], O_RDONLY);
    if (fd == -1) {
        perror("wordCount: open file");
        return;
    }

    char buffer[1024];
    ssize_t bytesRead;
    int wordCount = 0;
    int inWord = 0;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < bytesRead; i++) {
            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
                inWord = 0;
            } else if (!inWord) {
                inWord = 1;
                wordCount++;
            }
        }
    }

    if (bytesRead == -1) {
        perror("wordCount: read file");
    } else {
        printf("Word count: %d\n", wordCount);
    }

    close(fd);
}
