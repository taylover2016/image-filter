#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int tmp;
    // Compute the average of 3 different channels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = tmp;
            image[i][j].rgbtGreen = tmp;
            image[i][j].rgbtRed = tmp;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Swap the corresponding values
    BYTE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = tmp;

            tmp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = tmp;

            tmp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = tmp;

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    // Note that there are 9 situations
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           if (((i == 0) && (j == 0)) || ((i == 0) && (j == width - 1)) ||
                ((i == height - 1) && (j == 0)) || ((i == height - 1) && (j == width - 1)))
           {
               // Pixels at corners
               if ((i == 0) && (j == 0))
               {
                   tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                   image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4.0);
                   tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                   image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4.0);
                   tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                   image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.0);
               }
               else if ((i == height - 1) && (j == 0))
               {
                   tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                   image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4.0);
                   tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                   image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4.0);
                   tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                   image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4.0);
               }
               else if ((i == 0) && (j == width - 1))
               {
                   tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                   image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4.0);
                   tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                   image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4.0);
                   tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                   image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4.0);
               }
               else
               {
                   tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                   image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4.0);
                   tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                   image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4.0);
                   tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                   image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0);
               }

           }
           else if ((i == 0) || (j == width - 1) ||
                (i == height - 1) || (j == 0))
           {
               // Pixels at edges
                if (i == 0)
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                    image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                    image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 6.0);

                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                    image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                    image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen) / 6.0);

                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                    image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed +
                    image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed) / 6.0);
                }
                else if (i == height - 1)
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                    image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                    image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 6.0);

                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                    image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                    image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen) / 6.0);

                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                    image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                    image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed) / 6.0);

                }
                else if (j == width - 1)
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                    image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                    image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6.0);

                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                    image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                    image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6.0);

                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                    image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                    image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6.0);
                }
                else
                {
                    tmp[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                    image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                    image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6.0);

                    tmp[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                    image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                    image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6.0);

                    tmp[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                    image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                    image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed) / 6.0);

                }
           }
           else
           {
               // Other pixels
                    tmp[i][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue +
                    image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                    image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                    image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                    image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 9.0);

                    tmp[i][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen +
                    image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                    image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                    image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                    image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 9.0);

                    tmp[i][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed +
                    image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                    image[i][j - 1].rgbtRed + image[i][j].rgbtRed +
                    image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                    image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed) / 9.0);
           }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    double Gx,Gy;
    // Note that there are 9 situations
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           if (((i == 0) && (j == 0)) || ((i == 0) && (j == width - 1)) ||
                ((i == height - 1) && (j == 0)) || ((i == height - 1) && (j == width - 1)))
           {
               // Pixels at corners
               if ((i == 0) && (j == 0))
               {
                   Gx = (2.0 * image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue);
                   Gy = (2.0 * image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue);
                   tmp[i][j].rgbtBlue = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (2.0 * image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
                   Gy = (2.0 * image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
                   tmp[i][j].rgbtGreen = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (2.0 * image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed);
                   Gy = (2.0 * image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed);
                   tmp[i][j].rgbtRed = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

               }
               else if ((i == height - 1) && (j == 0))
               {
                   Gx = (2.0 * image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue);
                   Gy = (-2.0 * image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue);
                   tmp[i][j].rgbtBlue = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (2.0 * image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen);
                   Gy = (-2.0 * image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen);
                   tmp[i][j].rgbtGreen = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (2.0 * image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed);
                   Gy = (-2.0 * image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed);
                   tmp[i][j].rgbtRed = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

               }
               else if ((i == 0) && (j == width - 1))
               {
                   Gx = (-2.0 * image[i][j - 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue);
                   Gy = (2.0 * image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue);
                   tmp[i][j].rgbtBlue = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (-2.0 * image[i][j - 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen);
                   Gy = (2.0 * image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen);
                   tmp[i][j].rgbtGreen = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (-2.0 * image[i][j - 1].rgbtRed - image[i + 1][j - 1].rgbtRed);
                   Gy = (2.0 * image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed);
                   tmp[i][j].rgbtRed = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

               }
               else
               {
                   Gx = (-2.0 * image[i][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue);
                   Gy = (-2.0 * image[i - 1][j].rgbtBlue - image[i - 1][j - 1].rgbtBlue);
                   tmp[i][j].rgbtBlue = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (-2.0 * image[i][j - 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen);
                   Gy = (-2.0 * image[i - 1][j].rgbtGreen - image[i - 1][j - 1].rgbtGreen);
                   tmp[i][j].rgbtGreen = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (-2.0 * image[i][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed);
                   Gy = (-2.0 * image[i - 1][j].rgbtRed - image[i - 1][j - 1].rgbtRed);
                   tmp[i][j].rgbtRed = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

               }

           }
           else if ((i == 0) || (j == width - 1) ||
                (i == height - 1) || (j == 0))
           {
               // Pixels at edges
                if (i == 0)
                {
                   Gx = (-2.0 * image[i][j - 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue +
                   2.0 * image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue);
                   Gy = (2.0 * image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                   image[i + 1][j + 1].rgbtBlue);
                   tmp[i][j].rgbtBlue = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (-2.0 * image[i][j - 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen +
                   2.0 * image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
                   Gy = (2.0 * image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                   image[i + 1][j + 1].rgbtGreen);
                   tmp[i][j].rgbtGreen = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (-2.0 * image[i][j - 1].rgbtRed - image[i + 1][j - 1].rgbtRed +
                   2.0 * image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed);
                   Gy = (2.0 * image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed +
                   image[i + 1][j + 1].rgbtRed);
                   tmp[i][j].rgbtRed = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
}
                else if (i == height - 1)
                {
                   Gx = (-2.0 * image[i][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue +
                   2.0 * image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue);
                   Gy = (-2.0 * image[i - 1][j].rgbtBlue - image[i - 1][j - 1].rgbtBlue -
                   image[i - 1][j + 1].rgbtBlue);
                   tmp[i][j].rgbtBlue = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (-2.0 * image[i][j - 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen +
                   2.0 * image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen);
                   Gy = (-2.0 * image[i - 1][j].rgbtGreen - image[i - 1][j - 1].rgbtGreen -
                   image[i - 1][j + 1].rgbtGreen);
                   tmp[i][j].rgbtGreen = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                   Gx = (-2.0 * image[i][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed +
                   2.0 * image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed);
                   Gy = (-2.0 * image[i - 1][j].rgbtRed - image[i - 1][j - 1].rgbtRed -
                   image[i - 1][j + 1].rgbtRed);
                   tmp[i][j].rgbtRed = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                }
                else if (j == width - 1)
                {
                    Gx = (-2.0 * image[i][j - 1].rgbtBlue - image[i - 1][j - 1].rgbtBlue -
                   image[i + 1][j - 1].rgbtBlue);
                   Gy = (-2.0 * image[i - 1][j].rgbtBlue - image[i - 1][j - 1].rgbtBlue +
                   image[i + 1][j - 1].rgbtBlue + 2.0 * image[i + 1][j].rgbtBlue);
                   tmp[i][j].rgbtBlue = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                    Gx = (-2.0 * image[i][j - 1].rgbtGreen - image[i - 1][j - 1].rgbtGreen -
                   image[i + 1][j - 1].rgbtGreen);
                   Gy = (-2.0 * image[i - 1][j].rgbtGreen - image[i - 1][j - 1].rgbtGreen +
                   image[i + 1][j - 1].rgbtGreen + 2.0 * image[i + 1][j].rgbtGreen);
                   tmp[i][j].rgbtGreen = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                    Gx = (-2.0 * image[i][j - 1].rgbtRed - image[i - 1][j - 1].rgbtRed -
                   image[i + 1][j - 1].rgbtRed);
                   Gy = (-2.0 * image[i - 1][j].rgbtRed - image[i - 1][j - 1].rgbtRed +
                   image[i + 1][j - 1].rgbtRed + 2.0 * image[i + 1][j].rgbtRed);
                   tmp[i][j].rgbtRed = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));
}
                else
                {
                    Gx = (2.0 * image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                   image[i + 1][j + 1].rgbtBlue);
                   Gy = (-2.0 * image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue +
                   image[i + 1][j + 1].rgbtBlue + 2.0 * image[i + 1][j].rgbtBlue);
                   tmp[i][j].rgbtBlue = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                    Gx = (2.0 * image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                   image[i + 1][j + 1].rgbtGreen);
                   Gy = (-2.0 * image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen +
                   image[i + 1][j + 1].rgbtGreen + 2.0 * image[i + 1][j].rgbtGreen);
                   tmp[i][j].rgbtGreen = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                    Gx = (2.0 * image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed +
                   image[i + 1][j + 1].rgbtRed);
                   Gy = (-2.0 * image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed +
                   image[i + 1][j + 1].rgbtRed + 2.0 * image[i + 1][j].rgbtRed);
                   tmp[i][j].rgbtRed = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                }
           }
           else
           {
               // Other pixels
                    Gx = (2.0 * image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                   image[i + 1][j + 1].rgbtBlue) - (2.0 * image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                   image[i + 1][j - 1].rgbtBlue);
                   Gy = (-2.0 * image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue -
                   image[i - 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                   2.0 * image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue);
                   tmp[i][j].rgbtBlue = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));


                    Gx = (2.0 * image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                   image[i + 1][j + 1].rgbtGreen) - (2.0 * image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                   image[i + 1][j - 1].rgbtGreen);
                   Gy = (-2.0 * image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen -
                   image[i - 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                   2.0 * image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen);
                   tmp[i][j].rgbtGreen = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

                    Gx = (2.0 * image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed +
                   image[i + 1][j + 1].rgbtRed) - (2.0 * image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed +
                   image[i + 1][j - 1].rgbtRed);
                   Gy = (-2.0 * image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed -
                   image[i - 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed +
                   2.0 * image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed);
                   tmp[i][j].rgbtRed = round(sqrt(pow(Gx, 2) + pow(Gy, 2))) > 255?
                   255: round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

           }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }

    return;
}
