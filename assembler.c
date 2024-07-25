#include <stdio.h>
#include "first_pass.h"

int main(int argc, char *argv[])
{
    int i;
    for(i=1; i<argc; i++)
    {
        FILE *file = interpret_macro(argv[i]);
        first_pass(file, argv[i]);
        second_pass(file);
    }
}