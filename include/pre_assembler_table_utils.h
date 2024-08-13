#ifndef PRE_ASSEMBLER_TABLE_UTILS_H
#define PRE_ASSEMBLER_TABLE_UTILS_H

#include "defs.h"

/*Function prototypes*/

/**
 * @brief Checks if a macro name already exists in the macro table.
 * 
 * @param name The name of the macro.
 * @param tables A pointer to the tables.
 * @return int 1 if the macro name already exists, 0 otherwise.
 */
int macro_name_already_exists(char *name, Tables *tables);

/**
 * @brief Adds a macro to the macro table.
 * 
 * @param name The name of the macro.
 * @param tables A pointer to the tables.
 */
void add_macro_to_macro_table(char *name, Tables *tables);

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
 * @param am_file A pointer to the .am file.
 * @param file_info A pointer to the file info.
 * @param tables A pointer to the tables.
 * @return int 1 if the macro was found and printed, 0 otherwise.
 */
int find_macro_and_print(char *line, FILE *am_file, FileInfo *file_info, Tables *tables);

#endif