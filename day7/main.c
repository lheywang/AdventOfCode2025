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

    // Showing memory status
    for (int i = 0; i < LINE_NB; i++)
    {
        for (int ii = 0; ii < COLU_NB; ii++)
        {
            printf("%c", array[i][ii]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}