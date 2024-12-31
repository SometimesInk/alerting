#ifndef PARSER_H
#define PARSER_H

extern int parse_line(char *line);

/// Returns:
///   ERROR_ALLOCATION_FAILURE
///   1 --- Success
extern int parse_config(void);

#endif
