/*this file includes different tables and structers and macros used for the assembler*/
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>

/*Macros that will be used all over the project*/
#define MAX_OP_NAME_LENGTH 5
#define MAX_DATA_NAME_LENGTH 8
#define MAX_LINE_LENGTH 80
#define MAX_LABEL_LENGTH 31
#define NUM_OF_OP 16
#define NUM_OF_DATA 4
#define NUM_OF_ADDRESSING_METHODS 4
#define ALLOC_SIZE 50
#define BITS_IN_WORD 15
#define MAX_PROGRAM_LENGTH 1000
#define FIRST_ADDRESS 100
#define ERROR_MESSAGE "%s:%d: %s\n", file_info->file_name, file_info->line_count

/*Dynamic Tables*/

/**
 * @brief A struct containing a node in the label table.
 * 
 * @param name The name of the label.
 * @param address The address of the label.
 * @param is_data A flag indicating if the label is a label to a data command.
 * @param next A pointer to the next node in the table.
 */
typedef struct LabelTableNode
{
    char name[MAX_LABEL_LENGTH + 1]; /*+1 for '\0'*/
    int address;
    int is_data : 1; /*one bit flag*/
    struct LabelTableNode *next;
} LabelTableNode;

/**
 * @brief A struct containing a node in the entry table.
 * 
 * @param name The name of the entry label.
 * @param next A pointer to the next node in the table.
 */
typedef struct EntryTableNode
{
    char name[MAX_LABEL_LENGTH + 1]; /*+1 for '\0'*/
    struct EntryTableNode *next;
} EntryTableNode;

/**
 * @brief A struct containing a node in the extern table.
 * 
 * @param name The name of the external label.
 * @param next A pointer to the next node in the table.
 */
typedef struct ExternTableNode
{
    char name[MAX_LABEL_LENGTH + 1]; /*+1 for '\0'*/
    struct ExternTableNode *next;
} ExternTableNode;

/**
 * @brief A struct containing a node in the operand table.
 * 
 * @param name The name of the operand label.
 * @param position_in_instruction_array The position of the operand in the instruction array.
 * @param position_in_file The position of the operand in the file.
 * @param next A pointer to the next node in the table.
 */
typedef struct OperandTableNode
{
    char name[MAX_LABEL_LENGTH + 1]; /*+1 for '\0'*/
    int position_in_instruction_array;
    int position_in_file;
    struct OperandTableNode *next;
} OperandTableNode;

/*Constant Tables*/

/**
 * @brief A struct containing information about an operation.
 * 
 * @param code The operation code.
 * @param name The name of the operation.
 * @param num_of_operands The number of operands the operation is allowed to take.
 * @param source_address_method An array containing the source addressing methods.
 * @param target_address_method An array containing the target addressing methods.
 */
typedef struct
{
    int code;
    char name[MAX_OP_NAME_LENGTH];
    int num_of_operands;
    int first_operand_address_method[NUM_OF_ADDRESSING_METHODS];
    int second_operand_method[NUM_OF_ADDRESSING_METHODS];
} OperationTable;

/**
 * @brief A struct containing information about a data command.
 * 
 * @param code The data command code.
 * @param name The name of the data command.
 */
typedef struct 
{
    int code;
    char name[MAX_DATA_NAME_LENGTH];
} DataTable;

/*Useful Data Structers for passing along in the project*/

/**
 * @brief A struct containing the machine code image.
 * 
 * @param instruction_array An array containing all the instructions commands.
 * @param data_array An array containing all the data commands.
 * @param IC The instruction counter.
 * @param DC The data counter.
 */
typedef struct
{
    unsigned int instruction_array[MAX_PROGRAM_LENGTH];
    unsigned int data_array[MAX_PROGRAM_LENGTH];
    int IC;
    int DC;
} MachineCodeImage;

/**
 * @brief A struct containing the tables.
 * 
 * @param label_table_head A pointer to the head of the label table.
 * @param entry_table_head A pointer to the head of the entry table.
 * @param extern_table_head A pointer to the head of the extern table.
 * @param operand_label_table_head A pointer to the head of the operand label table.
 */
typedef struct
{
    LabelTableNode *label_table_head;
    EntryTableNode *entry_table_head;
    ExternTableNode *extern_table_head;
    OperandTableNode *operand_label_table_head;
} Tables;

/**
 * @brief A struct containing information about the file.
 * 
 * @param file A pointer to the file.
 * @param file_name The name of the file.
 * @param line_count The current line number in the file.
 * @param error_status A flag indicating if an error has was detected.
 */
typedef struct
{
    FILE *file;
    char *file_name;
    int line_count;
    unsigned int error_status : 1;
} FileInfo;


#endif