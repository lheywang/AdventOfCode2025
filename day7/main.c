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

#define LINE_NB 142
#define COLU_NB 141

#define FREE (' ')
#define USED ('o')
#define SPLT ('^')

static uint8_t array[LINE_NB][COLU_NB] = { 0 };
static uint64_t ways[LINE_NB][COLU_NB] = { 0 }; // For step 2

int process_line(uint8_t input[COLU_NB], uint8_t output[COLU_NB])
{
    int switches = 0;
    for (int i = 0; i < COLU_NB; i++)
    {
        /*
         * Check if there was an element on this line
         */
        if (input[i] == USED)
        {
            switch (output[i])
            {
                case FREE:
                    output[i] = USED; // report one line under
                    break;
                case SPLT:
                    if (i > 0) {output[i - 1] = USED;}
                    if (i < (COLU_NB - 1)) {output[i + 1] = USED;}
                    switches += 1;
                    break;

                // Do nothing
                case USED:
                default:
                    break;
            }
        }
    }

    return switches;
}

int count_ways(uint64_t input[COLU_NB], uint64_t output[COLU_NB], uint8_t elements[COLU_NB])
{
    for (int i = 0; i < COLU_NB; i++)
    {
        uint64_t w = input[i];

        // Ignore if no ways are presents --> won't change the output.
        if (w == 0)
            continue;

        // Handle the cases :
        switch (elements[i])
        {
            case FREE:
            case USED:
                output[i] += w;
                break;
            case SPLT:
                if (i > 0) {output[i - 1] += w;}
                if (i < (COLU_NB - 1)) {output[i + 1] += w;}
                break;
            default:
                break;

        } 
    }
}

int main(int argc, char **argv)
{
    // open the source file
    FILE* file = fopen("input/input.txt", "r");

    // Initialize some data
    char buffer[COLU_NB + 2] = {0};
    int line = 0;

    if (file != NULL)
    {   
        while (fgets(buffer, sizeof(buffer), file))
        {
            if (buffer[0] == '\n')
                continue;

            for (int chr = 0; chr < COLU_NB; chr ++)
            {
                switch (buffer[chr])
                {
                    case 'S':
                        array[line][chr] = USED;
                        ways[line][chr] = 1;
                        break;
                    case '^':
                        array[line][chr] = SPLT;
                        ways[line][chr] = 0;
                        break;
                    case '.':
                    default:
                        array[line][chr] = FREE;
                        ways[line][chr] = 0;
                        break;
                }
            }
            line += 1;
        }
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    // Compute stage 2 before going on stage 1
    for (int lines = 0; lines < (LINE_NB - 1); lines ++)
    {
        count_ways(ways[lines], ways[lines + 1], array[lines]);
    }

    int splits = 0;
    for (int lines = 0; lines < (LINE_NB - 1); lines ++)
    {
        splits += process_line(array[lines], array[lines + 1]); // process a line, and output it into the next one
    }

    // Couting the ways (last line)
    uint64_t sum = 0;
    for (int i = 0; i < COLU_NB; i++)
    {
        sum += ways[LINE_NB - 1][i];
        printf("%3d --> %16lld | %16lld\n", i, ways[LINE_NB - 1][i], sum);
    }

    printf("\n\n");
    printf("Result 1 : %d\n", splits);
    printf("Result 2 : %lld\n", sum);
    printf("\n\n");

    return EXIT_SUCCESS;
}