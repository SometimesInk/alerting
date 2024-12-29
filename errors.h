#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
  ERROR_ALLOCATION_FAILURE,
  ERROR_INVALID_ARGUMENT,
  ERROR_NULL_POINTER,
} Errors;

extern char *error_message(Errors e);

#endif
