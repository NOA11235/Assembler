#ifndef FIRST_PASS_TABLE_UTILS_H
#define FIRST_PASS_TABLE_UTILS_H

#include "defs.h"

/*Function prototypes*/

/**
 * @brief Adds a label to the label table.
 * 
 * @param name The name of the label.
 * @param address The address of the label.
 * @param type The type of the label.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param tables A pointer to the Tables struct containing the tables.
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 */
void add_label_to_table(char *name, int address, char *type, FileInfo *file_info, Tables *tables);

/**
 * @brief Adds an operand label to the operand table.
 * 
 * @param name The name of the operand label.
 * @param position_in_instruction_array The position of the operand label in the instruction array.
 * @param position_in_file The position of the operand label in the file.
 * @param tables A pointer to the Tables struct containing the tables.
 */
void add_operand_to_table(char *name, int position_in_instruction_array, int position_in_file, Tables *tables);

/**
 * @brief Checks if a label name is a macro name.
 * 
 * @param name The name of the macro.
 * @param tables A pointer to the tables.
 */
int is_macro_name(char *name, Tables *tables);

/**
 * @brief Adds the instruction segment length to the data labels.
 * 
 * @param tables A pointer to the tables.
 * @param data_offset The offset of the data segment.
 */
void add_offset_to_data_labels(Tables *tables, int data_offset);

/**
 * @brief Checks if a labels defined as entry are defined in the file.
 * 
 * @param tables A pointer to the tables.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 */
void validate_entry_labels(FileInfo *file_info, Tables *tables);

#endif