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
    char *token;
    int num;

    validate_commas(line, file_info);
    token = strtok(line, " ,\t\n");

    do
    {
        /*checking if the data is valid*/
        if(!is_valid_integer(token))
        {
            printf(ERROR_MESSAGE, "error: data must be an integer");
            file_info->error_status = 1;
        }

        /*converting the data to two's complement integer and adding it to the memory picture*/
        num = calculate_two_complement(token, BITS_IN_WORD, file_info);

        machine_code_image->data_array[machine_code_image->DC] = num;
        machine_code_image->DC++;

    } while((token = strtok(NULL, " ,\t\n")) != NULL);
}

void process_string_data(char *line, FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    char *token;
    int i;
    token = strtok(line, "\""); /*this token consists of white spaces*/
    token = strtok(NULL, "\""); /*this token consists of the string*/

    for(i = 0; i < strlen(token); i++)
    {
        machine_code_image->data_array[machine_code_image->DC++] = token[i];
    }

    machine_code_image->data_array[machine_code_image->DC++] = '\0'; /*adding '\0' to the end of the string*/

    /*checking for extraneous text after the end of command*/
    if((token = strtok(NULL, " \t\n")))
    {
        printf(ERROR_MESSAGE, "error: extraneous text after the end of command");
        file_info->error_status = 1;
    }
}

void process_entry_data(char *line, FileInfo *file_info, Tables *tables)
{
    char *label_name = strtok(line, " \t\n"); /*this token consists of label name*/

    add_label_to_table(label_name, 0, "entry", file_info, tables);

    /*checking for extraneous text after the end of command*/
    if(strtok(NULL, " \t\n"))
    {
        printf(ERROR_MESSAGE, "error: extraneous text after the end of command");
        file_info->error_status = 1;
    }
}

void process_extern_data(char *line, FileInfo *file_info, Tables *tables)
{
    char *label_name = strtok(line, " \t\n"); /*this token consists of label name*/

    add_label_to_table(label_name, 0, "extern", file_info, tables);

    /*checking for extraneous text after the end of command*/
    if(strtok(NULL, " \t\n"))
    {
        printf(ERROR_MESSAGE, "error: extraneous text after the end of command");
        file_info->error_status = 1;
    }
}