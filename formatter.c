#include "formatter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void format(char **string, char *key, char *value) {
  // Find the length of the string, key, and value
  int string_length = strlen(*string);
  int key_length = strlen(key);
  int value_length = strlen(value);

  // Check if the key exists in the string
  char *found = strstr(*string, key);
  if (found == NULL) {
    return; // If key is not found, return without changes
  }

  // Calculate the new null-terminated size
  int new_size = string_length - key_length + value_length + 1;

  // Allocate memory for the new string
  char *result = (char *)malloc(new_size * sizeof(char));
  if (result == NULL) {
    // Handle memory allocation failure
    return;
  }

  // Copy the part of the string before the key
  int index = 0;
  while (*string + index != found) {
    result[index] = (*string)[index];
    index++;
  }

  // Copy the value in place of the key
  for (int i = 0; i < value_length; i++) {
    result[index++] = value[i];
  }

  // Copy the remaining part of the string after the key
  int remainingIndex = (found - *string) + key_length;
  while (remainingIndex < string_length) {
    result[index++] = (*string)[remainingIndex++];
  }

  // Null-terminate the result string
  result[index] = '\0';

  // Update the original string pointer
  free(*string); // Free the original string
  *string = result;
}

void integer_as_string(char **output, int number, int hex) {
  // Handle the special case for 0 explicitly
  if (number == 0) {
    *output = malloc(2 * sizeof(char)); // Allocate memory for "0"
    if (*output) {
      (*output)[0] = '0';
      (*output)[1] = '\0';
    }
    return;
  }

  // Calculate the length of the number string
  int length = snprintf(NULL, 0, "%d", number);

  // Allocate memory for the string
  *output = malloc((length + 1) * sizeof(char)); // Modify the caller's pointer
  if (!*output)
    return;

  // Convert the integer to string in base 10 or 16
  if (hex)
    snprintf(*output, length + 1, "%x", number);
  else
    snprintf(*output, length + 1, "%d", number);
}

void ensure_two_digits(char **hex) {
  // Ensure not NULL and null terminated
  if (hex && strlen(*hex) == 1) {
    // Shift the string by 1 to leave space for the leading 0
    size_t len = strlen(*hex);
    memmove(hex + 1, *hex, len + 1);
    *hex[0] = '0';
  }
}
