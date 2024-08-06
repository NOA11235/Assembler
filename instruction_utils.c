#include "instruction_utils.h"
#include "defs.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void process_immediate(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int i, num;
    /*checking if addressing method is allowed*/
    if(!operation_table[opcode].addressing_method[operand_num - 1][0])
    {
        printf(ERROR_MESSAGE, "immediate addressing method is not allowed");
        file_info->error_status = 1;
        return;
    }
    token = (token[1] == '+' || token[1] == '-')? token + 2: token + 1; /*getting rid of '#' and a positive or negitive sign*/
    for(i = 0; i < strlen(token); i++)
    {
        if(!isdigit(token[i]))
        {
            printf(ERROR_MESSAGE, "immediate value must be a number");
            file_info->error_status = 1;
            return;
        }
    }
    /*inserting 'A' field into the instruction and information word*/
    machine_code_image->instruction_array[machine_code_image->IC] |= 1 << 2;
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= 1 << 2;
    /*inserting addressing method 0 in source or target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= \
    (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? 1 << 7 : 1 << 3;
    /*inserting immediate value into the the information word*/
    num = atoi(token);
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= num << 3;
}

void process_indirect_register(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int num;

    if(!operation_table[opcode].addressing_method[operand_num - 1][1])
    {
        printf(ERROR_MESSAGE, "indirect register addressing method is not allowed");
        file_info->error_status = 1;
        return;
    }

    token =  token + 2; /*getting rid of '*' and 'r'*/
    if(token[0] < '0' || token[0] > '7')
    {
        printf(ERROR_MESSAGE, "invalid register");
        file_info->error_status = 1;
        return;
    }
    if(token[1] != '\0')
    {   
        if(isdigit(token[1]))
        {
            printf(ERROR_MESSAGE, "invalid register");
        }
        else
        {
            printf(ERROR_MESSAGE, "invalid operand");
        }
        file_info->error_status = 1;
    }

    /*inserting 'A' field into the instruction and information word*/
    machine_code_image->instruction_array[machine_code_image->IC] |= 1 << 2;
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= 1 << 2;
    /*inserting addressing method 2 into source or target. If there is only one operand the method is inserted into the target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= \
    (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? 1 << 9 : 1 << 5;

    num = token[0] - '0';

    /*inserting register number into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= \
    (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? num << 7 : num << 3;
}

void process_direct_register(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int num;

    if(!operation_table[opcode].addressing_method[operand_num - 1][2])
    {
        printf(ERROR_MESSAGE, "direct register addressing method is not allowed");
        file_info->error_status = 1;
        return;
    }

    token =  token + 1; /*getting rid of 'r'*/
    if(token[0] < '0' || token[0] > '7')
    {
        printf(ERROR_MESSAGE, "invalid register");
        file_info->error_status = 1;
        return;
    }
    if(token[1] != '\0')
    {   
        if(isdigit(token[1]))
        {
            printf(ERROR_MESSAGE, "invalid register");
        }
        else
        {
            printf(ERROR_MESSAGE, "invalid operand");
        }
        file_info->error_status = 1;
    }

    /*inserting 'A' field into the instruction and information word*/
    machine_code_image->instruction_array[machine_code_image->IC] |= 1 << 2;
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= 1 << 2;
    /*inserting addressing method 3 into source or target. If there is only one operand the method is inserted into the target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= \
    (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? 1 << 10 : 1 << 6;

    num = token[0] - '0';

    /*inserting register number into the information word*/
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= \
    (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? num << 7 : num << 3;
}

void process_direct(char *token, int opcode, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    if(!operation_table[opcode].addressing_method[operand_num - 1][1])
    {
        printf(ERROR_MESSAGE, "direct addressing method is not allowed");
        file_info->error_status = 1;
        return;
    }

    /*inserting 'A' field into the instruction word*/
    machine_code_image->instruction_array[machine_code_image->IC] |= 1 << 2;
    /*inserting addressing method 1 into source or target. If there is only one operand the method is inserted into the target*/
    machine_code_image->instruction_array[machine_code_image->IC] |= \
    (operand_num == 1 && operation_table[opcode].num_of_operands == 2)? 1 << 8 : 1 << 4;
}