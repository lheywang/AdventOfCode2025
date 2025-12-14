/**
 *  @file day3/main.c
 *
 *  @brief challenge 3 main C file
 * 
 *  @author l.heywang <leonard.heywang@proton.me>
 *  @date   14/12/2025
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

// #define DEBUG

#define LINE_COUNT 137
#define COL_COUNT 137 // Why, but it works....

#define LINE_LEN (LINE_COUNT + 2)
#define COL_LEN (COL_COUNT + 2)

int main(int argc, char **argv)
{
    // open the source file
    FILE* file = fopen("input/input.txt", "r");

    // Initialize some data
    char buffer[COL_COUNT + 2] = {0};

    // Read the file and compute some elements
    int id = 1;
    if (file != NULL)
    {   
        while (fgets(buffer, sizeof(buffer), file))
        {
            printf("\nLine processed : \n%s", buffer);
        }
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    return EXIT_SUCCESS;
}