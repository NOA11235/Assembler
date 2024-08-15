#include "instruction_utils.h"
#include "defs.h"
#include "first_pass_table_utils.h"
#include "parser_utils.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void process_immediate(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int num;
    /*flag is set if the operand is the source operand*/
    int source_operand_flag = (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? 1 : 0;
    /*checking if  immediate addressing method is allowed*/
    if(!operation_table[opcode].addressing_method[operand_num - 1][IMMEDIATE_ADDRESSING_CODE])
    {
        if(source_operand_flag)
        {
            printf(ERROR_MESSAGE, "error: immediate addressing method is not allowed for source operand");
        }
        else
        {
            printf(ERROR_MESSAGE, "error: immediate addressing method is not allowed for target operand");
        }
        file_info->error_status = 1;
        return;
    }

    token++; /*getting rid of the '#'*/
    num = calculate_two_complement(token, BITS_IN_WORD - IMMEDIATE_OFFSET, file_info); /*calculating the number in 2's complement*/

    /*inserting addressing method 0 in source or target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= \
    1 << (IMMEDIATE_ADDRESSING_CODE + ((source_operand_flag)? SOURCE_ADDRESSING_OFFSET: TARGET_ADDRESSING_OFFSET));
    /*inserting 'A' field into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= SET_A_FIELD;
    /*inserting immediate value into the the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= num << IMMEDIATE_OFFSET;
}

void process_indirect_register(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int num;
    /*flag is set if the operand is the source operand*/
    int source_operand_flag = (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? 1 : 0;
    /*checking if indirect register addressing method is allowed*/
    if(!operation_table[opcode].addressing_method[operand_num - 1][INDRECT_REGISTER_ADDRESSING_CODE])
    {
        if(source_operand_flag)
        {
            printf(ERROR_MESSAGE, "error: indirect register addressing method is not allowed for source operand");
        }
        else
        {
            printf(ERROR_MESSAGE, "error: indirect register addressing method is not allowed for target operand");
        }
        file_info->error_status = 1;
        return;
    }

    token =  token + 2; /*getting rid of '*' and 'r'*/

    /*inserting addressing method 2 into source or target. If there is only one operand the method is inserted into the target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= \
    1 << (INDRECT_REGISTER_ADDRESSING_CODE + ((source_operand_flag)? SOURCE_ADDRESSING_OFFSET: TARGET_ADDRESSING_OFFSET));
    /*inserting 'A' field into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= SET_A_FIELD;

    num = token[0] - '0';

    /*inserting register number into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= num << ((source_operand_flag)? SOURCE_REGISTER_OFFSET : TARGET_REGISTER_OFFSET);
}

void process_direct_register(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int num;
    /*flag is set if the operand is the source operand*/
    int source_operand_flag = (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? 1 : 0;
    /*checking if direct register addressing method is allowed*/
    if(!operation_table[opcode].addressing_method[operand_num - 1][DIRECT_REGISTER_ADDRESSING_CODE])
    {
        if(source_operand_flag)
        {
            printf(ERROR_MESSAGE, "error: direct register addressing method is not allowed for source operand");
        }
        else
        {
            printf(ERROR_MESSAGE, "error: direct register addressing method is not allowed for target operand");
        }
        file_info->error_status = 1;
        return;
    }

    token =  token + 1; /*getting rid of 'r'*/

    /*inserting addressing method 3 into source or target. If there is only one operand the method is inserted into the target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= \
    1 << (DIRECT_REGISTER_ADDRESSING_CODE + ((source_operand_flag)? SOURCE_ADDRESSING_OFFSET: TARGET_ADDRESSING_OFFSET));
    /*inserting 'A' field into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= SET_A_FIELD;

    num = token[0] - '0';

    /*inserting register number into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= num << ((source_operand_flag)? SOURCE_REGISTER_OFFSET : TARGET_REGISTER_OFFSET);
}

void process_direct(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, Tables *tables, MachineCodeImage *machine_code_image)
{
    /*flag is set if the operand is the source operand*/
    int source_operand_flag = (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? 1 : 0;

    if(!operation_table[opcode].addressing_method[operand_num - 1][DIRECT_ADDRESSING_CODE])
    {
        if(source_operand_flag)
        {
            printf(ERROR_MESSAGE, "error: direct addressing method is not allowed for source operand");
        }
        else
        {
            printf(ERROR_MESSAGE, "error: direct addressing method is not allowed for target operand");
        }
        file_info->error_status = 1;
        return;
    }

    /*inserting addressing method 1 into source or target. If there is only one operand the method is inserted into the target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= \
    1 << (DIRECT_ADDRESSING_CODE + ((source_operand_flag)? SOURCE_ADDRESSING_OFFSET: TARGET_ADDRESSING_OFFSET));

    /*adding label to label operand table to deal with in the second pass*/
    add_operand_to_table(token, machine_code_image->IC + word_count, file_info->line_count, tables);
}