#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "defs.h"

/*Function prototypes*/

/**
 * @brief The second pass of the assembler
 * 
 * @param fileInfo A pointer to the FileInfo struct containing information about the file.
 * @param tables A pointer to the Tables struct containing the tables.
 * @param machineCodeImage A pointer to the MachineCodeImage struct containing the machine code image.
 */
void second_pass(MachineCodeImage *machine_code_image, Tables *tables, FileInfo *file_info);

#endif
