#include "first_pass.h"
#include "first_pass_utils.h"
#include "first_pass_table_utils.h"
#include "parser_utils.h"
#include "defs.h"
#include <stdio.h>

void first_pass(MachineCodeImage *machine_code_image, Tables *tables, FileInfo *file_info)
{
    char line[MAX_LINE_LENGTH + 2]; /*buffer for the line. +2 for '\n' and '\0'*/
    char *line_ptr; /*pointer to the line buffer*/
    file_info->line_count = 0;
    while(read_line(line, file_info))
    {
        line_ptr = line;
        if(is_empty(line))
        {
            continue;
        }
        if(is_comment(line))
        {
            continue;
        }
        if(is_data(line))
        {
            if(search_for_label(line, file_info, tables))
            {
                line_ptr = process_label(line, file_info, tables, machine_code_image->DC);
            }
            process_data(line_ptr, file_info, tables, machine_code_image);
        }
        else if(is_instruction(line))
        {
            if(search_for_label(line, file_info, tables))
            {
                line_ptr = process_label(line, file_info, tables, machine_code_image->IC);
            }
            process_instruction(line_ptr, file_info, tables, machine_code_image);
        }
    }

    add_offset_to_data_labels(tables, machine_code_image->IC);
    validate_entry_labels(file_info, tables);
}