#ifndef PRECOMPILE_CONFIG_H
#define PRECOMPILE_CONFIG_H

#include <stdio.h>

/// Config variables
///
extern int interpolation_degree;
extern char *segment_header;
extern char *segment_repeated;
extern char *segment_footer;

/// Returns:
///   ERROR_NULL_POINTER
///   0 --- Key does not match any known variable
///   EXIT_SUCCESS
extern int parse_kvp(char *key, int value);

#endif
