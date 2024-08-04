/*this file includes different tables and structers and macros used for the assembler*/
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>

/*Macros that will be used all over the project*/
#define MAX_OP_NAME_LEN 5
#define MAX_DATA_NAME_LEN 8
#define MAX_LINE_LENGTH 80
#define MAX_LABEL_LENGTH 31
#define NUM_OF_OP 16
#define NUM_OF_DATA 4
#define NUM_OF_ADDRESSING_METHODS 4
#define NUM_OF_REGISTERS 8
#define ALLOC_SIZE 50
#define BITS_IN_WORD 15
#define MAX_PROGRAM_LENGTH 1000
#define FIRST_ADDRESS 100
#define ERROR_MESSAGE "%s:%d: %s\n", file_info->file_name, file_info->line_count

/*Useful Data Structers for passing along in the project*/
typedef struct
{
    unsigned int instruction_array[MAX_PROGRAM_LENGTH];
    unsigned int data_array[MAX_PROGRAM_LENGTH];
    int IC;
    int DC;
} MachineCodeImage;

typedef struct
{
    LabelTableNode *label_table_head;
    EntryTableNode *entry_table_head;
    ExternTableNode *extern_table_head;
    OperandTableNode *operand_label_table_head;
} Tables;

typedef struct
{
    FILE *file;
    const char *file_name;
    int line_count;
    int error_status : 1;
} FileInfo;

/*Dynamic Tables*/
typedef struct LabelTableNode
{
    char name[MAX_LABEL_LENGTH + 1]; /*+1 for '\0'*/
    int address;
    int is_data : 1; /*one bit flag*/
    struct LabelTableNode *next;
} LabelTableNode;

typedef struct EntryTableNode
{
    char name[MAX_LABEL_LENGTH + 1]; /*+1 for '\0'*/
    struct EntryTableNode *next;
} EntryTableNode;

typedef struct ExternTableNode
{
    char name[MAX_LABEL_LENGTH + 1]; /*+1 for '\0'*/
    struct ExternTableNode *next;
} ExternTableNode;

typedef struct OperandTableNode
{
    char name[MAX_LABEL_LENGTH + 1]; /*+1 for '\0'*/
    int position_in_instruction_array;
    int position_in_file;
    struct OperandTableNode *next;
} OperandTableNode;

/*Constant Tables*/
typedef struct
{
    int code;
    char name[MAX_OP_NAME_LEN];
    int num_of_operands;
    int source_address_method[NUM_OF_ADDRESSING_METHODS];
    int target_address_method[NUM_OF_ADDRESSING_METHODS];
} OperationTable;

typedef struct 
{
    int code;
    char name[MAX_DATA_NAME_LEN];
} DataTable;

/*Definitions of the operation and data tables*/
extern const OperationTable operation_table[] = {
            {0, "mov", 2, {1,1,1,1}, {0,1,1,1}},
            {1, "cmp", 2, {1,1,1,1}, {1,1,1,1}},
            {2, "add", 2, {1,1,1,1}, {0,1,1,1}}, 
            {3, "sub", 2, {1,1,1,1}, {0,1,1,1}}, 
            {4, "lea", 2, {0,1,0,0}, {0,1,1,1}}, 
            {5, "clr", 1, {0}, {0,1,1,1}}, 
            {6, "not", 1, {0}, {0,1,1,1}}, 
            {7, "inc", 1, {0}, {0,1,1,1}}, 
            {8, "dec", 1, {0}, {0,1,1,1}}, 
            {9, "jmp", 1, {0}, {0,1,1,0}}, 
            {10, "bne", 1, {0}, {0,1,1,0}}, 
            {11, "red", 1, {0}, {0,1,1,1}},
            {12, "prn", 1, {0}, {1,1,1,1}},
            {13, "jsr", 1, {0}, {0,1,1,0}},
            {14, "rts", 0, {0}, {0}},
            {15, "stop", 0, {0}, {0}}
       };
extern const DataTable data_table[] = {
            {0, ".data"},
            {1, ".string"},
            {2, ".entry"},
            {3, ".extern"}
};

#endif