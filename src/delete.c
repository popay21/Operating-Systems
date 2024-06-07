#include <stdio.h>
#include <unistd.h>
#include "functions.h"

// פונקציה למחיקת קובץ
void delete(char *str) {
    if (unlink(str) == 0) {
        printf("Deleted %s successfully\n", str);
    } else {
        perror("delete");
    }
}
