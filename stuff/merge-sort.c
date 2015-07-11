#include <stdio.h>

#include <cs50.h>

int* merge_sort(int [], int, int);

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
        vec[i-1] = atoi(argv[i]);
    }

    /* sort the array */
    merge_sort(vec, 0, argc-1);

    /* print it */
    for (int i = 0; i < argc-1; i++)
    {
        printf("%d, ", vec[i]);
    }
    printf("\n");

    return 0;
}

int* merge_sort(int vec[], int min, int max)
{
    int size = max - min + 1;
    if (size < 2)
    {
        return vec;
    }

    /* the recursive call */
    int mid = size / 2;
    int* left = merge_sort(vec, 0, mid - 1);
    int* right = merge_sort(vec, mid, size - 1);

    /* merging left and right */


}
