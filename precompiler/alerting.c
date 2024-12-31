#include "config.h"
#include "parser.h"
#include "precompile.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  parse_config();
  compile_write();

  // Free segments
  if (segment_header != NULL)
    free(segment_header);
  if (segment_repeated != NULL)
    free(segment_repeated);
  if (segment_footer != NULL)
    free(segment_footer);
  return EXIT_SUCCESS;
}
