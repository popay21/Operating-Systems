#include <stdio.h>
#include <unistd.h>
#include "functions.h"

// פונקציה לשינוי ספריית העבודה הנוכחית
void cd(char **args) {
    // אם לא סופק פרמטר, הדפס הודעת שגיאה
    if (args[1] == NULL) {
        fprintf(stderr, "cd: expected argument to \"cd\"\n");
    } else {
        // שינוי הספרייה
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
}
