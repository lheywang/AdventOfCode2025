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

#define LINE_COUNT 136
#define COL_COUNT 138 // Why, but it works....

#define LINE_LEN (LINE_COUNT + 2)
#define COL_LEN (COL_COUNT + 2)

// Data storages (use too much stack otherwise)
static int rolls[LINE_LEN][COL_LEN] = { 0 };
static int rolls_cnt[LINE_LEN][COL_LEN] = { 0 };

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
            for (int i = 1; i < COL_COUNT + 1; i++)
            {
                rolls[id][i] = (buffer[i] == '@') ? 1 : 0;
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

    // Iterate over the array and store how many neighbors does the rolls have
    for (int y = 0; y < LINE_LEN; y ++)
    {
        for (int x = 0; x < COL_LEN; x++)
        {
            printf("%d", rolls[x][y]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}