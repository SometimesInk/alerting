#include "config.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int config_interpolation_degree = 1;
int config_start_r = 111;
int config_start_g = 201;
int config_start_b = 141;
int config_end_r = 181;
int config_end_g = 4;
int config_end_b = 10;
int config_offset = 1;

char *segment_header = NULL;
size_t segment_header_length = 0;
char *segment_repeated = NULL;
size_t segment_repeated_length = 0;
char *segment_footer = NULL;
size_t segment_footer_length = 0;

int parse_section(char **section, size_t *length, char *line) {
  size_t line_length = strlen(line);

  // Remove marker
  line += 2;
  line_length -= 2;

  // Reallocate memory to accommodate the new line
  *section = realloc(*section, *length + line_length +
                                   2); // +2 for newline and null terminator
  if (*section == NULL) {
    return ERROR_NULL_POINTER;
  }

  // Append the line and a newline to the section
  memcpy(*section + *length, line, line_length);
  (*section)[*length + line_length] = '\n';     // Add newline character
  (*section)[*length + line_length + 1] = '\0'; // Null-terminate the string
  *length += line_length + 1;                   // Update the length

  return EXIT_SUCCESS;
}

int parse_kvp(char *line, char *key, int value) {
  // Check for NULL
  if (key == NULL) {
    return -ERROR_NULL_POINTER;
  }

  // Assign variable to its correct value
  if (strcmp(key, "config_interpolation_degree") == 0) {
    config_interpolation_degree = value;
    return EXIT_SUCCESS;
  } else if (strcmp(key, "config_start_r") == 0) {
    config_start_r = value;
    return EXIT_SUCCESS;
  } else if (strcmp(key, "config_start_g") == 0) {
    config_start_g = value;
    return EXIT_SUCCESS;
  } else if (strcmp(key, "config_start_b") == 0) {
    config_start_b = value;
    return EXIT_SUCCESS;
  } else if (strcmp(key, "config_end_r") == 0) {
    config_end_r = value;
    return EXIT_SUCCESS;
  } else if (strcmp(key, "config_end_g") == 0) {
    config_end_g = value;
    return EXIT_SUCCESS;
  } else if (strcmp(key, "config_end_b") == 0) {
    config_end_b = value;
    return EXIT_SUCCESS;
  } else if (strcmp(key, "config_offset") == 0) {
    config_offset = value;
    return EXIT_SUCCESS;
  }

  return 0;
}
