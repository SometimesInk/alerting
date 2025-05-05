#include "parser.h"
#include "config.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_line(char *line) {
  int key_assigned = 0;

  char *key;
  int value;

  // Remove newline
  line[strcspn(line, "\n")] = 0;

  // Assign KVp
  char *token = strtok(line, "=");
  while (token != NULL) {
    if (!key_assigned) {
      key = token;
      key_assigned = 1;
    } else {
      // String -> Integer
      value = strtol(token, NULL, 10);
    }
    token = strtok(NULL, "");
  }

  if (parse_kvp(line, key, value) == 0) {
    // Check if line is a path
    if (strncmp(line, "%p", 2) == 0)
      return parse_section(&path_output_script, &path_output_script_length, line);
    if (strncmp(line, "%P", 2) == 0)
      return parse_section(&path_function_script, &path_function_script_length, line);

    // Check if line is a segment
    if (strncmp(line, "%h", 2) == 0)
      return parse_section(&segment_header, &segment_header_length, line);
    if (strncmp(line, "%r", 2) == 0)
      return parse_section(&segment_repeated, &segment_repeated_length, line);
    if (strncmp(line, "%f", 2) == 0)
      return parse_section(&segment_footer, &segment_footer_length, line);
  }
  return 0;
}

int parse_config(void) {
  FILE *file;
  char *line = NULL;
  size_t length = 0;
  ssize_t read;

  file = fopen("alerting.ini", "r");

  // Check if memory allocation was successful
  if (file == NULL)
    return -ERROR_ALLOCATION_FAILURE;

  // Read file line by line excluding comments
  while ((read = getline(&line, &length, file)) != -1) {
    if (line[0] != ';') {
      parse_line(line);
    }
  }

  fclose(file);
  if (line)
    free(line);
  return 1;
}
