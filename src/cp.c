#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "functions.h"

// פונקציה להעתקת קובץ ממקור ליעד
void cp(char **args) {
    int source_fd, dest_fd, n_read;
    char buffer[1024];

    // אם לא סופקו מספיק פרמטרים, הדפס הודעת שגיאה
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "cp: expected source and destination arguments\n");
        return;
    }

    // פתיחת קובץ המקור
    source_fd = open(args[1], O_RDONLY);
    if (source_fd == -1) {
        perror("cp: open source file");
        return;
    }

    // פתיחת/יצירת קובץ היעד
    dest_fd = open(args[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("cp: open destination file");
        close(source_fd);
        return;
    }

    // העתקת הנתונים ממקור ליעד
    while ((n_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, n_read) != n_read) {
            perror("cp: write to destination file");
            close(source_fd);
            close(dest_fd);
            return;
        }
    }

    if (n_read == -1) {
        perror("cp: read from source file");
    }

    // סגירת הקבצים
    close(source_fd);
    close(dest_fd);
}
