#include <stdio.h>
/*include here the macro header*/
#include "first_pass.h"
#include "second_pass.h"

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