#include "second_pass.h"
#include "common.h"
#include "dynamic_tables.h"
#include "parser_utilities.h"
#include <stdio.h>

void second_pass(MachineCodeImage *machine_code_image, Tables *tables, FileInfo *file_info)
{
    add_values_to_label_table(tables, machine_code_image->IC);
    process_label_operands(file_info, tables, machine_code_image);
    print_entry_labels(file_info, tables);
    print_extern_labels(file_info, tables);
    print_machine_code(file_info, machine_code_image);
}