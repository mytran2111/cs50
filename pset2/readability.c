# include <stdio.h>
# include <cs50.h>
# include <string.h>
# include <ctype.h>
# include <math.h>


int main(void)
{

    string input = get_string("Text: ");
    long letters = 0;
    long words = 0;
    long sentences = 0;
    // Count lettes
    for (int i = 0, n = strlen(input); i < n ; i+= 1)
    {
        if ( isalpha(input[i]) != 0 )
        {
            letters += 1;
        }
    }
    //printf("Letters are : %li \n", letters);

    // Count words
    for ( int i = 0, n = strlen(input);i <n; i++)
    {
        if (input[i] == ' ')
        {
            continue;
        }
        else
        {
            words += 1;
            int j;
            for ( j = i; j < n && input[j] != ' '; j++ );
            // Tuong duong voi for khong nhan lenh gi
            i = j - 1;

        }
    }
    //printf("Words are : %li\n", words);

    // Count sentence
    for  (int i = 0 , n = strlen(input); i < n; i++)
    {
        if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            sentences += 1;
        }
    }
    //printf("Sentences are : %li\n", sentences);

    // Find index
    // L is average number of letters per 100 words:
    double L =  ( (double) letters/words) * 100;
    double S =  ( (double) sentences/words) * 100;
    double index = 0.0588 * L - 0.296*S -15.8;
    index = round(index);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16 )
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }

}
