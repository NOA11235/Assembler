/*this file includes different tables and structers and macros used for the assembler*/
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>

/*Macros that will be used all over the project*/
#define MAX_OP_NAME_LENGTH 5
#define MAX_DATA_NAME_LENGTH 8
#define MAX_LINE_LENGTH 80
#define MAX_LABEL_LENGTH 31
#define MAX_MACRO_NAME_LENGTH 31
#define NUM_OF_OPERATIONS 16
#define NUM_OF_DATA 4
#define NUM_OF_ADDRESSING_METHODS 4
#define ALLOC_SIZE 50
#define BITS_IN_WORD 15
#define MAX_PROGRAM_LENGTH 1000
#define FIRST_ADDRESS 100
#define MACRO_ERROR_MESSAGE "%s.as:%d: %s\n", file_info->base_filename, file_info->line_count
#define ERROR_MESSAGE "%s.am:%d: %s\n", file_info->base_filename, file_info->line_count
#define SET_A_FIELD 1 << 2
#define SET_R_FIELD 1 << 1
#define SET_E_FIELD 1
#define SOURCE_ADDRESSING_OFFSET 7
#define TARGET_ADDRESSING_OFFSET 3
#define SOURCE_REGISTER_OFFSET 6
#define TARGET_REGISTER_OFFSET 3
#define OPCODE_OFFSET 11
#define IMMEDIATE_OFFSET 3
#define LABEL_OFFSET 3
#define IMMEDIATE_ADDRESSING_CODE 0
#define DIRECT_ADDRESSING_CODE 1
#define INDRECT_REGISTER_ADDRESSING_CODE 2
#define DIRECT_REGISTER_ADDRESSING_CODE 3

#define MAX_REGISTER_NUMBER 7

/*Dynamic Tables*/

/**
 * @brief A struct containing a node in the macro table.
 * 
 * @param name The name of the macro.
 * @param macro_content The content of the macro.
 * @param next A pointer to the next node in the table.
 */
typedef struct MacroTableNode
{
    char name[MAX_MACRO_NAME_LENGTH];
    char *content;
    struct MacroTableNode *next;

} MacroTableNode;

typedef struct SymbolTableNode
{
    char name[MAX_LABEL_LENGTH + 1]; /*+1 for '\0'*/
    int address;
    int position_in_file;
    unsigned int is_instruction : 1; /*one bit flag*/
    unsigned int is_data : 1; /*one bit flag*/
    unsigned int is_extern : 1; /*one bit flag*/
    unsigned int is_entry : 1; /*one bit flag*/
    struct SymbolTableNode *next;
} SymbolTableNode;

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
 * @param addressing_method An array containing the addressing method of the first operand in 
 *                          addressing_method[0] and of the second operand in addressing_method[1].
 */
typedef struct
{
    int code;
    char name[MAX_OP_NAME_LENGTH];
    int num_of_operands;
    int addressing_method[2][NUM_OF_ADDRESSING_METHODS];
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
    unsigned short int instruction_array[MAX_PROGRAM_LENGTH];
    unsigned short int data_array[MAX_PROGRAM_LENGTH];
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
    MacroTableNode *macro_table_head;
    SymbolTableNode *symbol_table_head;
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
    FILE *input_file;
    const char *base_filename;
    int line_count;
    unsigned int error_status : 1;
} FileInfo;

/*constant tables for the functions in this file*/
extern const OperationTable operation_table[];
extern const DataTable data_table[];

#endif