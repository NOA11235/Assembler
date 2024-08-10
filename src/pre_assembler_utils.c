#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void process_macro_definition(char *line, FileInfo *file_info, Tables *tables)
{
    char *token;
    int i;

    line = line + 5; /*getting rid of "macr ", +5 for "macr "*/
    token = strtok(line, " \t"); /*this token consists of the macro name*/

    /*cheching if macro name is a data name*/
    for(i = 0; i < NUM_OF_DATA; i++)
    {
        if(strcmp(token, data_table[i].name) == 0)
        {
            printf(ERROR_MESSAGE, "error: macro name is identical to a data name");
            file_info->error_status = 1;
        }
    }

    /*cheching if macro name is to long*/
    if(strlen(token) > MAX_MACRO_NAME_LENGTH)
    {
        printf(ERROR_MESSAGE, "error: macro name is too long");
        file_info->error_status = 1;
    }

    /*cheching if macro name is an operation name*/
    for(i = 0; i < NUM_OF_OP; i++)
    {
        if(strcmp(token, operation_table[i].name) == 0)
        {
            printf(ERROR_MESSAGE, "error: macro name is identical to an operation name");
            file_info->error_status = 1;
        }
    }
    
    /*cheching if macro name is already exists*/
    if(macro_name_already_exists(token, tables))
    {
        printf(ERROR_MESSAGE, "error: macro name already exists");
        file_info->error_status = 1;
    }

    if(!(token = strtok(NULL, " \t"))) /*if there is more text after the macro name*/
    {
        printf(ERROR_MESSAGE, "error: extranous text after macro name");
        file_info->error_status = 1;
    }

    /*if the macro name is valid, add it to the macro table*/
    add_macro_to_macro_table(token, tables);
}

void process_end_of_macro_definition(char *line, FileInfo *file_info, Tables *tables)
{
    char *token = strtok(line, " \t"); /*this token consists of "endmacr"*/
    if(!(token = strtok(NULL, " \t")))
    {
        printf(ERROR_MESSAGE, "error: extranous text after end of macro definition");
        file_info->error_status = 1;
    }
}

void add_content_to_macro(char *line, FileInfo *file_info, Tables *tables)
{

}

int find_macro_and_print(char *line, FileInfo *file_info, Tables *tables)
{

}