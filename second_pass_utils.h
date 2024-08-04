#ifndef SECOND_PASS_UTILS_H
#define SECOND_PASS_UTILS_H

#include "defs.h"

/* Function prototypes */

/**
 * Prints the machine code for the given file and machine code image.
 *
 * @param fileInfo A pointer to the FileInfo struct containing information about the file.
 * @param machineCodeImage A pointer to the MachineCodeImage struct containing the machine code image.
 */
void print_machine_code(FileInfo *, MachineCodeImage *);

#endif