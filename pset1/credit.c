#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");
    // Sum of those in position require multiplication of two
    int sum_mult = 0;
    // Sum of those in position does not require multiplication of 2
    int sum_not = 0;
    // count length of credit card number
    int count = 0;
    long original = number;
    while(number > 0 )
    {
        count += 1;
        if (count % 2 != 0)
        {
            sum_not += (number % 10);
            number = (number - (number % 10)) / 10;

        }
        else
        {
            int add = (number % 10) * 2;
            if (add >9)
            {
                sum_mult += (add % 10 );
                add = (add-(add % 10)) / 10;
                sum_mult += add;
            }
            else
            {
                sum_mult += add;
            }

            number = (number - (number % 10)) / 10;
        }
    }

    int sum = sum_mult + sum_not;
    //printf("Sum is %i.\n", sum);
    //printf("a is %i.\n", sum_mult);
    //printf("Length is %i.\n", count);
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        long divisor_1 = 1;
        long divisor_2 = 1;
        for (int x = 1; x < count; x+= 1)
        {
            divisor_1 *= 10;
        }
        for (int y = 1; y < count-1; y+= 1)
        {
            divisor_2 *= 10;
        }
        // This is to check the divisor
        //printf("First divisor:%li\n", divisor_1);
        //printf("Second divisor:%li\n", divisor_2);
        int first_digit = original / divisor_1;
        int two_digit = original / divisor_2;
        // This is to check the digits printed
        //printf("First digit is %i\n", first_digit);
        //printf("First two digits is %i\n", two_digit);
        if (count == 15 && (two_digit == 34 || two_digit == 37))
        {
            printf("AMEX\n");
        }
        else if (count == 16 && (two_digit > 50 && two_digit < 56))
        {
            printf("MASTERCARD\n");
        }
        else if ((count == 13 || count == 16) && first_digit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

}
