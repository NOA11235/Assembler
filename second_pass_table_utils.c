#include "second_pass_table_utils.h"
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*for the second pass*/
void add_values_to_label_table(Tables *tables, int data_offset)
{
    LabelTableNode *current = tables->label_table_head;
    while (current != NULL)
    {
        current->address += (current->is_data)? FIRST_ADDRESS + data_offset : FIRST_ADDRESS;
        current = current->next;
    }
}

void process_label_operands(FileInfo *file_info, Tables *tables, MachineCodeImage *machine_code_image)
{
    int address = -1;
    OperandTableNode *current_operand = tables->operand_label_table_head;
    LabelTableNode *current_label;
    ExternTableNode *current_extern;

    while (current_operand != NULL)
    {
        current_label = tables->label_table_head;
        current_extern = tables->extern_table_head;
        while (current_label != NULL)
        {
            if (strcmp(current_operand->name, current_label->name) == 0)
            {
                address = current_label->address;
                break;
            }
            current_label = current_label->next;
        }
        if(address != -1)
        {
            while (current_extern != NULL)
            {
                if (strcmp(current_operand->name, current_extern->name) == 0)
                {
                    address = 0;
                    break;
                }
                current_extern = current_extern->next;
            }
        }
        /*if label is not defined*/
        if (address == -1)
        {
            printf("%s:%d: %s\n", file_info->file_name, tables->operand_label_table_head->position_in_file , "undefined label");
            file_info->error_status = 1;
        }
        /*if label was defined, the E=1 if the label is external and otherwise R=1*/
        else
        {
            machine_code_image->instruction_array[current_operand->position_in_instruction_array] = (address == 0)? (address << 3) | 1  : (address << 3) | (1 << 2);
        }
        current_operand = current_operand->next;
    }

    machine_code_image->instruction_array[tables->operand_label_table_head->position_in_instruction_array] = address;
}

void print_entry_labels(FileInfo *file_info, Tables *tables)
{
    EntryTableNode *current_entry = tables->entry_table_head;    
    LabelTableNode *current_label;
    FILE *ent_file = NULL;

    char *filename = malloc(strlen(file_info->file_name) + 5); /*+5 for ".ent" and '\0'*/
    if(filename == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    sprintf(filename, "%s.ent", file_info->file_name);

    while(current_entry != NULL)
    {
        current_label = tables->label_table_head;
        while(current_label != NULL)
        {
            if(strcmp(current_entry->name, current_label->name) == 0)
            {
                /*if file didn't exit yet, create and open it*/
                if (ent_file == NULL) 
                {
                    ent_file = fopen(filename, "w");
                    if (ent_file == NULL) 
                    {
                        printf("Error opening file");
                        exit(EXIT_FAILURE);
                    }
                }
                /*write to file*/
                fprintf(ent_file, "%s %d\n", current_entry->name, current_label->address);
                break;
            }
            current_label = current_label->next;
        }
        current_entry = current_entry->next;
    }
    /*close ent_file if it was opened*/
    if (ent_file != NULL) 
    {
        fclose(ent_file);
    }
    free(filename);
}

void print_extern_labels(FileInfo *file_info, Tables *tables)
{
    ExternTableNode *current_extern = tables->extern_table_head;
    LabelTableNode *current_label;
    FILE *ext_file = NULL;

    char *filename = malloc(strlen(file_info->file_name) + 5); /*+5 for ".ext" and '\0'*/
    if(filename == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    sprintf(filename, "%s.ext", file_info->file_name);

    while(current_extern != NULL)
    {
        current_label = tables->label_table_head;
        while(current_label != NULL)
        {
            if(strcmp(current_extern->name, current_label->name) == 0)
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
                fprintf(ext_file, "%s %04d\n", current_extern->name, current_label->address);
                break;
            }
            current_label = current_label->next;
        }
        current_extern = current_extern->next;
    }
    /*close ent_file if it was opened*/
    if (ext_file != NULL) 
    {
        fclose(ext_file);
    }
    free(filename);
}