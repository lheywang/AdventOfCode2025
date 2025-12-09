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

int main(int argc, char **argv)
{
    // open the source file
    FILE* file = fopen("input/input.txt", "r");

    // Initialize some data
    char buffer[1024] = {0};
    int val1, val2;

    // Read the file and compute some elements
    if (file != NULL)
    {   
        while (fgets(buffer, sizeof(buffer), file))
        {
            sscanf(buffer, "%d-%d", val1, val2);
            printf("%d | %d\n", val1, val2);
        }
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    return EXIT_SUCCESS;
}