# include <cs50.h>
# include <stdio.h>
int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8 );

    for ( int i = 1; i < height+1; i += 1)
    {
        for (int j = 0; j < height-i; j+= 1 )
        {
            printf(" ");
        }
        for (int k = 0; k < i; k+= 1)
        {
            printf("#");
        }
        printf(" ");
        printf(" ");
        for (int l = 0; l < i; l+= 1)
        {
            printf("#");
        }
        printf("\n");
    }

}
