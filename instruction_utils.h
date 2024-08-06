#ifndef INSTRUCTION_UTILS_H
#define INSTRCTION_UTILS_H

#include "defs.h"

/*Function prototypes*/

/**
 * @brief Processes the immediate operand.
 * 
 * @param token The operand to process.
 * @param opcode The opcode of the command.
 * @param operand_num The number of the operand. Source operand is 1, destination operand is 2.
 * @param word_count The number of information word of the command (there might be a few information words).
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 */
void process_immediate(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image);

/**
 * @brief Processes the indirect register operands.
 * 
 * @param token The operand to process.
 * @param opcode The opcode of the command.
 * @param operand_num The number of the operand. Source operand is 1, destination operand is 2.
 * @param word_count The number of information word of the command (there might be a few information words).
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 */
void process_indirect_register(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image);

/**
 * @brief Processes the direct register operands.
 * 
 * @param token The operand to process.
 * @param opcode The opcode of the command.
 * @param operand_num The number of the operand. Source operand is 1, destination operand is 2.
 * @param word_count The number of information word of the command (there might be a few information words).
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 */
void process_direct_register(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image);

/**
 * @brief Processes the direct operands.
 * 
 * @param token The operand to process.
 * @param opcode The opcode of the command.
 * @param operand_num The number of the operand. Source operand is 1, destination operand is 2.
 * @param word_count The number of information word of the command (there might be a few information words).
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 */
void process_direct(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image);

#endif