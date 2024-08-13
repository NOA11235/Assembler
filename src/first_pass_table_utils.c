#include "defs.h"
#include <string.h>
#include <stdlib.h>


void add_label_to_table(char *name, int address, char *type, FileInfo *file_info, Tables *tables)
{
    SymbolTableNode *new_node;
    SymbolTableNode *current = tables->symbol_table_head;
    while(current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            /*instruction or data label can't be already defined or an external label*/
            if(strcmp(type, "instruction") == 0 || strcmp(type, "data") == 0)
            {
                /*if the label was already defined in the file*/
                if(current->is_instruction || current->is_data)
                {
                    printf(ERROR_MESSAGE, "error: label was already defined in the file");
                    file_info->error_status = 1;
                    return;
                }
                /*if the label was already defined as an external label*/
                if(current->is_extern)
                {
                    printf(ERROR_MESSAGE, "error: label was already defined as an external label");
                    file_info->error_status = 1;
                    return;
                }

                current->address = address + FIRST_ADDRESS; /*setting the address of the label*/

                if(strcmp(type, "instruction") == 0)
                {
                    current->is_instruction = 1;
                }
                else
                {
                    current->is_data = 1;
                }
            }
            /*entry label can't be already defined as an extern label*/
            else if(strcmp(type, "entry") == 0)
            {
                if(current->is_extern)
                {
                    printf(ERROR_MESSAGE, "error: label was already defined as an extern label");
                    file_info->error_status = 1;
                    return;
                }
                current->is_entry = 1;
            }
            /*extern label can't be already defined as a code or data or entry label*/
            else if(strcmp(type, "extern") == 0)
            {
                if(current->is_instruction || current->is_data)
                {
                    printf(ERROR_MESSAGE, "error: label was already defined in the file");
                    file_info->error_status = 1;
                    return;
                }
                if(current->is_entry)
                {
                    printf(ERROR_MESSAGE, "error: label was already defined as an entry label");
                    file_info->error_status = 1;
                    return;
                }
                current->is_extern = 1;
            }
            return;
        }
        current = current->next;
    }

    /*if the label isn't in the symbol table*/
    new_node = (SymbolTableNode *)malloc(sizeof(SymbolTableNode));
    memset(new_node, 0, sizeof(SymbolTableNode)); /*initialize the new node*/
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(new_node->name, name);
    new_node->position_in_file = file_info->line_count;
    /*adding the new node to the head of the symbol table*/
    new_node->next = tables->symbol_table_head;
    tables->symbol_table_head = new_node;
    /*setting the address and type of the label*/
    if(strcmp(type, "instruction") == 0)
    {
        new_node->address = address + FIRST_ADDRESS;
        new_node->is_instruction = 1;
    }
    else if(strcmp(type, "data") == 0)
    {
        new_node->address = address + FIRST_ADDRESS;
        new_node->is_data = 1;
    }
    else if(strcmp(type, "entry") == 0)
    {
        new_node->is_entry = 1;
    }
    else if(strcmp(type, "extern") == 0)
    {
        new_node->address = 0;
        new_node->is_extern = 1;
    }
}

void add_operand_to_table(char *name, int position_in_instruction_array, int position_in_file, Tables *tables)
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

int is_macro_name(char *name, Tables *tables)
{
    MacroTableNode *current = tables->macro_table_head;
    while(current != NULL)
    {
        if(strcmp(current->name, name) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void add_offset_to_data_labels(Tables *tables, int data_offset)
{
    SymbolTableNode *current = tables->symbol_table_head;
    while(current != NULL)
    {
        if(current->is_data)
        {
            current->address += data_offset;
        }
        current = current->next;
    }
}

void validate_entry_labels(FileInfo *file_info, Tables *tables)
{
    SymbolTableNode *current = tables->symbol_table_head;
    while(current != NULL)
    {
        if(current->is_entry)
        {
            if(!current->is_instruction && !current->is_data)
            {
                printf("%s.am:%d: error: entry label wasn't defined in the file\n", file_info->base_filename, current->position_in_file);
                file_info->error_status = 1;
            }
        }
        current = current->next;
    }
}