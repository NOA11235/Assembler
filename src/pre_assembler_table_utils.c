#include "pre_assembler_table_utils.h"
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int macro_name_already_exists(char *name, Tables *tables)
{
    MacroTableNode *current = tables->macro_table_head;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void add_macro_to_macro_table(char *name, Tables *tables)
{
    MacroTableNode *new_node = (MacroTableNode *)malloc(sizeof(MacroTableNode));
    if (new_node == NULL)
    {
        printf("Allocation error\n");
        exit(EXIT_FAILURE);
    }
    memset(new_node, 0, sizeof(MacroTableNode));
    strcpy(new_node->name, name);
    new_node->next = tables->macro_table_head;
    tables->macro_table_head = new_node;
}

void add_content_to_macro(char *line, FileInfo *file_info, Tables *tables)
{
    char *new_content;

    /*if the content of the macro is empty*/
    if(tables->macro_table_head->content == NULL)
    {
        new_content = (char *)malloc(strlen(line) + 1); /*+1 for '\0'*/
        memset(new_content, 0, strlen(line) + 1);
        if(new_content == NULL)
        {
            printf("Allocation error\n");
            exit(EXIT_FAILURE);
        }
    }
    else /*if the content of the macro is not empty*/
    {
        new_content = (char *)realloc(tables->macro_table_head->content, strlen(tables->macro_table_head->content) + strlen(line) + 1); /*+1 for '\0'*/
        if(new_content == NULL)
        {
            printf("Allocation error\n");
            exit(EXIT_FAILURE);
        }
    }
    tables->macro_table_head->content = new_content;
    strcat(tables->macro_table_head->content, line);
}

int find_macro_and_print(char *line, FILE *am_file, FileInfo *file_info, Tables *tables)
{
    MacroTableNode *current = tables->macro_table_head;
    char *token = strtok(line, " \t\n"); /*this token consists of the might-be macro name without whit spaces*/

    while(current != NULL)
    {
        if(strcmp(token, current->name) == 0)
        {
            fputs(current->content, am_file);
            return 1;
        }
        current = current->next;
    }
    return 0;
}