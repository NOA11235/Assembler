#include "second_pass_table_utils.h"
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*for the second pass*/

void process_label_operands(FileInfo *file_info, Tables *tables, MachineCodeImage *machine_code_image)
{
    int label_found;
    SymbolTableNode *current_label;
    OperandTableNode *current_operand = tables->operand_label_table_head;
    /*transversing the operand label table*/
    while (current_operand != NULL)
    {   
        label_found = 0;
        current_label = tables->symbol_table_head;
        /*transversing the symbol table to find the label*/
        while (current_label != NULL)
        {
            if (strcmp(current_operand->name, current_label->name) == 0)
            {
                /*inserting 'A' into label word*/
                machine_code_image->instruction_array[current_operand->position_in_instruction_array] = current_label->address << LABEL_OFFSET;
                /*if the label is external, then E=1, otherwise R=1*/
                machine_code_image->instruction_array[current_operand->position_in_instruction_array] |= (current_label->is_extern)? SET_E_FIELD : SET_R_FIELD;
                label_found = 1;
                break;
            }
            current_label = current_label->next;
        }
        if (!label_found) /*label wasn't found*/
        {
            printf("%s.am:%d: error: invalid addressing method (or non-existent label / register)\n", file_info->base_filename, current_operand->position_in_file);
            file_info->error_status = 1;
        }
        current_operand = current_operand->next;
    }
}

void print_entry_labels(FileInfo *file_info, Tables *tables)
{
    SymbolTableNode *current_label = tables->symbol_table_head;
    FILE *ent_file = NULL;

    /*creating the filename*/
    char *filename = malloc(strlen(file_info->base_filename) + 5); /*+5 for ".ent" and '\0'*/
    if(filename == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    sprintf(filename, "%s.ent", file_info->base_filename);

    /*transversing the symbol table*/
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

    /*creating the filename*/
    char *filename = malloc(strlen(file_info->base_filename) + 5); /*+5 for ".ext" and '\0'*/
    if(filename == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    sprintf(filename, "%s.ext", file_info->base_filename);

    /*transversing the symbol table*/
    while(current_label != NULL)
    {
        /*checking if the label is external*/
        if(current_label->is_extern)
        {
            current_operand_label = tables->operand_label_table_head;
            /*transversing the operand label table*/
            while(current_operand_label != NULL)
            {
                if(strcmp(current_label->name, current_operand_label->name) == 0)
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
    SymbolTableNode *current_label = tables->symbol_table_head;
    SymbolTableNode *next_label;
    OperandTableNode *current_operand = tables->operand_label_table_head;
    OperandTableNode *next_operand;

    while(current_macro != NULL)
    {
        next_macro = current_macro->next;
        free(current_macro->content);
        free(current_macro);
        current_macro = next_macro;
    }
    while(current_label != NULL)
    {
        next_label = current_label->next;
        free(current_label);
        current_label = next_label;
    }
    while(current_operand != NULL)
    {
        next_operand = current_operand->next;
        free(current_operand);
        current_operand = next_operand;
    }
}