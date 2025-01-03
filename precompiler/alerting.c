#include "config.h"
#include "parser.h"
#include "precompile.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  parse_config();

  if (path_output_script == NULL) {
    printf("Error: Config value 'path_output_script' is NULL.");
    return EXIT_FAILURE;
  }
  if (path_function_script == NULL) {
    printf("Error: Config value 'path_function_script' is NULL.");
    return EXIT_FAILURE;
  }
  if (segment_header == NULL) {
    printf("Error: Config value 'segment_header' is NULL.");
    return EXIT_FAILURE;
  }
  if (segment_repeated == NULL) {
    printf("Error: Config value 'segment_repeated' is NULL.");
    return EXIT_FAILURE;
  }
  if (segment_footer == NULL) {
    printf("Error: Config value 'segment_footer' is NULL.");
    return EXIT_FAILURE;
  }

  compile_write();

  // Free segments
  free(path_output_script);
  free(path_function_script);
  free(segment_header);
  free(segment_repeated);
  free(segment_footer);
  return EXIT_SUCCESS;
}
