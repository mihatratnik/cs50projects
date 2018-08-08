#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // prompt user for amount of change
    float change_dollar;
    do
    {
        change_dollar = get_float("Change owed: ");
    }
    while (change_dollar <= 0);

    // covert dolars to cents
    int change_cent = round(change_dollar * 100);

    int count = 0;

    // check to use quarters
    int quarters = 25;
    while (change_cent >= 25)
    {
        change_cent -= quarters;
        count++;
    }

    // check to use dimes
    int dimes = 10;
    while (change_cent >= 10 && change_cent < 25)
    {
        change_cent -= dimes;
        count++;
    }

    // check to see nickles
    int nickles = 5;
    while (change_cent >= 5 && change_cent < 10)
    {
        change_cent -= nickles;
        count++;
    }

    // check to see pennies
    int pennies = 1;
    while (change_cent > 0 && change_cent < 5)
    {
        change_cent -= pennies;
        count++;
    }
    printf("%i\n", count);
}