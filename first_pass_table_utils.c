#include "defs.h"
#include <string.h>
#include <stdlib.h>

/*for the first pass*/
void add_label_to_table(Tables *tables, char *name, int address, int is_data)
{
    LabelTableNode *new_node = (LabelTableNode *)malloc(sizeof(LabelTableNode));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->name, name);
    new_node->address = address;
    new_node->is_data = is_data;
    new_node->next = tables->label_table_head;
    tables->label_table_head = new_node;
}

void add_entry_to_table(Tables *tables, char *name)
{
    EntryTableNode *new_node = (EntryTableNode *)malloc(sizeof(EntryTableNode));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->name, name);
    new_node->next = tables->entry_table_head;
    tables->entry_table_head = new_node;
}

void add_extern_to_table(Tables *tables, char *name)
{
    ExternTableNode *new_node = (ExternTableNode *)malloc(sizeof(ExternTableNode));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->name, name);
    new_node->next = tables->extern_table_head;
    tables->extern_table_head = new_node;
}

void add_operand_to_table(Tables *tables, char *name, int position_in_instruction_array, int position_in_file)
{
    OperandTableNode *new_node = (OperandTableNode *)malloc(sizeof(OperandTableNode));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->name, name);
    new_node->position_in_instruction_array = position_in_instruction_array;
    new_node->position_in_file = position_in_file;
    new_node->next = tables->operand_label_table_head;
    tables->operand_label_table_head = new_node;
}