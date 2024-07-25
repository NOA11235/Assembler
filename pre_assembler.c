#include <stdio.h>

File *interpret_macro(File *file)
{
    File *macro_interpretation = fopen(macro_interpretation, "w");
    table *macro_table;
    table_entry *table_entry;
    char *line, *first_field;
    int macro_flag = 0;

    line = read_line(file);
    while(line != EOF)
    {
        first_field = get_next_word(line);

        if(*macro_name = is_in_table(macro_table, first_field(line)));
        {
            fprintf(macro_interpretation, "%s", table_entry.content);
            continue;
        }

        if(strcmp(first_field, "macr") == 0)
        {
            macro_flag = 1;
            insert_into_t(macro_table, get_next_word(line))
        }
    }
}