#include "pre_assembler_table_utils.h"
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

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
    strcpy(new_node->name = name);
    new_node->next = tables->macro_table_head;
    tables->macro_table_head = new_node;
}