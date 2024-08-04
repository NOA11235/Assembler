#include "defenitions.h"
#include <stdio.h>
#include <stdlib.h>

void print_machine_code(FileInfo *file_info, MachineCodeImage *machine_code_image)
{
    int i;
    char *filename = strcat(file_info->file_name, ".object");
    FILE *object_file = fopen(filename, "w");

    /*check if file was opened successfully*/
    if (object_file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    /*object_file header*/
    fprintf(object_file, "   %d %d\n", machine_code_image->IC, machine_code_image->DC);
    for(i = 0; i < machine_code_image->IC; i++)
    {
        fprintf(object_file, "%04d %05o\n", i + FIRST_ADDRESS, machine_code_image->instruction_array[i]);
    }
    for(i = 0; i < machine_code_image->DC; i++)
    {
        fprintf(object_file, "%04d %05o\n", i + machine_code_image->IC + FIRST_ADDRESS, machine_code_image->data_array[i]);
    }
    fclose(object_file);
}
