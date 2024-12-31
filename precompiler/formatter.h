#ifndef FORMATTER_H
#define FORMATTER_H

extern char *format(char *string, char *key, char *value);

/// If hexadecimals is 0, base 10 is assumed
extern void integer_as_string(char **output, int number, int hex);

extern void ensure_two_digits(char **hex);

#endif
