#include <stdio.h>

#include <cs50.h>

void bubble_sort(int [], int);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <input list>\n", argv[0]);
        exit(1);
    }

    int *vec = malloc(argc - 1);
    for (int i = 1; i < argc; i++)
    {
        vec[i - 1] = atoi(argv[i]);
    }

    /* sort the array */
    bubble_sort(vec, argc - 1);

    /* print the sorted array */
    for (int i = 0; i < argc - 1; i++)
    {
        printf("%d, ", vec[i]);
    }
    printf("\n");

    return 0;
}

void bubble_sort(int vec[], int size)
{
    int n = size;
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < (n - i); j++)
        {
            if (vec[j] < vec[j - 1])
            {
                /* if at wrong place, swap the two */
                int tmp = vec[j];
                vec[j] = vec[j - 1];
                vec[j - 1] = tmp;
            }
        }
    }

}
