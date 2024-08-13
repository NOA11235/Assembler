#include "second_pass_table_utils.h"
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*for the second pass*/

void process_label_operands(FileInfo *file_info, Tables *tables, MachineCodeImage *machine_code_image)
{
    int symbol_found;
    SymbolTableNode *current_symbol;
    OperandTableNode *current_operand = tables->operand_label_table_head;
    while (current_operand != NULL)
    {   
        symbol_found = 0;
        current_symbol = tables->symbol_table_head;
        while (current_symbol != NULL)
        {
            if (strcmp(current_operand->name, current_symbol->name) == 0)
            {
                machine_code_image->instruction_array[current_operand->position_in_instruction_array] = current_symbol->address << 3;
                /*if the label is external, then E=1, otherwise R=1*/
                machine_code_image->instruction_array[current_operand->position_in_instruction_array] |= (current_symbol->is_extern)? 1 : 1<<1;
                symbol_found = 1;
                break;
            }
            current_symbol = current_symbol->next;
        }
        if (!symbol_found)
        {
            printf("%s.am:%d: error: label was not defined in the file\n", file_info->base_filename, current_operand->position_in_file);
            file_info->error_status = 1;
        }
        current_operand = current_operand->next;
    }
}

void print_entry_labels(FileInfo *file_info, Tables *tables)
{
    SymbolTableNode *current_label = tables->symbol_table_head;
    FILE *ent_file = NULL;

    char *filename = malloc(strlen(file_info->base_filename) + 5); /*+5 for ".ent" and '\0'*/
    if(filename == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    sprintf(filename, "%s.ent", file_info->base_filename);

    while(current_label != NULL)
    {
        if(current_label->is_entry)
        {
            /*if file didn't exit yet, create and open it*/
            if(ent_file == NULL) 
            {
                ent_file = fopen(filename, "w");
                if (ent_file == NULL) 
                {
                    printf("Error opening file");
                    exit(EXIT_FAILURE);
                }
            }
            /*write to file*/
            fprintf(ent_file, "%s %04d\n", current_label->name, current_label->address);
        }
        current_label = current_label->next;
    }

    /*close ent_file if it was opened*/
    if(ent_file != NULL) 
    {
        fclose(ent_file);
    }
    free(filename);
}

void print_extern_labels(FileInfo *file_info, Tables *tables)
{
    SymbolTableNode *current_label = tables->symbol_table_head;
    OperandTableNode *current_operand_label;
    FILE *ext_file = NULL;

    char *filename = malloc(strlen(file_info->base_filename) + 5); /*+5 for ".ext" and '\0'*/
    if(filename == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    sprintf(filename, "%s.ext", file_info->base_filename);

    while(current_label != NULL)
    {
        current_operand_label = tables->operand_label_table_head;
        while(current_operand_label != NULL)
        {
            if(strcmp(current_label->name, current_operand_label->name) == 0 && current_label->is_extern)
            {
                /*if file didn't exit yet, create and open it*/
                if (ext_file == NULL) 
                {
                    ext_file = fopen(filename, "w");
                    if (ext_file == NULL) 
                    {
                        printf("Error opening file");
                        exit(EXIT_FAILURE);
                    }
                }
                /*write to file*/
                fprintf(ext_file, "%s %04d\n", current_label->name, current_operand_label->position_in_instruction_array + FIRST_ADDRESS);
            }
            current_operand_label = current_operand_label->next;
        }
        current_label = current_label->next;
    }
    /*close ent_file if it was opened*/
    if (ext_file != NULL) 
    {
        fclose(ext_file);
    }
    free(filename);
}

void free_tables(Tables *tables)
{
    MacroTableNode *current_macro = tables->macro_table_head;
    MacroTableNode *next_macro;
    SymbolTableNode *current_symbol = tables->symbol_table_head;
    SymbolTableNode *next_symbol;
    OperandTableNode *current_operand = tables->operand_label_table_head;
    OperandTableNode *next_operand;

    while (current_macro != NULL)
    {
        next_macro = current_macro->next;
        free(current_macro->content);
        free(current_macro);
        current_macro = next_macro;
    }
    while (current_symbol != NULL)
    {
        next_symbol = current_symbol->next;
        free(current_symbol);
        current_symbol = next_symbol;
    }
    while (current_operand != NULL)
    {
        next_operand = current_operand->next;
        free(current_operand);
        current_operand = next_operand;
    }
}