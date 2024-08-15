#include "parser_utils.h"
#include "first_pass_table_utils.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void validate_commas(char *line, FileInfo *file_info)
{
    /*checking if the line starts with a comma*/
    line = walkthrough_white_spaces(line);
    if(*line == ',')
    {
        printf(ERROR_MESSAGE, "error: unnecessary comma after the operation");
        file_info->error_status = 1;
        line++;
    }

    while(*line != '\n' && *line != '\0') /*while the line isn't over*/
    {
        /*checking if the line starts with a comma*/
        line = walkthrough_white_spaces(line);
        if(*line == ',')
        {
            printf(ERROR_MESSAGE, "error: consecutive commas");
            file_info->error_status = 1;
            line++;
            line = walkthrough_white_spaces(line);
        }
        /*walking through the text*/
        while(*line != ' ' && *line != '\t' && *line != '\n' && *line != '\0' && *line != ',')
        {
            line++;
        }
        /*checking if the line ends with a comma*/
        line = walkthrough_white_spaces(line);
        /*if we haven't reached the end of the line yet*/
        if(*line != ',' && *line != '\n' && *line != '\0')
        {
            /*extraneous text after the end of the command will also print an error about missing commas*/
            printf(ERROR_MESSAGE, "error: missing comma between operands");
            file_info->error_status = 1;
        }
        else if(*line == ',')
        {
            line++;
            line = walkthrough_white_spaces(line);
            if(*line == '\n' || *line == '\0')
            {
                printf(ERROR_MESSAGE, "error: unnecessary comma at the end of the command");
                file_info->error_status = 1;
            }
        }
    }
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
    if(token[0] == 'r' && token[1] >= '0' && token[1] <= ('0' + MAX_REGISTER_NUMBER) && token[2] == '\0')
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

    for(i = 0; i < NUM_OF_OPERATIONS; i++)
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
        if(!isdigit(token[i]))
        {
            return 0;
        }
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