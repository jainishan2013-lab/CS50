#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every row from top to bottom
    for (int i = 0; i < height; i++)
    {
        // Loop through every pixel in that row from left to right
        for (int j = 0; j < width; j++)
        {
            // 1. Get the original color values
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // 2. Find the average and round it to the nearest integer
            int avg = round((red + green + blue) / 3.0);

            // 3. Set all three colors of the pixel to the same average
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every row from top to bottom
    for (int i = 0; i < height; i++)
    {
        // Loop through every pixel in that row from left to right
        for (int j = 0; j < width; j++)
        {
            // 1. Get the original color values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // 2. Compute the sepia values
            int sepiaRed =
                round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen =
                round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue =
                round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            // 3. Max of each value = to max values

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every row
    for (int i = 0; i < height; i++)
    {
        // Loop only up to the half-way point of the row
        for (int j = 0; j < width / 2; j++)
        {
            // 1. Save the left pixel into a temporary container
            RGBTRIPLE temp = image[i][j];

            // 2. Move the right (mirror) pixel into the left position
            image[i][j] = image[i][width - 1 - j];

            // 3. Move the temporary container data into the right position
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // 1. Create a temporary copy of the image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // 2. Loop through every row and column of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize variables to keep track of totals and pixel counts
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            float counter = 0.00;

            // 3. Loop through the 3x3 neighbor grid (-1, 0, 1 relative to i and j)
            for (int row_offset = -1; row_offset <= 1; row_offset++)
            {
                for (int col_offset = -1; col_offset <= 1; col_offset++)
                {
                    int neighbor_row = i + row_offset;
                    int neighbor_col = j + col_offset;

                    // 4. Boundary Check: Only add pixel if it is inside the image frame
                    if (neighbor_row >= 0 && neighbor_row < height && neighbor_col >= 0 &&
                        neighbor_col < width)
                    {
                        totalRed += copy[neighbor_row][neighbor_col].rgbtRed;
                        totalGreen += copy[neighbor_row][neighbor_col].rgbtGreen;
                        totalBlue += copy[neighbor_row][neighbor_col].rgbtBlue;
                        counter++;
                    }
                }
            }

            // 5. Calculate averages and round them to the nearest integer
            image[i][j].rgbtRed = round(totalRed / counter);
            image[i][j].rgbtGreen = round(totalGreen / counter);
            image[i][j].rgbtBlue = round(totalBlue / counter);
        }
    }
    return;
}
