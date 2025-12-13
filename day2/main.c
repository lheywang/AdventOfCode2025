/**
 *  @file day2/main.c
 *
 *  @brief challenge 2 main C file
 * 
 *  @author l.heywang <leonard.heywang@proton.me>
 *  @date   09/12/2025
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#define NB_COUNT 64

int count_digits(unsigned long long n) {
    int digits = 0;
    if (n == 0) return 1;  // Special case for 0
    while (n > 0) {
        n /= 10;
        digits++;
    }
    return digits;
}

int main(int argc, char **argv)
{
    // open the source file
    FILE* file = fopen("input/input.txt", "r");

    // Initialize some data
    char buffer[1024] = {0};
   
    uint64_t values[2][NB_COUNT] = { 0 };

    // Read the file and compute some elements
    int id = 0;
    if (file != NULL)
    {   
        while (fgets(buffer, sizeof(buffer), file))
        {
            char *pair_str = strtok(buffer, ",");  // Split by comma

            while (pair_str != NULL) {
                uint64_t start, end;
                if (sscanf(pair_str, "%llu-%llu", &start, &end) == 2) {
                    values[0][id] = start;
                    values[1][id] = end;
                    id += 1;
                }
                pair_str = strtok(NULL, ",");
            }
        }
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    // Preparing the output
    uint64_t pass = 0;

    // Print the values
    for (int k = 0; k < NB_COUNT; k++)
    {
        printf("=================================================\n");
        printf("START : %16llu - END : %16llu\n", values[0][k], values[1][k]);
        printf("=================================================\n");

        // First, get the length of the numbers
        uint64_t first = count_digits(values[0][k]);
        uint64_t stop = count_digits(values[1][k]);

        // First condition : If lenghts aren't even, there CAN'T be two identical parts...s
        if ((first & 0x1) && (stop & 0x1))
        {
            printf("    Impossible combo. There can't two identical parts in number that aren't even \n");
            continue;
        }

        // Then, get the shortest element len and divide by two (to get the cell size)
        uint64_t cell_size = ((stop > first) ? stop : first) / 2;

        // Get the power of ten factor that correspond to this number
        uint64_t factor = 1;
        for (uint64_t i = 0; i < cell_size; i++)
            factor *= 10;

        printf("    Found a cell size of %d digits\n", cell_size);
        printf("    Nearest 10 power is : %d\n", factor);

        // Getting the limits of the range we're going to compute on : 
        uint64_t first_cell = (values[0][k] / factor);
        uint64_t stop_cell  = (values[1][k] / factor) + 1;

        // Ensure results are stricly positive
        first_cell = (first_cell > 0) ? first_cell - 1: first_cell;

        printf("    Start ID : %d; End ID : %d\n", first_cell, stop_cell);

        // Then, iterate within this range :
        for (uint64_t val = first_cell; val <= stop_cell; val ++)
        {
            /*
             * CASE 0 : Two ID per ranges
             */
            // Compute the value that is formed by this couple : 
            uint64_t tmp = (val * factor) + val;

            // Then, check if this value is within the values : 
            if ((values[0][k] <= tmp) && (tmp <= values[1][k]))
            {
                if ((count_digits(tmp) % 2) == 0)
                {
                    printf("    Found value : %llu\n", tmp);
                    pass += tmp;
                }
            }
        }
    }

    // final print
    printf("Output value : %llu\n\n", pass);

    return EXIT_SUCCESS;
}