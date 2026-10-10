#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdbool.h>
#include <stddef.h>

/* Prints a centred title between two rulers. */
void console_banner(const char *title);

/* Prints a numbered menu (1..count) plus "0. exit_label" and returns the
   validated choice, 0..count. */
int console_menu(const char *title, const char *const options[],
                 int count, const char *exit_label);

/* The functions below keep asking until the input is valid.
   If the input stream ends (EOF) the program exits cleanly. */
void  console_text(const char *prompt, char *dest, size_t size);
int   console_int(const char *prompt, int min, int max);
float console_float(const char *prompt, float min, float max);

/* Case-insensitive equality of two strings. */
bool str_equal_nocase(const char *a, const char *b);

#endif
