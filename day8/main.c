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
#include <ctype.h>

// #define DEBUG

#define ID_CNT 1000
#define RANGE_CNT 179

int main(int argc, char **argv)
{
    // open the source file
    FILE* file = fopen("input/input.txt", "r");

    // Initialize some data
    char buffer[64] = {0};

    // Read the file and compute some elements
    bool mode = false;

    int value_id = 0;
    int range_id = 0;

    if (file != NULL)
    {   
        while (fgets(buffer, sizeof(buffer), file))
        {

        }
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    return EXIT_SUCCESS;
}