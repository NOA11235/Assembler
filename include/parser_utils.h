#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "defs.h"

/*Function prototypes*/

/**
 * @brief This function validates the commas in a line, and prints an error message(s) if the commas are not valid.
 * 
 * @param line The line to validate.
 * @param file_info A pointer to the FileInfo struct.
 */
void validate_commas(char *line, FileInfo *file_info);

/**
 * @brief This function walks through white spaces in a line.
 * 
 * @param line The line to walk through.
 * @return A pointer to the first non-white-space character in the line.
 */
char *walkthrough_white_spaces(char *line);

/**
 * @brief This function reads the next line from the file and updates the FileInfo struct accordingly.
 * 
 * @param line A pointer to the  buffer-line to read into.
 * @param file_info A pointer to the FileInfo struct.
 * @return 1 if the line was read successfully, 0 otherwise.
 */
int read_line(char *line, FileInfo *file_info);

/**
 * @brief This function checks if a token is a register.
 * 
 * @param token The token to check.
 * @return 1 if the token is a register, 0 otherwise.
 */
int is_register(char *token);

/**
 * @brief This function checks if a name is a reserved word.
 * 
 * @param name The name to check.
 * @return 1 if the name is a reserved word, 0 otherwise.
 */
int is_reserved_word(char *name);

/**
 * @brief This function checks if a token is an integer.
 * 
 * @param token The token to check.
 * @return 1 if the token is an integer, 0 otherwise.
 */
int is_valid_integer(char *token);

/**
 * @brief This function calculates the two's complement of a token and checks if the token is in the range (can be represented by a certain number of bits).
 * 
 * @param token The token to calculate the two's complement of.
 * @param num_of_bits The number of bits the token is represented by.
 * @param file_info A pointer to the FileInfo struct.
 * @return The two's complement of the token.
 */
int calculate_two_complement(char *token, int num_of_bits, FileInfo *file_info);

#endif