/**
 * greedy.c
 *
 * Jonathan Sonnerup
 * Nooxet@gmail.com
 *
 * Calculates the least number of coins with which
 * a change can be made.
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define NUMCOINS 4

float get_positive(void);
int calc_min(int);

/* the available coin values we possess */
const int coins[] = { 25, 10, 5, 1 };

int main(void)
{
    float change = get_positive();
    /* 
     * convert to cents, as an integer, not forgetting
     * to round the floating point number to the 
     * correct decimal value
     * */
    int cents = (int) (roundf(change * 100));
    int chips = calc_min(cents);
    
    printf("%d\n", chips);
    return 0;
}

/*
 * gets a positive floatint point number
 */
float get_positive(void)
{
    float change;
    do
    {
        printf("Greet(d)ings mate! Enter your change: ");
        change = GetFloat();
    } while (change < 0);

    return change;
}

int calc_min(int cents)
{
    if (cents < 1)
    {
        return 0;
    }
    
    int coin = 0;
    for (int i = 0; i < NUMCOINS; i++)
    {
        /* 
         * find the largest coin which is less than
         * or equal to the remaining change
         */
        if (coins[i] <= cents)
        {
            coin = coins[i];
            break;
        }
    }

    /* 
     * recursive call to calculate the number of
     * coins for the rest of the change
     */
    return 1 + calc_min(cents - coin);

}

