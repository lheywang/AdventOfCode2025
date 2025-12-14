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

// Data storages (use too much stack otherwise)
static uint8_t rolls[LINE_LEN][COL_LEN] = { 0 };
static uint8_t rolls_cnt[LINE_LEN][COL_LEN] = { 0 };

int count_rolls(int data[3][3])
{
    return  data[0][0] +
            data[0][1] +
            data[0][2] +
            data[1][0] + // ignore data[1][1] since we count neighbors and not the roll by itself
            data[1][2] +
            data[2][0] +
            data[2][1] +
            data[2][2];
}

int remove_rolls()
{
    
    printf("\n\nDATA WITH PADDING\n\n");
    for (int y = 0; y < LINE_LEN; y ++)
    {
        for (int x = 0; x < COL_LEN; x++)
        {
            printf("%d", rolls[y][x]);
        }
        printf("\n");
    }

#ifdef DEBUG
    printf("\n\nTEMP ARRAYS\n\n");
#endif

    // Iterate over the array and store how many neighbors does the rolls have
    for (int y = 1; y < LINE_LEN - 1; y ++)
    {
        for (int x = 1; x < COL_LEN - 1; x++)
        {
            // Create the temp array and fill it with the data
            int tmp[3][3] = {0};
            tmp[0][0] = rolls[y - 1][x - 1];
            tmp[0][1] = rolls[y - 1][x    ];
            tmp[0][2] = rolls[y - 1][x + 1];

            tmp[1][0] = rolls[y    ][x - 1];
            tmp[1][1] = rolls[y    ][x    ];
            tmp[1][2] = rolls[y    ][x + 1];

            tmp[2][0] = rolls[y + 1][x - 1];
            tmp[2][1] = rolls[y + 1][x    ];
            tmp[2][2] = rolls[y + 1][x + 1];

#ifdef DEBUG
            printf("X = %d, Y = %d\n", y, x);
            for (int i = 0; i < 3; i++)
            {
                for (int ii = 0; ii < 3; ii ++)
                {
                    printf("%d", tmp[i][ii]);
                }
                printf("\n");
            }
#endif
            rolls_cnt[y][x] = count_rolls(tmp);
        }
#ifdef DEBUG
        printf("\n");
#endif
    }

    printf("\n\nDATA WITH COUNT (W/ PADDING)\n\n");
    int sum = 0;
    for (int y = 1; y < LINE_LEN - 1; y ++)
    {
        for (int x = 1; x < COL_LEN - 1; x++)
        {
            printf("%d", rolls_cnt[y][x]);
            if (rolls_cnt[y][x] < 4)
            {
                if (rolls[y][x] != 0)
                {
                    sum += 1;
                    rolls[y][x] = 0; // Remove the roll on this location. --> This will update them
                }     
            }
        }
        printf("\n");
    }

    return sum;
}

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
            for (int i = 0; i < COL_COUNT; i++)
            {
                if (buffer[i] == '@')
                {
                    rolls[id][i + 1] = 1;
                }
                else if (buffer[i] == '.')
                {
                    rolls[id][i + 1] = 0;
                }
                else
                {
                    continue;
                }
#ifdef DEBUG
                printf("%c : %d --> X = %d, Y = %d\n", buffer[i], rolls[id][i + 1], id, i + 1);
#endif
            }
            id += 1;
            
        }
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    int sum = 0;
    while (true)
    {
        int tmp = remove_rolls();
        if (tmp != 0)
            sum += tmp;
        else
            break;
    }

    printf("\nresult : %d\n\n", sum);

    return EXIT_SUCCESS;
}