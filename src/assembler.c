/*include here the macro header*/
#include "first_pass.h"
#include "second_pass.h"
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i;
    FILE *am_file, *as_file;
    MachineCodeImage machine_code_image;
    Tables tables;
    FileInfo file_info;

    for(i = 1; i < argc; i++)
    {
        char *filename = (char *)malloc(strlen(argv[i]) + 4); /*+4 for the ".as" \ ".am" and '\0'*/

        /*resetting the structers for the next file*/
        memset(&machine_code_image, 0, sizeof(MachineCodeImage));
        memset(&tables, 0, sizeof(Tables));
        memset(&file_info, 0, sizeof(FileInfo));

        strcpy(filename, argv[i]);
        strcat(filename, ".as");
        am_file = fopen(filename, "r");
        if(am_file == NULL)
        {
            printf("Error: %s file not found\n", filename);
            free(filename);
            continue;
        }

        file_info.file = as_file;
        file_info.file_name = filename;

        am_file = interpret_macro(&file_info, &tables);

        if(am_file == NULL) /*if there was an error detected in the pre_assembler function*/
        {
            continue;
        }
        memset(&file_info, 0, sizeof(FileInfo));
        first_pass(&machine_code_image, &tables, &file_info);
        second_pass(&machine_code_image, &tables, &file_info);

        fclose(as_file);
        fclose(am_file);
    }
    return 0;
}