#ifndef PARSER_UTILITIES_H
#define PARSER_UTILITIES_H
#include <stdio.h>

char *comma_parser(char *, int *);
char *read_line(FILE *);
int is_label(char *);

#endif