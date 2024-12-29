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

  return parse_kvp(key, value);
}

int parse_config() {
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
