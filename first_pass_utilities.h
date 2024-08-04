#ifndef FIRST_PASS_UTILITIES_H
#define FIRST_PASS_UTILITIES_H

#include "common.h"

/* Function prototypes */
void process_data(char *, FileInfo *, EntryTableNode *, ExternTableNode *, MachineCodeImage *);
void process_instruction(char *, FileInfo *, OperandTableNode *, MachineCodeImage *);
void process_label(char **, FileInfo *, LabelTableNode *, int);
int is_empty(char *);
int is_comment(char *);
int is_data(char *); 
int is_instruction(char *);

#endif 