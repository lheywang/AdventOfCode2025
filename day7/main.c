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
                    if (i > 1) {output[i - 1] = USED;}
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
                        break;
                    case '^':
                        array[line][chr] = SPLT;
                        break;
                    case '.':
                    default:
                        array[line][chr] = FREE;
                        break;
                }
            }
            line += 1;
            // memset((void *)buffer, 0x00, (size_t)sizeof(buffer));
        }
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    int splits = 0;
    for (int lines = 0; lines < (LINE_NB - 1); lines ++)
    {

        int tmp = process_line(array[lines], array[lines + 1]); // process a line, and output it into the next one
        splits += tmp;

        printf("Line %d : Splits %d\n", lines, tmp);

        // Showing memory status
        for (int i = 0; i < LINE_NB; i++)
        {
            for (int ii = 0; ii < COLU_NB; ii++)
            {
                printf("%c", array[i][ii]);
            }
            printf("\n");
        }
    }

    printf("\n\n");
    printf("Result 1 : %d\n", splits);
    printf("Result 2 : %d\n", 0);
    printf("\n\n");

    return EXIT_SUCCESS;
}