#include "data_utilities.h"
#include "both_pass_common.h"
#include "tables.h"
#include "parser_utilities.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void process_data_data(char *line)
{
    char *token = strtok(line, " \t");
    int comma_flag = 0; /*flag for indecating the comma is expected in the beginning of next data*/
    int minus_flag = 0; /*flag for indecating that the number is negative*/
    int i, num;
    do
    {
        token = comma_parser(token, &comma_flag);
        /*checking for sign in the beginning*/
        if(token[0] == '+' || token[0] == '-')
        {
            if(token[0] == '-')
            {
                minus_flag = 1;
            }
            token++;
        }
        /*checking if the data is valid*/
        for(i = 0; i < strlen(token); i++)
        {
            if(isdigit(token[i]))
            {
                printf(ERROR_MESSAGE, "invalid data");
                error_flag = 1;
            }
        }
        /*converting the data to integer and adding it to the memory picture*/
        num = atoi(token);
        /*calculating the number if the data is negitive so it would be represented in the 2's complement method*/
        if(minus_flag)
        {
            num = 2^BITS_IN_WORD - num;
        }
        data_array[DC] = num;
        DC++;
    } while((token = strtok(NULL, " \t")) != NULL);
}

void process_string_data(char *line)
{
    char *token;
    int i;
    token = strtok(line, "\""); /*this token consists of white spaces*/
    token = strtok(NULL, "\""); /*this token consists of the string*/
    for(i = 0; i < strlen(token); i++)
    {
        data_array[DC] = token[i];
        DC++;
    }
    /*checking for extraneous text after the end of command*/
    while(token = strtok(NULL, " \t"))
    {
        for(i = 0; i < strlen(token); i++)
        {
            if(token[i] != '\t' && token[i] != ' ')
            {
                printf(ERROR_MESSAGE, "extraneous text after the end of word");
                error_flag = 1;    
                break;
            }
        }
    }
}

void process_entry_data(char *line)
{
    char *label = strtok(line, " \t"); /*this token consists of white spaces*/
    label = strtok(NULL, " \t"); /*this token consists of the label*/
    create_label_entry(&entry_table, label, 0);
}

void process_extern_data(char *line)
{
    char *label = strtok(line, " \t"); /*this token consists of white spaces*/
    label = strtok(NULL, " \t"); /*this token consists of the label*/
    create_label_entry(&extern_table, label, 0);
}
