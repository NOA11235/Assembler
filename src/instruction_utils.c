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
    /*checking if addressing method is allowed*/
    if(!operation_table[opcode].addressing_method[operand_num - 1][0])
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
    num = calculate_two_complement(token, 12, file_info); /*calculating the number in 2's complement*/

    /*inserting addressing method 0 in source or target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= (source_operand_flag)? 1 << 7 : 1 << 3;
    /*inserting 'A' field into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= 1 << 2;
    /*inserting immediate value into the the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= num << 3;
}

void process_indirect_register(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int num;
    /*flag is set if the operand is the source operand*/
    int source_operand_flag = (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? 1 : 0;

    if(!operation_table[opcode].addressing_method[operand_num - 1][1])
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
    machine_code_image->instruction_array[machine_code_image->IC] |= (source_operand_flag)? 1 << 9 : 1 << 5;
    /*inserting 'A' field into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= 1 << 2;

    num = token[0] - '0';

    /*inserting register number into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= (source_operand_flag)? num << 6 : num << 3;
}

void process_direct_register(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int num;
    /*flag is set if the operand is the source operand*/
    int source_operand_flag = (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? 1 : 0;

    if(!operation_table[opcode].addressing_method[operand_num - 1][2])
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
    machine_code_image->instruction_array[machine_code_image->IC] |= (source_operand_flag)? 1 << 10 : 1 << 6;
    /*inserting 'A' field into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= 1 << 2;

    num = token[0] - '0';

    /*inserting register number into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= (source_operand_flag)? num << 6 : num << 3;
}

void process_direct(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, Tables *tables, MachineCodeImage *machine_code_image)
{
    /*flag is set if the operand is the source operand*/
    int source_operand_flag = (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? 1 : 0;

    if(!operation_table[opcode].addressing_method[operand_num - 1][1])
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

    if(!is_valid_label(token, file_info, tables))
    {
        return;
    }

    /*inserting addressing method 1 into source or target. If there is only one operand the method is inserted into the target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= (source_operand_flag)? 1 << 8 : 1 << 4;

    add_operand_to_table(token, machine_code_image->IC + word_count, file_info->line_count, tables);
}