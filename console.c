#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"

#define BANNER_WIDTH 40
#define LINE_SIZE    128

/* Reads one full line from stdin into dest (without the newline).
   Anything that does not fit is discarded, so it cannot leak into the
   next prompt. */
static void fetch_line(char *dest, size_t size)
{
    if (fgets(dest, (int)size, stdin) == NULL) {
        printf("\nInput ended. Exiting program.\n");
        exit(0);
    }

    size_t len = strcspn(dest, "\n");
    if (dest[len] == '\n') {
        dest[len] = '\0';
    } else {
        int ch;                         /* line was longer than the buffer */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* throw the rest away */
        }
    }

    len = strlen(dest);
    if (len > 0 && dest[len - 1] == '\r') {
        dest[len - 1] = '\0';
    }
}

static void trim(char *s)
{
    size_t start = 0;
    while (isspace((unsigned char)s[start])) {
        start++;
    }
    size_t len = strlen(s + start);
    while (len > 0 && isspace((unsigned char)s[start + len - 1])) {
        len--;
    }
    memmove(s, s + start, len);
    s[len] = '\0';
}

void console_banner(const char *title)
{
    int pad = (BANNER_WIDTH - (int)strlen(title)) / 2;
    if (pad < 0) {
        pad = 0;
    }
    printf("\n========================================\n");
    printf("%*s%s\n", pad, "", title);
    printf("========================================\n");
}

int console_menu(const char *title, const char *const options[],
                 int count, const char *exit_label)
{
    console_banner(title);
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, options[i]);
    }
    printf("0. %s\n\n", exit_label);
    return console_int("Enter your choice: ", 0, count);
}

void console_text(const char *prompt, char *dest, size_t size)
{
    for (;;) {
        printf("%s", prompt);
        fetch_line(dest, size);
        trim(dest);
        if (dest[0] != '\0') {
            return;
        }
        printf("This field cannot be empty.\n");
    }
}

int console_int(const char *prompt, int min, int max)
{
    char line[LINE_SIZE];

    for (;;) {
        printf("%s", prompt);
        fetch_line(line, sizeof line);

        char *end;
        errno = 0;
        long value = strtol(line, &end, 10);
        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (end != line && *end == '\0' && errno == 0 &&
            value >= min && value <= max) {
            return (int)value;
        }

        if (max == INT_MAX) {
            printf("Please enter a whole number of at least %d.\n", min);
        } else {
            printf("Please enter a whole number from %d to %d.\n", min, max);
        }
    }
}

float console_float(const char *prompt, float min, float max)
{
    char line[LINE_SIZE];

    for (;;) {
        printf("%s", prompt);
        fetch_line(line, sizeof line);

        char *end;
        double value = strtod(line, &end);
        while (isspace((unsigned char)*end)) {
            end++;
        }

        /* Written as !(a && b) so that NaN is rejected as well. */
        if (end != line && *end == '\0' && value >= min && value <= max) {
            return (float)value;
        }
        printf("Please enter a number from %.2f to %.2f.\n", min, max);
    }
}

bool str_equal_nocase(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return false;
        }
        a++;
        b++;
    }
    return *a == *b;
}
