
/**
 * initials.c
 *
 * Jonathan Sonnerup
 * Nooxet@gmail.com
 *
 * Prompts the user for their name
 * outputs the initials in upper case
 */

#include <stdio.h>
#include <ctype.h>

#include <cs50.h>

int main(int argc, char* argv[])
{
    string name = GetString();

    /* make room for all initials, plus ending NULL char */
    char initials[argc];

    int i = 0, j = 0;
    while (name[i] != '\0')
    {
        /**
         * add the first letter in upper case to the array
         * and increase the index to hold the next char
         */
        initials[j++] = (char) toupper(name[i]);

        while (name[i] != ' ' && name[i] != '\0')
        {
            /* skip the letters in the name */
            i++;
        }
        
        if (name[i] == ' ')
        {
            /* skip the space */
            i++;
        }
    }
    
    /* add the ending NULL char */
    initials[j] = '\0';

    printf("%s\n", initials);
    return 0;
}
    
