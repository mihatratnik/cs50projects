#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long card_num;
    do
    {
        card_num = get_long_long("Please input your credit card number: ");
    }
    while (card_num < 0);

    // check for number of digits in the card number
    int card_digits = 0;
    long long card_num_dig = card_num;
    while (card_num_dig > 1)
    {
        card_digits++;
        card_num_dig /= 10;
    }

    // check if the card is Visa 13-digit
    if (card_digits == 13 && card_num >= 4000000000000 && card_num < 5000000000000)
    {

        // separate every other number, multiply and add to total
        long long second_to_last = card_num / 10;
        int total_sum = 0;
        for (long long i = second_to_last; i > 1;)
        {
            int j = (i % 10) * 2;

            // separate 2 digits and add them to total
            while (j >= 10)
            {
                for (int k = j; j >= 1;)
                {
                    int l = k % 10;
                    total_sum += l;
                    j = j / 10;
                    k = k / 10;
                }
            }
            total_sum += j;
            i = i / 100;
        }

        // add remaining numbers to total
        for (long long m = card_num; m >= 1;)
        {
            int n = m % 10;
            total_sum += n;
            m = m / 100;
        }

        // check validity
        if (total_sum % 10 == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    // check if the card is Visa 16-digit
    else if (card_digits == 16 && card_num >= 4000000000000000 && card_num < 5000000000000000)
    {

        // separate every other number, multiply and add to total
        long long second_to_last = card_num / 10;
        int total_sum = 0;
        for (long long i = second_to_last; i > 1;)
        {
            int j = (i % 10) * 2;

            // separate 2 digits and add them to total
            while (j >= 10)
            {
                for (int k = j; j >= 1;)
                {
                    int l = k % 10;
                    total_sum += l;
                    j = j / 10;
                    k = k / 10;
                }
            }
            total_sum += j;
            i = i / 100;
        }

        // add remaining numbers to total
        for (long long m = card_num; m >= 1;)
        {
            int n = m % 10;
            total_sum += n;
            m = m / 100;
        }

        // check validity
        if (total_sum % 10 == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    // check if the card is Mastercard
    else if (card_digits == 16 && card_num >= 5100000000000000 && card_num < 5600000000000000)
    {

        // separate every other number, multiply and add to total
        long long second_to_last = card_num / 10;
        int total_sum = 0;
        for (long long i = second_to_last; i > 1;)
        {
            int j = (i % 10) * 2;

            // separate 2 digits and add them to total
            while (j >= 10)
            {
                for (int k = j; j >= 1;)
                {
                    int l = k % 10;
                    total_sum += l;
                    j = j / 10;
                    k = k / 10;
                }
            }
            total_sum += j;
            i = i / 100;
        }

        // add remaining numbers to total
        for (long long m = card_num; m >= 1;)
        {
            int n = m % 10;
            total_sum += n;
            m = m / 100;
        }

        // check validity
        if (total_sum % 10 == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    // check if the card is American Express and starts with 34
    else if (card_digits == 15 && card_num >= 340000000000000 && card_num < 350000000000000)
    {

        // separate every other number, multiply and add to total
        long long second_to_last = card_num / 10;
        int total_sum = 0;
        for (long long i = second_to_last; i > 1;)
        {
            int j = (i % 10) * 2;

            // separate 2 digits and add them to total
            while (j >= 10)
            {
                for (int k = j; j >= 1;)
                {
                    int l = k % 10;
                    total_sum += l;
                    j = j / 10;
                    k = k / 10;
                }
            }
            total_sum += j;
            i = i / 100;
        }

        // add remaining numbers to total
        for (long long m = card_num; m >= 1;)
        {
            int n = m % 10;
            total_sum += n;
            m = m / 100;
        }

        // check validity
        if (total_sum % 10 == 0)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    // check if the card is American Express and starts with 37
    else if (card_digits == 15 && card_num >= 370000000000000 && card_num < 380000000000000)
    {

        // separate every other number, multiply and add to total
        long long second_to_last = card_num / 10;
        int total_sum = 0;
        for (long long i = second_to_last; i > 1;)
        {
            int j = (i % 10) * 2;

            // separate 2 digits and add them to total
            while (j >= 10)
            {
                for (int k = j; j >= 1;)
                {
                    int l = k % 10;
                    total_sum += l;
                    j = j / 10;
                    k = k / 10;
                }
            }
            total_sum += j;
            i = i / 100;
        }

        // add remaining numbers to total
        for (long long m = card_num; m >= 1;)
        {
            int n = m % 10;
            total_sum += n;
            m = m / 100;
        }

        // check validity
        if (total_sum % 10 == 0)
        {
            printf("AMEX\n");
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
    return 0;
}