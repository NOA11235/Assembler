#include <stdio.h>
#include "first_pass.h"
#include "first_pass_utilities.h"
#include "parser_utilities.h"

FILE *first_pass(FILE *file, char *file_name)
{
    char *line;
    file_info.line_count = 0;
    file_info.file_name = file_name;
    while((line = read_line(file)) != NULL)
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
                line = process_label(line, DC);
            }
            process_data(line);
        }
        if(is_instruction(line))
        {
            if(is_label(line))
            {
                line = process_label(line, IC);
            }
            process_instruction(line);
        }
        file_info.line_count++;
    }
}