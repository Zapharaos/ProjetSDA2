#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils/errors.h"
#include "utils/io.h"

int main(int argc, char* argv[])
{

    // if : too few arguments
	if (argc == 1)
    {
        print_error("Too few arguments: type ./bin/ald -help to display help");
        return 1;
    }

    // if : too much arguments
	if (argc > 3)
    {
        print_error("Too much arguments: type ./bin/ald -help to display help");
        return 1;
    }

    // if : checking the arguments
    if(handle_args(argc, argv) == 0)
    {
        // return : program success
        return 0;
    }

    // return : program failed
    print_error("Arguments not found: type ./bin/ald -help to display help");
    return 1;
}
