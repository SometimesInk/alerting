#include "config.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int interpolation_degree = 1;
char *segment_header;
char *segment_repeated;
char *segment_footer;

int parse_kvp(char *key, int value) {
  // Check for NULL
  if (key == NULL) {
    return -ERROR_NULL_POINTER;
  }

  // Assign variable to its correct value
  if (strcmp(key, "interpolation_degree") == 0) {
    interpolation_degree = value;
    return EXIT_SUCCESS;
  }

  // Check if line is a segment
  if (key[0] == '%' && strlen(key) > 1) {
    memmove(key, key + 2, strlen(key));
    if (key[1] == 'h') {
      // Reallocate memory for the old segment_header, the new line to append, a
      // new line and a null terminating character
      segment_header = (char *)realloc(
          segment_header,
          sizeof(char) * (strlen(segment_header) + strlen(key) + 2));

      // Move line at the end of segment_header
      memmove(segment_header + strlen(segment_header), key, strlen(key));

      // Add new line and ensure null termination
      segment_header[strlen(segment_header) - 2] = '\n';
      segment_header[strlen(segment_header) - 1] = '\0';
    } else if (key[1] == 'r') {
      // Parse repeated segment
    } else if (key[1] == 'f') {
      // Parse footer
    }
  }

  return 0;
}
