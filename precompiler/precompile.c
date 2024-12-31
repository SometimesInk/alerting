#include "precompile.h"
#include "config.h"
#include "errors.h"
#include "formatter.h"
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
    output = strtol(result, NULL, 10);
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
  remove("precompiled_values.sh");
  file = fopen("precompiled_values.sh", "w");
  if (file == NULL)
    return;

  // Write some text to the file
  fprintf(file, "%s", segment_header);

  // 0  ->99    no
  // 1  ->101   i 100
  // 1  ->101   i 100 abs
  //
  // 100->1     no
  // 99->0      i 100
  // 100->0     i 100 abs

  for (int i = 0 + config_offset; i < 100 + config_offset; i++) {
    char *index_as_string;
    integer_as_string(&index_as_string, abs(100 + config_offset - i), 0);

    int r = compile_calculate(config_start_r, config_end_r,
                              config_interpolation_degree, i);
    int g = compile_calculate(config_start_g, config_end_g,
                              config_interpolation_degree, i);
    int b = compile_calculate(config_start_b, config_end_b,
                              config_interpolation_degree, i);
    char *r_string;
    char *g_string;
    char *b_string;

    integer_as_string(&r_string, r, 1);
    integer_as_string(&g_string, g, 1);
    integer_as_string(&b_string, b, 1);

    ensure_two_digits(&r_string);
    ensure_two_digits(&g_string);
    ensure_two_digits(&b_string);

    fprintf(file, "%s",
            format(format(format(format(segment_repeated, "%", index_as_string),
                                 "&", r_string),
                          "$", g_string),
                   "#", b_string));

    free(index_as_string);
    free(r_string);
    free(g_string);
    free(b_string);
  }

  fprintf(file, "%s", segment_footer);

  // Close the file
  fclose(file);
}
