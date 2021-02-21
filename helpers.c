#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate average  value for rgb
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            // int/int always int

            // set average value to rgb
            image[i][j].rgbtBlue = avg;

            image[i][j].rgbtGreen = avg;

            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

void swap(RGBTRIPLE *f, RGBTRIPLE *l);
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swap last with first
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Set temp image
    RGBTRIPLE newimage[height][width];

    float c;

    float avgred;

    float avggreen;

    float avgblue;
    
    //Go through all pixels and copy to newimage
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newimage[i][j] = image[i][j];
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            c = 0.00;
            
            avgred = 0.00;
            
            avggreen = 0.00;
            
            avgblue = 0.00;
            
            for (int k = -1; k < 2; k++)
            {
                if (i + k < 0 || i + k > height - 1)
                {
                    continue;
                }
                for (int h = -1; h < 2; h++)
                {
                    if (j + h < 0 || j + h > width - 1)
                    {
                        continue;
                    }   
                    c++;
                    
                    avgred += newimage[i + k][j + h].rgbtRed;
            
                    avggreen += newimage[i + k][j + h].rgbtGreen;
            
                    avgblue += newimage[i + k][j + h].rgbtBlue;
                }
            }
            image[i][j].rgbtRed = round(avgred/c);
            
            image[i][j].rgbtGreen = round(avggreen/c);
            
            image[i][j].rgbtBlue = round(avgblue/c);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //initialize blueprint for image
    RGBTRIPLE edgeimage[height][width];

    //declaration of RGB values in Gx and Gy formats
    float GxRed, GxGreen, GxBlue, GyRed, GyGreen, GyBlue;
    
    // sobel matrix
    int Gx[3][3] = { {-1, 0, 1},
                     {-2, 0, 2},
                     {-1, 0, 1} };
                             
    int Gy[3][3] = { {-1, -2, -1},
                     {0 , 0 , 0 },
                     {1 , 2 , 1 } };
            
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Clearing all counts
            GxRed = 0.00;
            
            GxGreen = 0.00; 
            
            GxBlue = 0.00;
            
            GyRed = 0.00;
            
            GyGreen = 0.00;
            
            GyBlue = 0.00;
            
            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    // Skips if doesn't meet requirement
                    if ((i + h) < 0 || (i + h) == height || (j + k) < 0 || (j + k) == width)
                    {
                        continue;
                    }
                    // multiplication with Gx and Gy values
                    GxRed += image[i + h][j + k].rgbtRed * Gx[h + 1][k + 1];
                    
                    GxGreen += image[i + h][j + k].rgbtGreen * Gx[h + 1][k + 1];
                    
                    GxBlue += image[i + h][j + k].rgbtBlue * Gx[h + 1][k + 1];
                            
                    GyRed += image[i + h][j + k].rgbtRed * Gy[h + 1][k + 1];
                    
                    GyGreen += image[i + h][j + k].rgbtGreen * Gy[h + 1][k + 1];
                    
                    GyBlue += image[i + h][j + k].rgbtBlue * Gy[h + 1][k + 1];
                }
            }
            // Iplementation of Sobel's alghoritm
            edgeimage[i][j].rgbtRed = round(fmin(255, sqrt(pow(GxRed,2) + pow(GyRed,2))));
            
            edgeimage[i][j].rgbtGreen = round(fmin(255, sqrt(pow(GxGreen,2) + pow(GyGreen,2))));
            
            edgeimage[i][j].rgbtBlue = round(fmin(255, sqrt(pow(GxBlue,2) + pow(GyBlue,2))));

        }
    }
    //copy to original
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            image[i][j] = edgeimage[i][j];
    
    return;
}

// swap last and first elements
void swap(RGBTRIPLE *f, RGBTRIPLE *l)
{
    RGBTRIPLE t;
    
    t = *f;
    
    *f = *l;
    
    *l = t;
}