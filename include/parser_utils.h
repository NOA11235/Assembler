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
 * @brief This function checks if a token is a valid label name.
 * 
 * @param token The token to check.
 * @param file_info A pointer to the FileInfo struct.
 * @param tables A pointer to the Tables struct.
 * @return 1 if the token is a valid label name, 0 otherwise.
 */
int is_valid_label(char *token, FileInfo *file_info, Tables *tables);

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