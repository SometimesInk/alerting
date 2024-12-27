#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int interpolation_degree = 1;

void read_line(char *line) {
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
      value = strtol(token, NULL, 10);
    }
    token = strtok(NULL, "");
  }

  // Assign variable to its correct value
  if (strcmp(key, "interpolation_degree") == 0) {
    interpolation_degree = value;
  }
}

void read_config(FILE *file, char *line) {
  size_t length = 0;
  ssize_t read;

  // Read file line by line
  while ((read = getline(&line, &length, file)) != -1) {
    // Read all lines that aren't comments
    if (line[0] != ';') {
      read_line(line);
    }
  }
}

int compile(int t) {
  FILE *file;
  char result[128]; // Buffer to store the output of the command
  int output;

  // Open a pipe to execute the command and capture its output
  file = popen("./interpolation_nth_degree.sh", "r");
  if (file == NULL) {
    perror("popen");
    return 1;
  }

  // Read the output of the command into the result buffer
  if (fgets(result, sizeof(result), file) != NULL) {
    // Convert the result to an integer
    output = strtol(result, NULL, 16);
  } else {
    perror("fgets");
  }

  // Close the pipe
  fclose(file);
  return 0;
}

int main(void) {
  FILE *file;
  char *line = NULL;

  // Open file
  file = fopen("alerting.ini", "r");
  if (file == NULL)
    exit(EXIT_FAILURE);

  // Parse config file
  read_config(file, line);

  fclose(file);
  if (line)
    free(line);

  // TODO: Write to file "precompiled_values.sh" & actually precompile

  // Precompile values for function
  for (int i = 1; i < 101; i++) { // Values [1,100]
  }

  exit(EXIT_SUCCESS);
}
