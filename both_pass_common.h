#ifndef FIRST_PASS_COMMON_H
#define FIRST_PASS_COMMON_H

#define MAX_LINE_LENGTH 80
#define MAX_PROGRAM_LENGTH 1000
#define WORD_SIZE 15
#define MAX_LABEL_LENGTH 31
#define BITS_IN_WORD 15
#define ERROR_MESSAGE "%d: %d: %s\n", file_info.file_name, file_info.line_count

extern unsigned int instruction_array[MAX_PROGRAM_LENGTH];
extern unsigned int data_array[MAX_PROGRAM_LENGTH];
extern int IC = 0, DC = 0;
extern int error_flag = 0;
extern struct
{
    const char *file_name;
    int line_count;
} file_info;

#endif