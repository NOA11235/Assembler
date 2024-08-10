#ifndef PRE_ASSEMBLER_UTILS_H
#define PRE_ASSEMBLER_UTILS_H

#include "defs.h"

/*Function prototypes*/

/**
 * @brief Checks if a given string is a valid macro name.
 * 
 * @param name The name to check.
 * @return int 1 if the name is valid, 0 otherwise.
 */
int is_valid_macro_name(char *name);

/**
 * @brief Processes a new macro definition.
 * 
 * @param line The line containing the macro definition.
 * @param file_info A pointer to the file info.
 * @param tableshe pointer to the tables.
 */
vo Tid process_macro_definition(char *line, FileInfo *file_info, Tables *tables);

/**
 * @brief Processes the end of a macro definition.
 * 
 * @param line The line containing the end of the macro definition.
 * @param file_info A pointer to the file info.
 * @param tables A pointer to the tables.
 */
void process_end_of_macro_definition(char *line, FileInfo *file_info, Tables *tables);

/**
 * @brief Adds the content of a macro to the macro table.
 * 
 * @param line The line containing the macro content.
 * @param file_info A pointer to the file info.
 * @param tables A pointer to the tables.
 */
void add_content_to_macro(char *line, FileInfo *file_info, Tables *tables);

/**
 * @brief Finds a macro in the macro table and prints it.
 * 
 * @param line The first word in the line.
 * @param file_info A pointer to the file info.
 * @param tables A pointer to the tables.
 * @return int 1 if the macro was found and printed, 0 otherwise.
 */
int find_macro_and_print(char *line, FileInfo *file_info, Tables *tables);

#endif