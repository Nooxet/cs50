/**
 * credit.c
 *
 * Jonathan Sonnerup
 * Nooxet@gmail.com
 *
 * A program for checking credit cards, using Luhn's algorithm - hacker version.
 */

#define VALID       1
#define INVALID     0

#include <stdio.h>

#include <cs50.h>

int luhn(long long);
string get_manu(long long);

int main(void)
{
    printf("Enter credit card number: ");
    long long card = GetLongLong();

    string merchant = get_manu(card);
    if (merchant != NULL)
    {
        if (luhn(card) == VALID)
        {
            printf("%s\n", merchant);
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

/**
 * Using Luhn's algorithm to detect transpositions
 * in a credit card number
 */
int luhn(long long card_num)
{
    int sum = 0;
    int interm;
    while (card_num != 0)
    {
        sum += card_num % 10;
        card_num /= 10;

        /* multiply each other number by 2 */
        interm = card_num % 10;
        interm *= 2;

        /* sum up the digits in interm, in case it is > 9 */
        sum += (interm % 10) + (interm / 10);

        card_num /= 10;
    }

    return sum % 10 == 0 ? VALID : INVALID;
}

/**
 * Find out which manufacturer the card belongs to
 * by checking the first two digits
 */
string get_manu(long long card_num)
{
    while (card_num >= 100)
    {
        card_num /= 10;
    }

    if (card_num == 34 || card_num == 37)
    {
        return "AMEX";
    }
    else if (card_num >= 40 && card_num < 50)
    {
        return "VISA";
    }
    else if (card_num >= 51 && card_num <= 55)
    {
        return "MASTERCARD";
    }
    else
    {
        return NULL;
    }
}
