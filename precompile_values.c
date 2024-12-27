#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int interpolation_degree = 1;

char *segment_header;
char *segment_repeated;
char *segment_footer;

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
    return;
  }

  // Check if line is a segment
  if (line[0] == '%' && strlen(line) > 1) {
    memmove(line, line + 2, strlen(line));
    if (line[1] == 'h') {
      // Reallocate memory for the old segment_header, the new line to append, a
      // new line and a null terminating character
      segment_header = (char *)realloc(
          segment_header,
          sizeof(char) * (strlen(segment_header) + strlen(line) + 2));

      // Move line at the end of segment_header
      memmove(segment_header + strlen(segment_header), line, strlen(line));

      // Add new line and ensure null termination
      segment_header[strlen(segment_header) - 2] = '\n';
      segment_header[strlen(segment_header) - 1] = '\0';
    } else if (line[1] == 'r') {
      // Parse repeated segment
    } else if (line[1] == 'f') {
      // Parse footer
    }
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

void write_script() {
  FILE *file;

  // Open a file in writing mode
  file = fopen("precompiled_values.sh", "w");

  // Write some text to the file
  fprintf(file, "Some text");

  // Close the file
  fclose(file);
}

int main(void) {
  // Allocate memory for segments
  segment_header = (char *)malloc(sizeof(char));
  segment_repeated = (char *)malloc(sizeof(char));
  segment_footer = (char *)malloc(sizeof(char));

  // Check if allocation succeeded
  if (segment_header == NULL || segment_repeated == NULL ||
      segment_footer == NULL) {
    printf("Memory allocation failed\n");
    return EXIT_FAILURE;
  }

  // Ensure null termination
  segment_header[0] = '\0';
  segment_repeated[0] = '\0';
  segment_footer[0] = '\0';

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

  printf("%s", segment_header);

  free(segment_header);
  free(segment_repeated);
  free(segment_footer);
  exit(EXIT_SUCCESS);
}
