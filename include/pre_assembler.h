#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

#include "defs.h"
#include "stdio.h"

/**
 * @brief This function interpret the macros in the file.
 * 
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param tables A pointer to the Tables struct containing the tables.
 * @return FILE* A pointer to the .am file with the macros interpreted or NULL if an error was detected.
 */
FILE *interpret_macro(FileInfo *file_info, Tables *tables);

#endif