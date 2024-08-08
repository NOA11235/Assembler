#ifndef DATA_UTILS_H
#define DATA_UTILS_H

#include "defs.h"

/* Function prototypes */

/**
 * @brief Processes the .data line.
 * 
 * @param line The line to process.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 */
void process_data_data(char *line, FileInfo *file_info, MachineCodeImage *machine_code_image);

/**
 * @brief Processes the .string line.
 * 
 * @param line The line to process.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 */
void process_string_data(char *line, FileInfo *file_info, MachineCodeImage *machine_code_image);

/**
 * @brief Processes the .entry line.
 * 
 * @param line The line to process.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param tables A pointer to the Tables struct containing the tables.
 */
void process_entry_data(char *line, FileInfo *file_info, Tables *tables);

/**
 * @brief Processes the .extern line.
 * 
 * @param line The line to process.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param tables A pointer to the Tables struct containing the tables.
 */
void process_extern_data(char *line, FileInfo *file_info, Tables *tables);

#endif 