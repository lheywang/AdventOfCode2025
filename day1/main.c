/**
 *  @file day1/main.c
 *
 *  @brief challenge 1 main C file
 * 
 *  @author l.heywang <leonard.heywang@proton.me>
 *  @date   09/12/2025
 * 
 * */

#include <stdio.h>
#include <stdlib.h>

#define MAX_POSITION 100

int increment_value(int count)
{
    static int value = 50;
    static int pass = 0;
    static int old_pass = 0;

    int count_save = abs(count);

    /*
     * This highly unoptimized loop took place when tried debugging my own brain (I didn't read the whole requirements)
     */
    if (count > 0)
    {
        while (count_save != 0)
        {
            value += 1;
            if (value == 100)
            {
                value = 0;
            }

            if (value == 0)
            {
                pass += 1;
            }

            count_save -= 1;
        }
    }
    else
    {
        while (count_save != 0)
        {
            value -= 1;
            if (value == -1)
            {
                value = 99;
            }

            if (value == 0)
            {
                pass += 1;
            }

            count_save -= 1;
        }
    }

    /*
     * For step 1 purposes
     */
    if (value == 0)
        old_pass += 1;

    printf("Command | New | Zeros = %4d | %4d | %4d\n", count, value, pass);
    return pass;
}

int main(int argc, char **argv)
{
    // open the source file
    FILE* file = fopen("input/input.txt", "r");

    // Initialize some data
    char buffer[8] = {0};
    int pass = 0;

    int next_value = 0;

    // Read the file and compute some elements
    if (file != NULL)
    {   
        while (fgets(buffer, sizeof(buffer), file))
        {
            // Parse the line to get the value : 
            switch (buffer[0])
            {
                case 'R' :
                    next_value = strtol((void *)&buffer[1], NULL, 10);
                    break;
                case 'L' : 
                    next_value = -strtol((void *)&buffer[1], NULL, 10);
                    break;
                default :
                    next_value = 0;
                    break;
            }

            pass = increment_value(next_value);
        }

        printf("Pass = %d\n", pass);
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    return EXIT_SUCCESS;
}