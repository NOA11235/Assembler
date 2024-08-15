#ifndef PRE_ASSEMBLER_UTILS_H
#define PRE_ASSEMBLER_UTILS_H

#include "defs.h"

/*Function prototypes*/

/**
 * @brief Creates a .am file.
 * 
 * @param filename The name of the file.
 * @return A pointer to the file.
 */
FILE *create_am_file(const char *filename);

/**
 * @brief Processes a new macro definition.
 * 
 * @param line The line containing the macro definition.
 * @param tables A pointer to the FileInfo struct containing information about the file.
 * @param tableshe pointer to the tables.
 */
void process_macro_definition(char *line, FileInfo *file_info, Tables *tables);

/**
 * @brief Processes the end of a macro definition.
 * 
 * @param line The line containing the end of the macro definition.
 * @param tables A pointer to the FileInfo struct containing information about the file.
 * @param tables A pointer to the Tables struct containing the tables
 */
void process_end_of_macro_definition(char *line, FileInfo *file_info, Tables *tables);

/**
 * @brief Frees the macro table.
 * 
 * @param tables A pointer to the Tables struct containing the tables
 */
void free_macro_table(Tables *tables);

#endif