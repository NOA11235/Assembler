#include "parser_utils.h"
#include "first_pass_table_utils.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

char *comma_parser(char *token, int *comma_flag, FileInfo *file_info)
{
    char *tmp_ptr;
    /*if there is a  comma at the beginning of the token*/
    if(token[0] == ',')
    {
        if(*comma_flag)
        {
            *comma_flag = 0;
        }
        else /*there is a comma at the beginning of the token and commas flag isn't set*/
        {
            printf(ERROR_MESSAGE, "consecutive commas");
            file_info->error_status = 1;
        }
        if(strcmp(token, ",") == 0) /*if the token is only a comma*/
        {
            token = strtok(NULL, " \t\n");
        }
        else
        {
            token++;
        }
    }

    if(*comma_flag) /*if there isn't a comma in the beginnig of the token and comma flag is set*/
    {
        printf(ERROR_MESSAGE, "error: missing comma");
        file_info->error_status = 1;
    }

    *comma_flag = 1;

    /*getting rid of the comma at the end*/
    if(token[strlen(token)-1] == ',')
    {
        *comma_flag = 0;
        if(token[strlen(token)-2] == ',') /*if there consecutive commas the end of the token*/
        {
            token[strlen(token)-2] = '\0';
            printf(ERROR_MESSAGE, "error: consecutive commas");
            file_info->error_status = 1;
        }

        token[strlen(token)-1] = '\0';
    }
    /*if there is a comma in the middle of the token*/
    else if((tmp_ptr = strchr(token, ',')))
    {
        *comma_flag = 0;
        *tmp_ptr = ' ';
        token = strtok(token, " \t\n"); /*getting the first part of the token*/
    }

    return token;
}

char *walkthrough_white_spaces(char *line)
{
    while(*line == ' ' || *line == '\t')
    {
        line++;
    }
    return line;
}

int read_line(char *line, FileInfo *file_info)
{
    /*reading the next line from file*/
    if(!fgets(line, MAX_LINE_LENGTH+2, file_info->input_file))
    {
        return 0;
    }

    /*Updating the line count*/
    file_info->line_count++;
    /*checking if the line is too long (more than 80 characters)*/
    if(line[strlen(line)-1] != '\n' && !feof(file_info->input_file))
    {
        printf(ERROR_MESSAGE, "error: line is too long");
        file_info->error_status = 1;
    }
    return 1;
}

int is_register(char *token)
{
    if(token[0] == 'r' && token[1] >= '0' && token[1] <= '7' && token[2] == '\0')
    {
        return 1;
    }
    return 0;
}

int is_reserved_word(char *name)
{
    int i;
    for(i = 0; i < NUM_OF_DATA; i++)
    {
        if(strcmp(name, data_table[i].name) == 0)
        {
            return 1;
        }
    }

    for(i = 0; i < NUM_OF_OP; i++)
    {
        if(strcmp(name, operation_table[i].name) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int is_valid_integer(char *token)
{
    int i;

    if(token[0] == '-' || token[0] == '+')
    {
        token++;
    }

    for(i = 0; i < strlen(token); i++)
    {
        if(token[i] < '0' || token[i] > '9')
        {
            return 0;
        }
    }
        return 1;
        return 1;
    return 1;
}

int is_valid_label(char *token, FileInfo *file_info, Tables *tables)
{
    int i;

    if(!isalpha(token[0]))
    {
        printf(ERROR_MESSAGE, "error: label must start with a letter");
        file_info->error_status = 1;
        return 0;
    }

    for(i = 1; i < strlen(token); i++)
    {
        if(!isalnum(token[i]))
        {
            printf(ERROR_MESSAGE, "error: label must contain only letters and digits");
            file_info->error_status = 1;
            return 0;
        }
    }

    if(strlen(token) > MAX_LABEL_LENGTH)
    {
        printf(ERROR_MESSAGE, "error: label is too long");
        return 0;
    }

    if(is_reserved_word(token))
    {
        printf(ERROR_MESSAGE, "error: label is identical to a reserved word");
        return 0;
    }

    if(is_macro_name(token, tables))
    {   
        printf(ERROR_MESSAGE, "error: label is identical to a macro name");
        return 0;
    }

    return 1;
}

int calculate_two_complement(char *token, int num_of_bits, FileInfo *file_info)
{
    int num, is_negitive = 0;

    if(token[0] == '+' || token[0] == '-')
    {
        if(token[0] == '-')
        {
            is_negitive = 1;
        }
        token++;
    }

    num = atoi(token);

    /*checking if the number is in range*/
    if(num < -pow(2, num_of_bits - 1) || num >= pow(2, num_of_bits - 1))
    {
        printf(ERROR_MESSAGE, "error: number is out of range");
        file_info->error_status = 1;
    }

    /*calculating the number in two's complement*/
    if(is_negitive)
    {
        num = (~num) + 1; /*calculating the two's complement*/
        num = num & ((1 << num_of_bits) - 1); /*making sure the number is num_of_bits bits long*/
    }
    return num;
}