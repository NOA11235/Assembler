#include "parser_utils.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *comma_parser(char *token, int *comma_flag, FileInfo *file_info)
{
    /*if there is a  comma at the beginning of the token*/
    if(token[0] == ',')
    {
        if(*comma_flag)
        {
            *comma_flag = 0;
        }
        else /*there is a comma at the beginning of the token and commas flag isn't set*/
        {
            printf(ERROR_MESSAGE, "consecutive commas");
            file_info->error_status = 1;
        }
        if(strcmp(token, ",") == 0) /*if the token is only a comma*/
        {
            token = strtok(NULL, " \t");
        }
        else
        {
            token++;
        }
    }

    if(*comma_flag) /*if there isn't a comma in the beginnig of the token and comma flag is set*/
    {
        printf(ERROR_MESSAGE, "error: missing comma");
        file_info->error_status = 1;
    }

    /*getting rid of the comma at the end*/
    if(token[strlen(token)-1] == ',')
    {
        if(token[strlen(token)-2] == ',') /*if there consecutive commas the end of the token*/
        {
            token[strlen(token)-2] = '\0';
            printf(ERROR_MESSAGE, "error: consecutive commas");
            file_info->error_status = 1;
        }

        token[strlen(token)-1] = '\0';
    }
    else /*if there isn't a comma at the end of the token*/
    {
        *comma_flag = 1;
    }
 
    return token;
}

char *walkthrough_white_spaces(char *line)
{
    while(*line == ' ' || *line == '\t')
    {
        line++;
    }
    return line;
}

int read_line(char *line, FileInfo *file_info)
{
    /*reading the next line from file*/
    if(!fgets(line, MAX_LINE_LENGTH+2, file_info->file))
    {
        return 0;
    }
    /*updating the line count*/
    file_info->line_count++;
    /*checking if the line is too long (more than 80 characters)*/
    if(line[strlen(line)-1] != '\n' && !feof(file_info->file))
    {
        printf(ERROR_MESSAGE, "error: line is too long");
        file_info->error_status = 1;
    }
    if(!feof(file_info->file))
    {
        line[strlen(line)-1] = '\0'; /*getting rid of '\n'*/
    }
    return 1;
}

int is_register(char *token)
{
    if(token[0] == 'r' && token[1] >= '0' && token[1] <= '7' && token[2] == '\0')
    {
        return 1;
    }
    return 0;
}