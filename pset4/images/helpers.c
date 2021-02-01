#include "helpers.h"
# include <stdio.h>
# include <cs50.h>
# include <math.h>

#define MIN(x, y) (x < y) ? x : y
#define MAX(x, y) (x > y) ? x : y

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double mean_color = 0.0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mean_color = (double) (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            mean_color = (int) round(mean_color);
            image[i][j].rgbtRed = mean_color;
            image[i][j].rgbtGreen = mean_color;
            image[i][j].rgbtBlue = mean_color;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width/2) ; j++)
        {
            int y = width -1 -j;
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][y];
            image[i][y] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double red = 0;
            double green = 0;
            double blue = 0;
            int valid = 0;
            for (int n = -1; n <= 1; n++)
            {
                for (int m = -1; m <= 1; m ++)
                {
                    int new_row = i + n;
                    int new_column = j + m;
                    if (new_row < 0 || new_row >= height) continue;
                    if (new_column < 0 || new_column >= width) continue;
                    valid++;
                    red += (double) image[new_row][new_column].rgbtRed;
                    green += (double) image[new_row][new_column].rgbtGreen;
                    blue +=  (double) image[new_row][new_column].rgbtBlue;

                }
            }
            red = (int) round(red / (double) valid);
            green = (int) round(green / (double) valid);
            blue = (int) round(blue / (double) valid);
            new_image[i][j].rgbtRed = red;
            new_image[i][j].rgbtGreen = green;
            new_image[i][j].rgbtBlue = blue;
        }
    }

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            image[i][j] = new_image[i][j];

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};

    // This is to store and copy value later
    RGBTRIPLE new_image[height][width];

    for (int i = 0; i < height; i++ )
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_red = 0;
            int Gx_green = 0;
            int Gx_blue = 0;

            int Gy_red = 0;
            int Gy_green = 0;
            int Gy_blue = 0;

            double red = 0;
            double green = 0;
            double blue = 0;

            for (int n = -1; n <= 1; n++)
            {
                for (int m = -1; m <= 1; m ++)
                {
                    int new_row = i + n;
                    int new_column = j + m;
                    if (new_row < 0 || new_row >= height) continue;
                    if (new_column < 0 || new_column >= width) continue;
                    Gx_red += image[new_row][new_column].rgbtRed * Gx[1+n][1+m];
                    Gx_green += image[new_row][new_column].rgbtGreen * Gx[1+n][1+m];
                    Gx_blue += image[new_row][new_column].rgbtBlue * Gx[1+n][1+m];

                    Gy_red += image[new_row][new_column].rgbtRed * Gy[1+n][1+m];
                    Gy_green += image[new_row][new_column].rgbtGreen * Gy[1+n][1+m];
                    Gy_blue += image[new_row][new_column].rgbtBlue * Gy[1+n][1+m];



                }
            }

            red = sqrt( (double) (Gx_red * Gx_red) + (Gy_red * Gy_red) );
            green = sqrt( (double) (Gx_green * Gx_green) + (Gy_green * Gy_green) );
            blue = sqrt( (double) (Gx_blue * Gx_blue) + (Gy_blue * Gy_blue) );

            red = (int) round(red);
            green = (int) round(green);
            blue = (int) round(blue);

            new_image[i][j].rgbtRed = MIN(red, 255);
            new_image[i][j].rgbtGreen = MIN(green, 255);
            new_image[i][j].rgbtBlue = MIN(blue, 255);

        }
    }

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            image[i][j] = new_image[i][j];

    return;
}
