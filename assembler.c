/*include here the macro header*/
#include "first_pass.h"
#include "second_pass.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    FILE *am_file;
    /*structers for first and second pass*/
    MachineCodeImage machine_code_image;
    Tables tables;
    FileInfo file_info;

    for(i = 1; i < argc; i++)
    {
        am_file = interpret_macro(argv[i]);

        /*inserting file information into file_info*/
        file_info.file = am_file;
        file_info.file_name = argv[i];

        first_pass(&machine_code_image, &tables, &file_info);
        second_pass(&machine_code_image, &tables, &file_info);
        fclose(am_file); /*closing the file*/

        /*resetting the structers for the next file*/
        memset(&machine_code_image, 0, sizeof(MachineCodeImage));
        memset(&tables, 0, sizeof(Tables));
        memset(&file_info, 0, sizeof(FileInfo));
    }
    return 0;
}