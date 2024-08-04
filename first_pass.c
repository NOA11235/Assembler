#include "first_pass.h"
#include "first_pass_utils.h"
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
        if(is_label(line))
        {
            process_label(&line_ptr, file_info, tables, machine_code_image->IC);
        }
        if(is_data(line))
        {
            process_data(line_ptr, file_info, tables, machine_code_image);
        }
        else if(is_instruction(line))
        {
            process_instruction(line_ptr, file_info, tables, machine_code_image);
        }
    }
}