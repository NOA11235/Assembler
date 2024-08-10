#include "defs.h"
#include <stdlib.h>

int is_valid_macro_name(char *name)
{
    
}

void process_macro_definition(char *line, FileInfo *file_info, Tables *tables)
{
    char macro_name[MAX_MACRO_NAME_LENGTH];
    MacroTableNode *new_macro = (MacroTableNode*)malloc(sizeof(MacroTableNode));
    if (new_macro == NULL)
    {
        printf("Allocation error\n");
        exit(EXIT_FAILURE);
    }

    line = line + 5; /*getting rid of "macr ", +5 for "macr "*/
    sscanf(line, "%s", macro_name);
 
    if (!is_valid_macro_name(macro_name))
    {
        printf(ERROR_MESSAGE, "error: invalid macro name");
        file_info->error_status = 1;
    }

    strcpy(new_macro->name, macro_name);
    new_macro->next = tables->macro_table_head;
    tables->macro_table_head = new_macro;
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