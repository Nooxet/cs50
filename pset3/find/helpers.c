/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

bool binary_search(int value, int values[], int min, int max)
{
    if (max < min)
    {
        return 0;
    }

    int mid = (min + max) / 2;
    if (value > values[mid])
    {
        return binary_search(value, values, mid + 1, max);
    } 
    else if (value < values[mid])
    {
        return binary_search(value, values, min, mid - 1);
    }
    else
    {
        return 1;
    }
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // sort the array
    sort(values, n);

    return binary_search(value, values, 0, n - 1);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Sorting using selection sort
    int minpos;
    for (int i = 0; i < n; i++)
    {
        minpos = i;
        for (int j = i; j < n; j++)
        {
            if (values[j] < values[minpos])
            {
                minpos = j;
            }
        }
        int tmp = values[i];
        values[i] = values[minpos];
        values[minpos] = tmp;
    }
}
