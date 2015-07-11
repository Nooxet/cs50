/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

/**
 * Recursive function for binary search, returns true if value is found
 */
bool binary_search(int value, int values[], int a, int b);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);
