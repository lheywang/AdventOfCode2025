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

/*
 * There's some overflow here, so we use 128 bits integers : 
 */

// #define DEBUG

#define DATA_LINE 4
#define DATA_CNT 1000
#define CHAR_LEN 3770

// Data storage
static uint64_t values[DATA_LINE][DATA_CNT] = { 0 };
static char raw_lines[DATA_LINE][CHAR_LEN] = { 0 };
static char operators[DATA_CNT] = { 0 };

static uint64_t results[DATA_CNT] = { 0 };
static uint64_t results2[DATA_CNT] = { 0 };

int main(int argc, char **argv)
{
    // open the source file
    FILE* file = fopen("input/input.txt", "r");

    // Initialize some data
    char buffer[CHAR_LEN] = {0};

    if (file != NULL)
    {   
        int line = 0;
        while (fgets(buffer, sizeof(buffer), file))
        {
            if (buffer[0] == '\n')
                continue;

            if (line < 4)
                memcpy((void*)raw_lines[line], (void*)buffer, (size_t)(CHAR_LEN));

            char *token = strtok(buffer, " ");
            int id = 0;
            while (token != NULL)
            {
                if (line < 4)
                { 
                    values[line][id] = (uint64_t)strtoul(token, NULL, 10);
                }
                else
                {
                    operators[id] = (char)token[0];
                }
                id += 1;

                token = strtok(NULL, " ");
            }
            memset((void*)buffer, 0x00, (size_t)sizeof(buffer));
            line += 1;
        }
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    // Then, we perform the computation :   
    for (int i = 0; i < DATA_CNT; i++)
    {
        switch (operators[i])
        {
            case '*':
                results[i] = ((values[0][i] * values[1][i]) * values[2][i]) * values[3][i];
                printf("Result (*) : %4ld * %4ld * %4ld * %4ld = %20ld\n", values[0][i], values[1][i], values[2][i], values[3][i], results[i]);
                break;
            case '+':
                results[i] = values[0][i] + values[1][i] + values[2][i] + values[3][i];
                printf("Result (+) : %4ld + %4ld + %4ld + %4ld = %20ld\n", values[0][i], values[1][i], values[2][i], values[3][i], results[i]);
                break;
            default:
                results[i] = 0;
                break;
        }
    }

    // Showing the lines : 
    for (int i = 0; i < DATA_LINE + 1; i++)
    {
        printf("%s\n", raw_lines[i]);
    }

    // Summing all of the results
    uint64_t res = 0;
    uint64_t res2 = 0;
    for (int i = 0; i < DATA_CNT; i++)
    {
        res += results[i];
        res2 += results2[i];
    }

    // Outputs
    printf("\n\nResult 1 = %ld", res);
    printf("\nResult 2 = %ld\n\n", (uint64_t)0);

    return EXIT_SUCCESS;
}