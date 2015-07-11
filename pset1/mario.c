/**
 * mario.c
 *
 * Jonathan Sonnerup
 * Nooxet@gmail.com
 *
 * Prints the mario pyramid.
 */

#include <stdio.h>
#include <cs50.h>

void print_pyramid(int);

int main(void)
{
    int height;
    do 
    {
        printf("Enter size of pyramid (0-23): ");
        height = GetInt();
    } while (height > 23 || height < 0);
    print_pyramid(height);
}

/*
 *  prints a pyramid of a given height
 */
void print_pyramid(int height)
{
    for (int row = 0; row < height; row++) 
    {
        for (int col = 0; col <= height; col++) 
        {
            // check where we shall print the "#"
            if (col >= (height - row - 1)) 
            {
                printf("#");
            } 
            else 
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}
