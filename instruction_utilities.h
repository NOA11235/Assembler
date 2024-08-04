#ifndef INSTRUCTION_UTILITIES_H
#define INSTRCTION_UTILITIES_H

/*Function prototypes*/
void process_immediate(char *, int, int, FileInfo *, MachineCodeImage *);
void process_register(char *, int, int, int, FileInfo *, MachineCodeImage *);

#endif