#include "errors.h"

char *error_message(Errors e) {
  switch (e) {
  case ERROR_ALLOCATION_FAILURE:
    return "Failed to allocate memory.";
  case ERROR_INVALID_ARGUMENT:
    return "Invalid argument.";
  case ERROR_NULL_POINTER:
    return "Value is NULL";
  default:
    return error_message(ERROR_INVALID_ARGUMENT);
  }
}
