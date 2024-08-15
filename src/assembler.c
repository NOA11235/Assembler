#include "pre_assembler.h"
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
        char *input_filename = (char *)malloc(strlen(argv[i]) + 4); /*+4 for the ".as" \ ".am" and '\0'*/
        if(input_filename == NULL)
        {
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        /*resetting the structers for the next file*/
        memset(&machine_code_image, 0, sizeof(MachineCodeImage));
        memset(&tables, 0, sizeof(Tables));
        memset(&file_info, 0, sizeof(FileInfo));

        /*getting the name of the .as file*/
        sprintf(input_filename, "%s.as", argv[i]);

        as_file = fopen(input_filename, "r");
        if(as_file == NULL)
        {
            printf("Error: %s file not found\n", input_filename);
            free(input_filename);
            continue;
        }

        /*setting the input file to the .as file*/
        file_info.base_filename = argv[i];
        file_info.input_file = as_file;

        am_file = interpret_macro(&file_info, &tables);
        if(am_file == NULL) /*if there was an error detected in the pre_assembler function*/
        {
            fclose(as_file);
            free(input_filename);
            continue;
        }

        /*resetting the input file to the .am file*/
        file_info.input_file = am_file;

        /*reset the file pointer to the beginning of the .am file */
        if(fseek(file_info.input_file, 0, SEEK_SET) != 0)
        {
            printf("Error: fseek failed\n");
            fclose(as_file);
            fclose(am_file);
            free(input_filename);
            exit(EXIT_FAILURE);
        }
        

        first_pass(&machine_code_image, &tables, &file_info);
        second_pass(&machine_code_image, &tables, &file_info);

        fclose(as_file);
        fclose(am_file);
        free(input_filename);
    }
    return 0;
}