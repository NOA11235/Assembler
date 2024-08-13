#ifndef FIRST_PASS_UTILS_H
#define FIRST_PASS_UTILS_H

#include "defs.h"

/*Function prototypes*/

/**
 * @brief Checks if a line is empty.
 * 
 * @param line The line to check.
 * @return 1 if the line is empty, 0 otherwise.
 */
int is_empty(char line[]);

/**
 * @brief Checks if a line is a comment.
 * 
 * @param line The line to check.
 * @return 1 if the line is a comment, 0 otherwise.
 */
int is_comment(char line[]);

/**
 * @brief This function checks if a line contains a label.
 * 
 * @param line The line to check.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param tables A pointer to the Tables struct containing the tables.
 * @return 1 if the line contains a label, 0 otherwise.
 */
int search_for_label(char line[], FileInfo *file_info, Tables *tables);

/**
 * @brief Checks if a line is a data command.
 * 
 * @param line The line to check.
 * @return 1 if the line is a data command, 0 otherwise.
 */
int is_data(char line[]);

/**
 * @brief Checks if a line is an instruction command.
 * 
 * @param line The line to check.
 * @return 1 if the line is an instruction command, 0 otherwise.
 */
int is_instruction(char line[]);

/**
 * @brief Wrapper function for adding label to the label table. The function gets rid of the label from the line.
 * 
 * @param line The line containing the label to process.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param tables A pointer to the Tables struct containing the tables.
 * @param counter The segment counter IC or DC.
 * @return The line without the label.
 */
char *process_label(char line[], FileInfo *file_info, Tables *tables, int counter);

/**
 * @brief Processes the data command in the line.
 * 
 * @param line The line to process.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param tables A pointer to the Tables struct containing the tables.
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 */
void process_data(char *line, FileInfo *file_info, Tables *tables, MachineCodeImage *machine_code_image);

/**
 * @brief Processes the string command in the line.
 * 
 * @param line The line to process.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param tables A pointer to the Tables struct containing the tables.
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 */
void process_instruction(char *line, FileInfo *file_info, Tables *tables, MachineCodeImage *machine_code_image);

#endif 