#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "defs.h"

/*Function prototypes*/

/**
 * @brief This function takes a token and a comma flag as input and parses the commas in the token.
   It updates the comma flag accordingly and returns the modified token without the commas.
 *
 * @param token The token to parse.
 * @param comma_flag A pointer to the comma flag.
 * @param file_info A pointer to the FileInfo struct.
 * @return The modified token after parsing the commas.
 */
char *comma_parser(char *token, int *comma_flag, FileInfo *file_info);

/**
 * @brief This function reads the next line from the file and updates the FileInfo struct accordingly.
 * 
 * @param line A pointer to the  buffer-line to read into.
 * @param file_info A pointer to the FileInfo struct.
 * @return 1 if the line was read successfully, 0 otherwise.
 */
int read_line(char *line, FileInfo *file_info);

/**
 * @brief This function checks if a line contains a label.
 * 
 * @param line The line to check.
 * @return 1 if the line is contains a label, 0 otherwise.
 */
int is_label(char line[]);

#endif