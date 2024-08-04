#include "first_pass_utilities.h"
#include "definitions.h"
#include "parser_utilities.h"
#include "data_utilities.h"
#include "instruction_utilities.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_empty(char line[])
{
    int i;
    for(i = 0; i < strlen(line); i++)
    {
        if(line[i] != ' ' && line[i] != '\t')
        {
            return 0;
        }
    }
    return 1;
}

int is_comment(char line[])
{
    if(line[0] == ';')
    {
        return 1;
    }
    return 0;
}

int is_data(char line[])
{
    int i;
    for(i = 0; i < NUM_OF_DATA; i++)
    {
        if(strstr(line, data_table[i].name) != NULL)
        {
            return 1;
        }
    }
    return 0;
}

int is_instruction(char line[])
{
    int i;
    for(i = 0; i < NUM_OF_OP; i++)
    {
        if(strstr(line, operation_table[i].name) != NULL)
        {
            return 1;
        }
    }
    return 0;
}

void process_label(char **line, FileInfo *file_info, Tables *tables, int counter)
{
    char label[MAX_LABEL_LENGTH], *data_name;
    int is_data_label = 0;
    sscanf(*line, "%s", label);
    label[strlen(label)-1] = '\0'; /*remove ':'*/
    sscanf(*line, "%s", data_name);
    if(strcmp(data_name, data_table[2].name) == 0 || strcmp(data_name, data_table[3].name) == 0)
    {
        printf(ERROR_MESSAGE, "warning: label cannot be an entry or extern");
        file_info->error_status = 1;
    }
    if(strcmp(data_name, data_table[0].name) == 0 || strcmp(data_name, data_table[1].name) == 0)
    {
        is_data_label = 1;
    }

    add_label_to_table(tables, label, counter, is_data_label);
    *line = *line + strlen(label) + 1; /*+1 for ':'*/
}

void process_data(char *line, FileInfo *file_info, Tables *tables, MachineCodeImage *machine_code_image)
{
    char data_name[MAX_DATA_NAME_LEN];
    sscanf(line, "%s", data_name);
    line = line + strlen(data_name);
    if(strcmp(data_name, data_table[0].name) == 0)
    {
        process_data_data(line, file_info, machine_code_image);
    }
    else if(strcmp(data_name, data_table[1].name) == 0)
    {
        process_string_data(line, file_info, machine_code_image);
    }
    else if(strcmp(data_name, data_table[2].name) == 0)
    {
        process_entry_data(line, tables);
    }
    else if(strcmp(data_name, data_table[3].name) == 0)
    {
        process_extern_data(line, tables);
    }
    else
    {
        printf(ERROR_MESSAGE, "invalid data name");
        file_info->error_status = 1;
    }
}

void process_instruction(char line[], FileInfo *file_info, Tables *tables, MachineCodeImage *machine_code_image)
{
    char *token;
    char *op_name;
    int i, op_code;
    int source_register_flag = 0; /*keeps track if the source operand addressing method is 2 or 3*/
    int word_count = 0; /*keeps track of the number of information words in the instruction_array*/
    int comma_flag = 0; /*flag for indecating the comma is expected in the beginning of next data*/
    int *operand_address_method;

    token = strtok(line, " \t");/*this token consists of the operation name*/

    /*getting the operation code*/
    for(op_code = 0; op_code < NUM_OF_OP; op_code++)
    {
        if(strcmp(token, operation_table[op_code].name) != NULL)
        {
            machine_code_image->instruction_array[machine_code_image->IC] = operation_table[op_code].code << 11;
            break;
        }
    }

    /*processing the command*/
    for(i = 0; i < operation_table[op_code].num_of_operands; i++)
    {
        token = strtok(NULL, " \t"); /*this token consists of the operand*/
        token = comma_parser(token, &comma_flag, file_info);
    
        /*getting the addressing method*/
        operand_address_method = (i == 0)? operation_table[op_code].source_address_method : operation_table[op_code].target_address_method;

        if(token[0] == '#')
        {
            if(!operand_address_method[0])
            {
                printf(ERROR_MESSAGE, "direct addressing method is not allowed");
                file_info->error_status = 1;
                continue;
            }
            process_immediate(token, i+1, ++word_count, file_info, machine_code_image);
        }
        else if(token[0] == '*' && token[1] == 'r' && isdigit(token[2]))
        {
            if(!operand_address_method[2])
            {
                printf(ERROR_MESSAGE, "indirect register addressing method is not allowed");
                file_info->error_status = 1;
                continue;
            }
            source_register_flag = (i == 0)? 1 : 0;
            if(i == 0 || !source_register_flag)
            {
                ++word_count;
            }
            process_register(token, i+1, word_count, 0, file_info, machine_code_image);
        }
        else if(token[0] == 'r' && isdigit(token[1]))
        {
            if(!operand_address_method[3])
            {
                printf(ERROR_MESSAGE, "direct register addressing method is not allowed");
                file_info->error_status = 1;
                continue;
            }
            source_register_flag = (i == 0)? 1 : 0;
            if(i == 0 || !source_register_flag)
            {
                ++word_count;
            }
            process_register(token, i+1, word_count, 1, file_info, machine_code_image);
        }
        else if(is_label(token))
        {
            if(!operand_address_method[1])
            {
                printf(ERROR_MESSAGE, "direct addressing method is not allowed");
                file_info->error_status = 1;
                continue;
            }
            add_operand_to_table(tables, token, machine_code_image->IC + (++word_count), file_info->line_count);
        }
        else
        {
            printf(ERROR_MESSAGE, "there is no such addressing method");
            file_info->error_status = 1;
        }
    }
    machine_code_image->IC += word_count+1;
}