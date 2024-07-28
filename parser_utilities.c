#include "parser_utilities.h"
#include "first_pass_common.h"

char *comma_parser(char *token, int *comma_flag)
{
    /*if there wasn't a comma at the end of last operand then we'll check for it now*/
    if(comma_flag)
    {
        if(strcmp(token, ",") == 0)
        {
            token = strtok(NULL, " \t");
        }
        else if(token[0] != ',')
        {
            printf(ERROR_MESSAGE, "missing comma");
            error_flag = 1;
            token++;
        }
        comma_flag = 0;
    }

    /*getting rid of the comma at the end*/
    if(token[strlen(token-1)] == ',')
    {
        token[strlen(token-1)] = '\0';
    }
    else
    {
        comma_flag = 1;
    }
    return token;
}

char *read_line(FILE *file)
{
    static char line[MAX_LINE_LENGTH+2]; /*+2 for '\n' and '\0'*/
    if(fgets(line, MAX_LINE_LENGTH+1, file) == NULL)
    {
        return NULL;
    }
    if(line[strlen(line)-1] != '\n')
    {
        printf(ERROR_MESSAGE, "error: line is too long");
        error_flag = 1;
    }
    line[strlen(line)-1] = '\0';
    return line;
}

int is_label(char line[])
{
    char label[MAX_LABEL_LENGTH];
    sscanf(line, "%s", label);
    if(label[strlen(label)-1] == ':')
    {
        return 1;
    }
    return 0;
}


