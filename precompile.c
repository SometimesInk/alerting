#include "precompile.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

int compile_calculate(int a, int b, int n, int t) {
  FILE *file;
  char result[128]; // Buffer to store the output of the command
  int output;

  int max_command_length = 128;
  char *command = (char *)malloc(max_command_length * sizeof(char));
  if (command == NULL) {
    return -ERROR_NULL_POINTER;
  }
  command[0] = '\0';
  // Format command
  snprintf(command, 128, "./interpolation_nth_degree.sh %i %i %i %i", a, b, n,
           t);

  // Open a pipe to execute the command and capture its output
  file = popen(command, "r");
  if (file == NULL) {
    perror("popen");
    return -ERROR_NULL_POINTER;
  }

  // Deallocate memory
  free(command);

  // Read the output of the command into the result buffer
  if (fgets(result, sizeof(result), file) != NULL) {
    // Convert the result to an integer
    output = strtol(result, NULL, 16);
  } else {
    perror("fgets");
  }

  // Close the pipe
  fclose(file);
  return output;
}

void compile_write(void) {
  FILE *file;

  // Open a file in writing mode
  file = fopen("precompiled_values.sh", "w");

  // Write some text to the file
  fprintf(file, "Some text");

  // Close the file
  fclose(file);
}
