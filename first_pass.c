#include "first_pass.h"
#include "first_pass_utilities.h"
#include "parser_utilities.h"
#include "common.h"
#include <stdio.h>

void *first_pass(MachineCodeImage *machine_code_image, Tables *tables, FileInfo *file_info)
{
    char line[MAX_LINE_LENGTH + 2]; /*+2 for '\n' and '\0'*/
    file_info->line_count = 0;
    while(read_line(line, file_info))
    {
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
            if(is_label(line))
            {
                process_label(&line, file_info, tables, machine_code_image->DC);
            }
            process_data(line, file_info, tables, tables, machine_code_image);
        }
        if(is_instruction(line))
        {
            if(is_label(line))
            {
                process_label(&line, file_info, tables, machine_code_image->DC);
            }
            process_instruction(line, file_info, tables, machine_code_image);
        }
        file_info->line_count++;
    }
}