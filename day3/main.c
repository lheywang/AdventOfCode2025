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

#define LINE_COUNT 200
#define COL_COUNT 100

// Data storages (use too much stack otherwise)
static int numbers[LINE_COUNT][COL_COUNT] = { 0 };
static int max[LINE_COUNT] = { 0 };
static uint64_t max2[LINE_COUNT] = { 0 };

int main(int argc, char **argv)
{
    // open the source file
    FILE* file = fopen("input/input.txt", "r");

    // Initialize some data
    char buffer[128] = {0};

    // Read the file and compute some elements
    int id = 0;
    if (file != NULL)
    {   
        while (fgets(buffer, sizeof(buffer), file))
        {
            for (int i = 0; i < COL_COUNT; i++)
            {
                numbers[id][i] = buffer[i] - '0';
            }
            id += 1;
            printf("Line processed : %s", buffer);
        }
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    // Iterating over the array to find the greatest pairs (stage 1)
    for (int i = 0; i < LINE_COUNT; i++)
    {
        int best = 0;
        for (int u = 0; u < COL_COUNT; u++)
        {
            for (int uu = 0; uu < COL_COUNT; uu++)
            {
                if (uu <= u) // Ensure the numbers are treated in order, can't reorganize them
                    continue;

                int val = (numbers[i][u] * 10) + numbers[i][uu];
                best = (val > best) ? val : best;
            }
        }
        max[i] = best;
    }

    // Iterating over the array to find the greatest groups (12 digits) (stage 2)
    for (int i = 0; i < LINE_COUNT; i++)
    {
        int stack[100] = { 0 };
        int top = 0;
        int removals = COL_COUNT - 12; // 100 - 12;
        
        for (int k = 0; k < COL_COUNT; k++)
        {
            int d = numbers[i][k];

            // Removing numbers on the stack only if we can (enough numbers remaining)
            while ( top > 0 &&
                    stack[top - 1] < d &&
                    removals > 0) 
            {
                top--;
                removals--;
            } 

            // Write on the stack
            stack[top] = d;
            top += 1;
        }

        // Compute the value for the largest 12 digits
        uint64_t val = 0;
        for (int k = 0; k < 11; k++)
        {
            val += stack[k];
            val *= 10;
        }
        val += stack[11];

        max2[i] = val;
    }

    // Finally, make the sum
    int sum = 0;
    uint64_t sum2 = 0;
    for (int i = 0; i < LINE_COUNT; i++) 
    {
        sum += max[i];
        sum2 += max2[i];
    }

    // Output
    printf("results %d\n", sum);
    printf("results 2 %lld\n\n", sum2);

    return EXIT_SUCCESS;
}