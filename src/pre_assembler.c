#include "defs.h"
#include "parser_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *interpret_macro(FileInfo *file_info, Tables *tables)
{
    char line[MAX_LINE_LENGTH + 2]; /*+2 for '\n' and '\0'*/
    char first_word[MAX_MACRO_NAME_LENGTH + 2]; /*+2 for an extra character and '\0'*/
    char *token;
    int macro_definition_flag = 0;

    while(read_line(line, file_info))
    {   
        sscanf(line, "%s", first_word); /*get the first word in the line*/

        if (strcmp(first_word, "macr") == 0) 
        {
            macro_definition_flag = 1;
            process_macro_definition(line, file_info, tables);
        }
        else if (strcmp(first_word, "endmacr") == 0) 
        {
            macro_definition_flag = 0;
            process_end_of_macro_definition(line, file_info, tables);
        }
        if(!file_info->error_status) /*if there wasn't any error detected yet*/
        {
            if(macro_definition_flag)
            {
                /*add the content of the macro to the macro table*/
                add_content_to_macro(line, file_info, tables);
            }
            else if(!find_macro_and_print(first_word, file_info, tables)) /*if the line isn't a macro*/
            {
                /*print the line to the .am file*/
                fprintf(file_info->file, "%s\n", line);
            }
        }
    }

    if(file_info->error_status)
    {
        remove(file_info->file_name);
        return NULL;
    }
    return file_info->file;
}

/* A method that checks whether the macro name is valid */
int isValidMacroName(char name[MAX_LINE_LENGTH]) 
{
    return 1; /* To fix!!!!!!!!!!!! */
}

/* A method that gets macro details and creates a new macro node with these details */
macro_node* insert_macro_values(char name[MAX_LINE_LENGTH], int start, int end)
{
    macro_node *newMacro;
    
    newMacro = (macro_node*)malloc(sizeof(macro_node));
    if (newMacro == NULL)
    {
        perror("ALLOCATION ERROR");
        return NULL;
    }
    
    strncpy(newMacro->macro_data.macro_name, name, MAX_LINE_LENGTH);
    newMacro->macro_data.macro_start = start;
    newMacro->macro_data.macro_end = end;
    newMacro->next = NULL;
    return newMacro;
}

/* A method that goes over file, finds new macro definitions and saves them in a list. */   
int find_macros(const char *filename, macro_list *macros)
{
    char line[MAX_LINE_LENGTH]; /* The current line we are reading in the file */ 
    char name[MAX_LINE_LENGTH]; /* The macro name */
    int start, end;
    int inMacro; /* boolean flag which says if we are in macro now */
    int index;
    macro_node *tmp;
    FILE* file;

    inMacro = 0; /* Initialize flag */
    index = 0; /* Initialize index */
    
    file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("ERROR IN OPENING FILE");
        return EXIT_FAILURE;
    }
    
    while (fgets(line, sizeof(line), file))
    {
        if (!inMacro)
        {
            if (strncmp(line, "macr ", 5) == 0)
            {
                strcpy(name, line + 5);
                if (!isValidMacroName(name))
                {
                    perror("NOT VALID MACRO NAME");
                    fclose(file);
                    return EXIT_FAILURE;
                }
                start = index;
                inMacro = 1;
            }
        }
        else /* If we are in macro, it's the end of the macro, we want to check if the end is valid */
        {
            if (strncmp(line, "endmacr ", 7) == 0)
            {
                if (strncmp(line + 7, "\t", 1) == 0 && strlen(line) > 8) /* If there are more words in the line, the end is not valid */
                {
                    perror("NOT VALID MACRO END");
                    fclose(file);
                    return 0;
                }
                else if (strncmp(line + 7, "\n", 1) == 0)
                {
                    end = index - 1; /* The macro ends in the previous line */
                    tmp = insert_macro_values(name, start, end); /* Create new macro */
                    if (tmp == NULL)
                    {
                        fclose(file);
                        return -1;
                    }
                    else /* Add the new macro to the list */
                    {
                        if (macros->size == 0)
                        {
                            tmp->next = macros->head;
                            macros->head = tmp;
                            macros->size = 1;
                        }
                        else
                        {
                            macro_node *current = macros->head;
                            while (current->next != NULL)
                            {
                                current = current->next;
                            }
                            current->next = tmp;
                            (macros->size)++;
                        }
                    }
                    inMacro = 0; /* Now we are out of the macro */
                }
            }
        }
        index++;
    }
    
    fclose(file);
    return EXIT_SUCCESS;
}

int numOfLines(const char *filename)/*A method that counts how many lines there are in file*/
{
    FILE *file;
    int lines;
    char ch;

    lines = 0;
    
    file = fopen(filename, "r"); 
    if (file == NULL) 
    {
        perror("ERROR IN OPENING FILE");
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(file)) != EOF) 
    {
        if (ch == '\n') 
        {
            lines++;
        }
    }

    fclose(file); 
    return lines;
}

int copy_file(const char *filename, char **table, int num_of_lines)/*A method that copies file to a table*/ 
{
    FILE *file;
    int current_line;

    current_line = 0;

    file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("ERROR IN OPENING FILE: %s\n", filename);
        return EXIT_FAILURE;
    }

    while (current_line < num_of_lines && !feof(file)) 
    {
        table[current_line] = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
        if (table[current_line] == NULL) 
        {
            printf("MEMORY ALLOCATION FAILED\n");
            fclose(file);
            return EXIT_FAILURE;
        }

        if (fgets(table[current_line], MAX_LINE_LENGTH, file) != NULL) 
        {
            current_line++;
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int write_macros(const char *filename, const char *fileamname, macro_list *macros)
{
    int i, j;
    int num_of_lines;
    int foundMacro;
    char **table;
    FILE *fileam;
    macro_node *tmp;

    num_of_lines = numOfLines(filename);
    if (num_of_lines < 0) 
    {
        return EXIT_FAILURE; /* Handle error from numOfLines */
    }

    table = (char **)malloc(num_of_lines * sizeof(char *));
    if (table == NULL) 
    {
        printf("MEMORY ALLOCATION FAILED\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < num_of_lines; i++) 
    {
        table[i] = NULL;
    }

    if (copy_file(filename, table, num_of_lines) != EXIT_SUCCESS)
    {
        for (i = 0; i < num_of_lines; i++) 
        {
            free(table[i]);
        }
        free(table);
        return EXIT_FAILURE;
    }

    fileam = fopen(fileamname, "w+"); 
    if (fileam == NULL) 
    {
        perror("ERROR IN OPENING FILE");
        for (i = 0; i < num_of_lines; i++) 
        {
            free(table[i]);
        }
        free(table);
        return EXIT_FAILURE;
    }

    foundMacro = 0;
    for (i = 0; i < num_of_lines; i++) 
    {
        tmp = macros->head;
        while (tmp != NULL && !foundMacro) 
        {
            if (strncmp(table[i], tmp->macro_data.macro_name, strlen(tmp->macro_data.macro_name)) == 0) 
            {
                for (j = tmp->macro_data.macro_start; j <= tmp->macro_data.macro_end; j++) 
                {
                    fputs(table[j], fileam);
                }
                foundMacro = 1;
            }
            else 
            {
                tmp = tmp->next; 
            }
        }

        if (foundMacro) 
        {
            foundMacro = 0;
        }
        else 
        {
            fputs(table[i], fileam); /* Copy the current line */
        }        
    }

    fclose(fileam);
    for (i = 0; i < num_of_lines; i++) 
    {
        free(table[i]);
    }
    free(table);
    return EXIT_SUCCESS;
}



int macro_pass(const char *filename, const char *newfilename)
{
    int findMacros;
    int writeMacros;
    macro_list *macros;

    macros = (macro_list*)malloc(sizeof(macro_list));
    if (macros == NULL)
    {
        perror("ALLOCATION ERROR");
        return EXIT_FAILURE;
    }
    macros->head = NULL; /* Initialize the head pointer */
    macros->size = 0; /* Initialize the size */
    findMacros = find_macros(filename, macros);
    if (!findMacros)
    {
        free(macros);
        return EXIT_FAILURE;
    }
    writeMacros = write_macros(filename, newfilename, macros);
    if (!writeMacros)
    {
        free(macros);
        return EXIT_FAILURE;
    }
    free(macros);
    return EXIT_SUCCESS;
}
