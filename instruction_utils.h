#ifndef INSTRUCTION_UTILS_H
#define INSTRCTION_UTILS_H

#include "defs.h"

/*Function prototypes*/

/**
 * @brief Processes the immediate operand.
 * 
 * @param token The operand to process.
 * @param operand_num The number of the operand. Source operand is 1, destination operand is 2.
 * @param word_count The number of information word of the command (there might be a few information words).
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 */
void process_immediate(char *token, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image);

/**
 * @brief Processes the direct register and indirect register operands.
 * 
 * @param token The operand to process.
 * @param operand_num The number of the operand. Source operand is 1, destination operand is 2.
 * @param word_count The number of information word of the command (there might be a few information words).
 * @param is_direct 1 if the operand is direct, 0 if the operand is indirect.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 */
void process_register(char *token, int operand_num, int word_count, int is_direct, FileInfo *file_info, MachineCodeImage *machine_code_image);

#endif