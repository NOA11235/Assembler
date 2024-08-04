#include "instruction_utils.h"
#include "defs.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void process_immediate(char *token, int operand_num, int word_count, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int i, num;
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
    
    machine_code_image->instruction_array[machine_code_image->IC] |= 1 << 2; /* 'A' field is 1*/
    machine_code_image->instruction_array[machine_code_image->IC] |= (operand_num == 1)? 1 << 7 : 1 << 3; /*inserting addressing method 0*/
    /*inserting immediate value into the the information word*/
    num = atoi(token);
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= num << 3;
}

void process_register(char *token, int operand_num, int word_count, int is_direct, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int num;
    token = (is_direct)? token + 1: token + 2;

    if(token[0] < '0' && token[0] > '7')
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

    machine_code_image->instruction_array[machine_code_image->IC] |= 1 << 2; /* 'A' field is 1*/
    /*inserting addressing method 2 or 3 into source or target*/
    if(is_direct)
    {
        machine_code_image->instruction_array[machine_code_image->IC] |= (operand_num == 1)? 1 << 10 : 1 << 6;
    }
    else
    {
        machine_code_image->instruction_array[machine_code_image->IC] |= (operand_num == 1)? 1 << 9 : 1 << 5;
    }

    /*inserting register number into the the information word*/
    num = atoi(token);
    machine_code_image->instruction_array[machine_code_image->IC + word_count] |= (operand_num == 1)? num << 7 : num << 3;
}
