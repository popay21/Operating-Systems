#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

// פונקציה להתנתקות מה-shell
void logout(char *str) {
    // הדפסת הודעת התנתקות
    printf("Logout: %s\n", str);
    // סגירת התוכנית
    exit(0);
}
