#include "data_utils.h"
#include "defs.h"
#include "first_pass_table_utils.h"
#include "parser_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <math.h>
#include <ctype.h>

void process_data_data(char *line, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    char *token = strtok(line, " \t");
    int comma_flag = 0; /*flag for indecating the comma is expected in the beginning of next data*/
    int minus_flag = 0; /*flag for indecating that the number is negative*/
    int i, num;
    do
    {
        token = comma_parser(token, &comma_flag, file_info);
        /*checking for sign in the beginning*/
        if(token[0] == '+' || token[0] == '-')
        {
            if(token[0] == '-')
            {
                minus_flag = 1;
            }
            token++;
        }
        /*checking if the data is valid*/
        for(i = 0; i < strlen(token); i++)
        {
            if(!isdigit(token[i]))
            {
                printf(ERROR_MESSAGE, "invalid data");
                file_info->error_status = 1;
            }
        }
        /*converting the data to integer and adding it to the memory picture*/
        num = atoi(token);
        /*calculating the number if the data is negitive so it would be represented in the 2's complement method*/
        if(minus_flag)
        {
            num = (~num) + 1; /*calculating the 2's complement*/
            num = num & 0x7FFF; /*making sure the number is in the range of 15 bits*/
        }
        machine_code_image->data_array[machine_code_image->DC] = num;
        machine_code_image->DC++;
    } while((token = strtok(NULL, " \t")) != NULL);
}

void process_string_data(char *line, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    char *token;
    int i;
    token = strtok(line, "\""); /*this token consists of white spaces*/
    token = strtok(NULL, "\""); /*this token consists of the string*/
    for(i = 0; i < strlen(token); i++)
    {
        machine_code_image->data_array[machine_code_image->DC] = token[i];
        machine_code_image->DC++;
    }

    machine_code_image->data_array[machine_code_image->DC] = '\0'; /*adding '\0' to the end of the string*/
    machine_code_image->DC++;

    /*checking for extraneous text after the end of command*/
    while((token = strtok(NULL, " \t")))
    {
        for(i = 0; i < strlen(token); i++)
        {
            if(token[i] != '\t' && token[i] != ' ')
            {
                printf(ERROR_MESSAGE, "extraneous text after the end of word");
                file_info->error_status = 1;    
                break;
            }
        }
    }
}

void process_entry_data(char *line, Tables *tables)
{
    char *label = strtok(line, " \t"); /*this token consists of label name*/
    add_entry_to_table(tables, label);
}

void process_extern_data(char *line, Tables *tables)
{
    char *label = strtok(line, " \t"); /*this token consists of label name*/
    add_extern_to_table(tables, label);
}
