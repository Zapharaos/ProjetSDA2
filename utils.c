#include "utils.h"
#include <stddef.h>

void to_lower(char* entry)
{

    for (size_t i = 0; entry[i] != '\0'; i++)
    {
        if (entry[i] < 'A' || entry[i] > 'Z')
	        continue;
    	
        entry[i] = (char) (entry[i] - ('A' - 'a'));
    }
}
