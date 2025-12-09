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

            count_save -= 1;
        }
    }

    return value;
}

int main(int argc, char **argv)
{
    // open the source file
    FILE* file = fopen("input/input.txt", "r");

    // Initialize some data
    char buffer[8] = {0};
    int position = 0;
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

            position = increment_value(next_value);
            if (position == 0)
            {
                pass +=1 ;
            }

            printf("Raw : %s--> Value = %d\n--> New = %d\n", buffer, next_value, position);
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