#include "instruction_utilities.h"
#include "first_pass_common.h"
#include "tables.h"
#include <ctype.h>

void process_immediate(char *token, int operand_num, int word_count)
{
    int i, num;
    token = token + 1;
    for(i = 0; i < strlen(token); i++)
    {
        if(!isdigit(token[i]))
        {
            printf(ERROR_MESSAGE, "immediate value must be a number");
            error_flag = 1;
            return;
        }
    }
    
    instruction_array[IC] |= 1 << 2; /* 'A' field is 1*/
    instruction_array[IC] |= (operand_num == 1)? 1 << 7 : 1 << 3; /*inserting addressing method 0*/
    /*inserting immediate value into the the information word*/
    num = atoi(token);
    instruction_array[IC + word_count] |= num << 3;
}

void process_register(char *token, int operand_num, int word_count, int is_direct)
{
    int num;
    token = (is_direct)? token + 1: token + 2;

    if(token[0] < '0' && token[0] > '7')
    {
        printf(ERROR_MESSAGE, "invalid register");
        error_flag = 1;
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
        error_flag = 1;
    }

    instruction_array[IC] |= 1 << 2; /* 'A' field is 1*/
    /*inserting addressing method 2 or 3 into source or target*/
    if(is_direct)
    {
        instruction_array[IC] |= (operand_num == 1)? 1 << 10 : 1 << 6;
    }
    else
    {
        instruction_array[IC] |= (operand_num == 1)? 1 << 9 : 1 << 5;
    }

    /*inserting register number into the the information word*/
    num = atoi(token);
    instruction_array[IC + word_count] |= (operand_num == 1)? num << 7 : num << 3;
}
