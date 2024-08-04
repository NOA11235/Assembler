#ifndef FIRST_PASS_TABLE_UTILS_H
#define FIRST_PASS_TABLE_UTILS_H

#include "defs.h"

/*Function prototypes*/

/**
 * @brief Adds a label to the label table.
 * 
 * @param tables A pointer to the Tables struct containing the tables.
 * @param name The name of the label.
 * @param address The address of the label.
 * @param is_data A flag indicating if the label is a data label.
 */
void add_label_to_table(Tables *tables, char *name, int address, int is_data);

/**
 * @brief Adds an entry label to the entry table.
 * 
 * @param tables A pointer to the Tables struct containing the tables.
 * @param name The name of the entry label.
 */
void add_entry_to_table(Tables *tables, char *name);

/**
 * @brief Adds an extern label to the extern table.
 * 
 * @param tables A pointer to the Tables struct containing the tables.
 * @param name The name of the extern label.
 */
void add_extern_to_table(Tables *tables, char *name);

/**
 * @brief Adds an operand label to the operand table.
 * 
 * @param tables A pointer to the Tables struct containing the tables.
 * @param name The name of the operand label.
 * @param position_in_instruction_array The position of the operand label in the instruction array.
 * @param position_in_file The position of the operand label in the file.
 */
void add_operand_to_table(Tables *tables, char *name, int position_in_instruction_array, int position_in_file);

#endif