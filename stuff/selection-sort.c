#include <stdio.h>

#include <cs50.h>

void selection_sort(int [], int);

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
    selection_sort(vec, argc - 1);

    for (int i = 0; i < argc - 1; i++)
    {
        printf("%d, ", vec[i]);
    }
    printf("\n");
    return 0;

}

/* the selection sort algorithm */
void selection_sort(int vec[], int size)
{
    int minpos;
    for (int i = 0; i < size; i++)
    {
        minpos = i;
        for (int j = i; j < size; j++)
        {
            if (vec[j] < vec[minpos])
            {
                /* found a lower value than current min, update */
                minpos = j;
            }
        }
        /* swap the i:th value to the current min */
        int tmp = vec[i];
        vec[i] = vec[minpos];
        vec[minpos] = tmp;
    }
}
