#include "instruction_utils.h"
#include "defs.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void process_immediate(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int i, num, minus_flag = 0;
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
    minus_flag = (token[1] == '-')? 1 : 0; /*checking if the immediate value is negitive*/
    token = (token[1] == '+' || token[1] == '-')? token + 2: token + 1; /*getting rid of '#' and a positive or negitive sign*/
    
    /*checking if the immediate value is an integer*/
    for(i = 0; i < strlen(token); i++)
    {
        if(!isdigit(token[i]))
        {
            printf(ERROR_MESSAGE, "error: immediate value must be an integer");
            file_info->error_status = 1;
            return;
        }
    }

    num = atoi(token);
    
    /*checking if the immediate value is in the range of 12 bits*/
    if(num < -pow(2, 11) || num >= pow(2, 11))
    {
        printf(ERROR_MESSAGE, "error: immediate value is out of range");
        file_info->error_status = 1;
        return;
    }

    /*calculating the number if the data is negitive so it would be represented in the 2's complement method*/
    if(minus_flag)
    {
        num = (~num) + 1; /*calculating the 2's complement*/
        num = num & 0xFFF; /*making sure the number is in the range of 12 bits*/
    }

    /*inserting 'A' field into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= 1 << 2;
    /*inserting addressing method 0 in source or target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= (source_operand_flag)? 1 << 7 : 1 << 3;
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

    /*inserting 'A' field into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= 1 << 2;
    /*inserting addressing method 2 into source or target. If there is only one operand the method is inserted into the target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= (source_operand_flag)? 1 << 9 : 1 << 5;

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

    /*inserting 'A' field into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= 1 << 2;
    /*inserting addressing method 3 into source or target. If there is only one operand the method is inserted into the target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= (source_operand_flag)? 1 << 10 : 1 << 6;

    num = token[0] - '0';

    /*inserting register number into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= (source_operand_flag)? num << 6 : num << 3;
}

void process_direct(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
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

    /*inserting addressing method 1 into source or target. If there is only one operand the method is inserted into the target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= (source_operand_flag)? 1 << 8 : 1 << 4;
}