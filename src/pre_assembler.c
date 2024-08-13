#include "pre_assembler.h"
#include "pre_assembler_utils.h"
#include "pre_assembler_table_utils.h"
#include "defs.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *interpret_macro(FileInfo *file_info, Tables *tables)
{
    char line[MAX_LINE_LENGTH + 2]; /*+2 for '\n' and '\0'*/
    char first_word[MAX_MACRO_NAME_LENGTH + 2]; /*+2 for an extra character and '\0'*/
    int macro_definition_flag = 0;
    FILE *am_file = NULL;
    char *am_filename = (char *)malloc(strlen(file_info->base_filename) + 4); /*+4 for ".am and \0"*/

    /*an am_file will be created, but if an error will be detected in the macro interpretation then the file will be deleted*/
    am_file = create_am_file(file_info->base_filename);

    while(read_line(line, file_info))
    {   
        sscanf(line, "%s", first_word); /*get the first word in the line*/

        if(strcmp(first_word, "macr") == 0) 
        {
            macro_definition_flag = 1;
            process_macro_definition(line, file_info, tables);
        }
        else if(strcmp(first_word, "endmacr") == 0) 
        {
            macro_definition_flag = 0;
            process_end_of_macro_definition(line, file_info, tables);
        }
        else if(!file_info->error_status) /*if there wasn't any error detected yet*/
        {
            if(macro_definition_flag)
            {
                /*add the content of the macro to the macro table*/
                add_content_to_macro(line, file_info, tables);
            }
            else if(!find_macro_and_print(first_word, am_file, file_info, tables)) /*if the line isn't a macro*/
            {
                /*print the line to the .am file*/
                fputs(line, am_file);
            }
        }
    }

    if(file_info->error_status)
    {
        fclose(am_file);
        remove(am_filename);
        free(am_filename);
        return NULL;
    }
    free(am_filename);
    return am_file;
}