#include "second_pass.h"
#include "second_pass_utils.h"
#include "second_pass_table_utils.h"
#include "defs.h"
#include "parser_utils.h"
#include <stdio.h>

void second_pass(MachineCodeImage *machine_code_image, Tables *tables, FileInfo *file_info)
{
    process_label_operands(file_info, tables, machine_code_image);
    /*the .ent .ext and .ob will be printed only if there wasn't any error detect*/
    if (file_info->error_status)
    {
        free_tables(tables);
        return;
    }
    print_entry_labels(file_info, tables);
    print_extern_labels(file_info, tables);
    print_machine_code(file_info, machine_code_image);
    free_tables(tables);
}