#ifndef PRECOMPILE_CONFIG_H
#define PRECOMPILE_CONFIG_H

#include <stdio.h>

/// Config variables
///
extern int config_interpolation_degree;
extern int config_start_r;
extern int config_start_g;
extern int config_start_b;
extern int config_end_r;
extern int config_end_g;
extern int config_end_b;
extern int config_offset;

extern char *segment_header;
extern size_t segment_header_length;
extern char *segment_repeated;
extern size_t segment_repeated_length;
extern char *segment_footer;
extern size_t segment_footer_length;

/// Pass the address of a `char *`
/// e.g.: parse_section(&section, &length, line);
///
/// Returns:
///  -ERROR_NULL_POINTER
///   EXIT_SUCCESS
extern int parse_section(char **section, size_t *length, char *line);

/// Returns:
///  -ERROR_NULL_POINTER
///   0 --- Key does not match any known variable
///   EXIT_SUCCESS
extern int parse_kvp(char *line, char *key, int value);

#endif
