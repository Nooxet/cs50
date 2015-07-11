
/**
 * vigenere.c
 *
 * Jonathan Sonnerup
 * Nooxet@gmail.com
 *
 * Encrypt a text string using Vigenere cipher
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <cs50.h>

char shift(char, char);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <key string>\n", argv[0]);
        return 1;
    }

    string key = argv[1];
    /* check that key only contains characters */
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Only characters are allowed in the key\n");
            return 1;
        }
    }

    /* get input from user */
    string text = GetString();
    
    for (int i = 0, j = 0, n = strlen(text), m = strlen(key); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            text[i] = shift(text[i], key[j]);
            /* only increment when used, wrap around if needed */
            j = (j + 1) % m;
        }
    }

    printf("%s\n", text);
    return 0;
}

char shift(char chr, char key)
{
    /* Both 'A' and 'a' in key counts as 0 */
    if (isupper(key))
    {
        key -= 'A';
    }
    else
    {
        key -= 'a';
    }

    if (isupper(chr))
    {
        return ((chr - 'A') + key) % 26 + 'A';
    }
    else
    {
        return ((chr - 'a') + key) % 26 + 'a';
    }

}
