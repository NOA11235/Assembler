#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "defs.h"
#include <stdio.h>

/*Function prototypes*/

/**
 * @brief The first pass of the assembler
 * 
 * @param machine_code_image A pointer to the MachineCodeImage struct containing the machine code image.
 * @param tables A pointer to the Tables struct containing the tables.
 * @param file_info A pointer to the FileInfo struct containing information about the file.
 */
void first_pass(MachineCodeImage *machine_code_image, Tables *tables, FileInfo *file_info);

#endif