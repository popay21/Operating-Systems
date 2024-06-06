#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "functions.h"

// פונקציה להדפסת הודעת הפתיחה
void welcome() {
    printf("aSPY//YASa\n");
    printf("apyyyyCY//////////YCa       |\n");
    printf("sY//////YSpcs  scpCY//Pp     | Welcome to myShell\n");
    printf("ayp ayyyyyyySCP//Pp           syY//C    | Version 2.4.3\n");
    printf("AYAsAYYYYYYYY///Ps              cY//S   |\n");
    printf("pCCCCY//p          cSSps y//Y   | https://github.com/<user>\n");
    printf("SPPPP///a          pP///AC//Y   |\n");
    printf("A//A            cyP////C   | Have fun!\n");
    printf("p///Ac            sC///a   |\n");
    printf("P////YCpc           A//A   | Craft packets like it is your last\n");
    printf("scccccp///pSP///p          p//Y   | day on earth.\n");
    printf("sY/////////y  caa           S//P   |                      -- Lao-Tze\n");
    printf("cayCyayP//Ya              pY/Ya   |\n");
    printf("sY/PsY////YCc          aC//Yp\n");
    printf("sc  sccaCY//PCypaapyCP//YSs\n");
    printf("spCPY//////YPSps\n");
    printf("ccaacs\n");
}

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

// פונקציה להתנתקות מה-shell
void logout(char *str) {
    // הדפסת הודעת התנתקות
    printf("Logout: %s\n", str);
    // סגירת התוכנית
    exit(0);
}

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

// פונקציה למחיקת קובץ
void delete(char *str) {
    if (unlink(str) == 0) {
        printf("Deleted %s successfully\n", str);
    } else {
        perror("delete");
    }
}

// פונקציה לביצוע שתי פקודות עם pipe
void mypipe(char **argv1, char **argv2) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // תהליך הילד הראשון
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        execvp(argv1[0], argv1);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // תהליך הילד השני
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        execvp(argv2[0], argv2);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // תהליך האב
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

// פונקציה להעברת (שינוי שם) קובץ
void move(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "move: expected source and destination arguments\n");
        return;
    }

    if (rename(args[1], args[2]) != 0) {
        perror("move");
    } else {
        printf("Moved %s to %s successfully\n", args[1], args[2]);
    }
}

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

