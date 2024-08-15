#include "pre_assembler_utils.h"
#include "pre_assembler_table_utils.h"
#include "defs.h"
#include "parser_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *create_am_file(const char *filename)
{
    FILE *am_file;
    char *am_filename = (char *)malloc(strlen(filename) + 4); /*+4 for ".am and \0"*/
    if(am_filename == NULL)
    {
        printf("Allocation error\n");
        exit(EXIT_FAILURE);
    }
    /*getting the filename*/
    sprintf(am_filename, "%s.am", filename);

    am_file = fopen(am_filename, "w+");
    free(am_filename); /*free the filename string now because we might exit because an error accured*/
    if(am_file == NULL)
    {
        printf("Error: %s file not found\n", am_filename);
        exit(EXIT_FAILURE);
    }

    return am_file;
}

void process_macro_definition(char *line, FileInfo *file_info, Tables *tables)
{
    char *token;

    token = strtok(line, " \t\n"); /*this token consists of "macr"*/
    token = strtok(NULL, " \t\n"); /*this token consists of the macro name*/

    /*cheching if macro name is to long*/
    if(strlen(token) > MAX_MACRO_NAME_LENGTH)
    {
        printf(MACRO_ERROR_MESSAGE, "error: macro name is too long");
        file_info->error_status = 1;
        return;
    }

    if(is_reserved_word(token))
    {
        printf(MACRO_ERROR_MESSAGE, "error: macro name is a reserved word");
        file_info->error_status = 1;
        return;
    }
    
    /*cheching if macro name is already exists*/
    if(macro_name_already_exists(token, tables))
    {
        printf(MACRO_ERROR_MESSAGE, "error: macro name already exists");
        file_info->error_status = 1;
        return;
    }

    /*if the macro name is valid, add it to the macro table*/
    add_macro_to_macro_table(token, tables);

    if((token = strtok(NULL, " \t\n"))) /*if there is more text after the macro name*/
    {
        printf(MACRO_ERROR_MESSAGE, "error: extranous text after macro name");
        file_info->error_status = 1;
    }
}

void process_end_of_macro_definition(char *line, FileInfo *file_info, Tables *tables)
{
    char *token = strtok(line, " \t\n"); /*this token consists of "endmacr"*/

    if((token = strtok(NULL, " \t\n"))) /*if there is more text after "endmacr"*/
    {
        printf(MACRO_ERROR_MESSAGE, "error: extranous text after end of macro definition");
        file_info->error_status = 1;
    }
}

void free_macro_table(Tables *tables)
{
    MacroTableNode *current = tables->macro_table_head;
    MacroTableNode *next;
    
    while(current != NULL)
    {
        next = current->next;
        free(current->content);
        free(current);
        current = next;
    }
}