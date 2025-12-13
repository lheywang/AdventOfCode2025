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
#include <math.h>
#include <stdint.h>

#define NB_COUNT 64

#define MAX_INVALID 100000

uint64_t invalids[MAX_INVALID];
size_t invalid_count = 0;

int count_digits(unsigned long long n) {
    int digits = 0;
    if (n == 0) return 1;  // Special case for 0
    while (n > 0) {
        n /= 10;
        digits++;
    }
    return digits;
}

int cmp_u64(const void *a, const void *b) {
    uint64_t x = *(const uint64_t *)a;
    uint64_t y = *(const uint64_t *)b;
    return (x > y) - (x < y);
}

bool is_multiple_of_smaller_pattern(uint64_t n, uint64_t cell_size) {
    char s[32];
    sprintf(s, "%llu", (unsigned long long)n);

    int len = strlen(s);

    for (int p = 1; p < cell_size; p++) {
        if (len % p != 0) continue;

        bool ok = true;
        for (int i = p; i < len; i++) {
            if (s[i] != s[i % p]) {
                ok = false;
                break;
            }
        }
        if (ok) return true;  // smaller pattern exists
    }
    return false;
}

uint64_t get_doubles(uint64_t values[2][NB_COUNT]){
    // Preparing the output
    uint64_t pass = 0;

    // Print the values
    for (int k = 0; k < NB_COUNT; k++)
    {
        printf("-------------------------------------------\n");
        printf("%12llu - %12llu\n", values[0][k], values[1][k]);
        printf("-------------------------------------------\n");

        // First, get the length of the numbers
        uint64_t first = count_digits(values[0][k]);
        uint64_t stop = count_digits(values[1][k]);

        // First condition : If lenghts aren't even, there CAN'T be two identical parts...s
        if ((first & 0x1) && (stop & 0x1))
        {
            continue;
        }

        // Then, get the shortest element len and divide by two (to get the cell size)
        uint64_t cell_size = ((stop > first) ? stop : first) / 2;

        // Get the power of ten factor that correspond to this number
        uint64_t factor = 1;
        for (uint64_t i = 0; i < cell_size; i++)
            factor *= 10;

        printf("    Found a cell size of %d digits\n", cell_size);
        printf("    Nearest 10 power is : %d\n", factor);

        // Getting the limits of the range we're going to compute on : 
        uint64_t first_cell = (values[0][k] / factor);
        uint64_t stop_cell  = (values[1][k] / factor) + 1;

        // Ensure results are stricly positive
        first_cell = (first_cell > 0) ? first_cell - 1: first_cell;

        printf("    Start ID : %d; End ID : %d\n", first_cell, stop_cell);

        // Then, iterate within this range :
        for (uint64_t val = first_cell; val <= stop_cell; val ++)
        {
            /*
             * CASE 0 : Two ID per ranges
             */
            // Compute the value that is formed by this couple : 
            uint64_t tmp = (val * factor) + val;

            printf("    Trying %llu...\n", tmp);

            // Then, check if this value is within the values : 
            if ((values[0][k] <= tmp) && (tmp <= values[1][k]))
            {
                if ((count_digits(tmp) % 2) == 0)
                {
                    printf("    Found value : %llu\n", tmp);
                    invalids[invalid_count++] = tmp;
                }
            }
        }
    }

    return pass;
}

uint64_t get_triples(uint64_t values[2][NB_COUNT]){
    // Preparing the output
    uint64_t pass = 0;

    // Print the values
    for (int k = 0; k < NB_COUNT; k++)
    {
        printf("-------------------------------------------\n");
        printf("%12llu - %12llu\n", values[0][k], values[1][k]);
        printf("-------------------------------------------\n");

        // First, get the length of the numbers
        uint64_t first = count_digits(values[0][k]);
        uint64_t stop = count_digits(values[1][k]);

        // First condition : If lenghts aren't even, there CAN'T be two identical parts...
        if (((first % 3) != 0) && ((stop % 3) != 0))
        {
            continue;
        }

        // Then, get the shortest element len and divide by two (to get the cell size)
        uint64_t cell_size = ((stop > first) ? stop : first) / 3;

        // Get the power of ten factor that correspond to this number
        uint64_t factor = 1;
        for (uint64_t i = 0; i < cell_size; i++)
            factor *= 10;

        printf("    Found a cell size of %d digits\n", cell_size);
        printf("    Nearest 10 power is : %d\n", factor);

        // Getting the limits of the range we're going to compute on : 
        uint64_t first_cell = (values[0][k] / (factor * factor));
        uint64_t stop_cell  = (values[1][k] / (factor * factor)) + 1;

        // Ensure results are stricly positive
        first_cell = (first_cell > 0) ? first_cell - 1: first_cell;

        printf("    Start ID : %d; End ID : %d\n", first_cell, stop_cell);

        // Then, iterate within this range :
        for (uint64_t val = first_cell; val <= stop_cell; val ++)
        {
            /*
             * CASE 0 : Two ID per ranges
             */
            // Compute the value that is formed by this couple : 
            uint64_t tmp = (val * factor * factor) + 
                           (val * factor) + 
                           val;

            printf("    Trying %llu...\n", tmp);

            // Then, check if this value is within the values : 
            if ((values[0][k] <= tmp) && (tmp <= values[1][k]))
            {
                if ((count_digits(tmp) % 3) == 0)
                {
                    printf("    Found value : %llu\n", tmp);
                    invalids[invalid_count++] = tmp;
                }
            }
        }
    }

    return pass;
}

uint64_t get_quad(uint64_t values[2][NB_COUNT]){
    // Preparing the output
    uint64_t pass = 0;

    // Print the values
    for (int k = 0; k < NB_COUNT; k++)
    {
        printf("-------------------------------------------\n");
        printf("%12llu - %12llu\n", values[0][k], values[1][k]);
        printf("-------------------------------------------\n");

        // First, get the length of the numbers
        uint64_t first = count_digits(values[0][k]);
        uint64_t stop = count_digits(values[1][k]);

        // First condition : If lenghts aren't even, there CAN'T be two identical parts...s
        if (((first % 4) != 0) && ((stop % 4) != 0))
        {
            continue;
        }

        // Then, get the shortest element len and divide by two (to get the cell size)
        uint64_t cell_size = ((stop > first) ? stop : first) / 4;

        // Get the power of ten factor that correspond to this number
        uint64_t factor = 1;
        for (uint64_t i = 0; i < cell_size; i++)
            factor *= 10;

        printf("    Found a cell size of %d digits\n", cell_size);
        printf("    Nearest 10 power is : %d\n", factor);

        // Getting the limits of the range we're going to compute on : 
        uint64_t first_cell = (values[0][k] / (factor * factor * factor));
        uint64_t stop_cell  = (values[1][k] / (factor * factor * factor)) + 1;

        // Ensure results are stricly positive
        first_cell = (first_cell > 0) ? first_cell - 1: first_cell;

        printf("    Start ID : %d; End ID : %d\n", first_cell, stop_cell);

        // Then, iterate within this range :
        for (uint64_t val = first_cell; val <= stop_cell; val ++)
        {
            /*
             * CASE 0 : Two ID per ranges
             */
            // Compute the value that is formed by this couple : 
            uint64_t tmp = (val * factor * factor * factor) + 
                           (val * factor * factor) + 
                           (val * factor) + 
                           val;

            printf("    Trying %llu...\n", tmp);

            // Then, check if this value is within the values : 
            if ((values[0][k] <= tmp) && (tmp <= values[1][k]))
            {
                if ((count_digits(tmp) % 4) == 0)
                {
                    printf("    Found value : %llu\n", tmp);
                    invalids[invalid_count++] = tmp;
                }
            }
        }
    }

    return pass;
}

uint64_t get_five(uint64_t values[2][NB_COUNT]){
    // Preparing the output
    uint64_t pass = 0;

    // Print the values
    for (int k = 0; k < NB_COUNT; k++)
    {
        printf("-------------------------------------------\n");
        printf("%12llu - %12llu\n", values[0][k], values[1][k]);
        printf("-------------------------------------------\n");

        // First, get the length of the numbers
        uint64_t first = count_digits(values[0][k]);
        uint64_t stop = count_digits(values[1][k]);

        // First condition : If lenghts aren't even, there CAN'T be two identical parts...s
        if (((first % 5) != 0) && ((stop % 5) != 0))
        {
            continue;
        }

        // Then, get the shortest element len and divide by two (to get the cell size)
        uint64_t cell_size = ((stop > first) ? stop : first) / 5;

        // Get the power of ten factor that correspond to this number
        uint64_t factor = 1;
        for (uint64_t i = 0; i < cell_size; i++)
            factor *= 10;

        printf("    Found a cell size of %d digits\n", cell_size);
        printf("    Nearest 10 power is : %d\n", factor);

        // Getting the limits of the range we're going to compute on : 
        uint64_t first_cell = (values[0][k] / (factor * factor * factor * factor));
        uint64_t stop_cell  = (values[1][k] / (factor * factor * factor * factor)) + 1;

        // Ensure results are stricly positive
        first_cell = (first_cell > 0) ? first_cell - 1: first_cell;

        printf("    Start ID : %d; End ID : %d\n", first_cell, stop_cell);

        // Then, iterate within this range :
        for (uint64_t val = first_cell; val <= stop_cell; val ++)
        {
            /*
             * CASE 0 : Two ID per ranges
             */
            // Compute the value that is formed by this couple : 
            uint64_t tmp = (val * factor * factor * factor * factor) + 
                           (val * factor * factor * factor) + 
                           (val * factor * factor) + 
                           (val * factor) + 
                           val;

            printf("    Trying %llu...\n", tmp);

            // Then, check if this value is within the values : 
            if ((values[0][k] <= tmp) && (tmp <= values[1][k]))
            {
                if ((count_digits(tmp) % 5) == 0)
                {
                    printf("    Found value : %llu\n", tmp);
                    invalids[invalid_count++] = tmp;
                }
            }
        }
    }

    return pass;
}

int main(int argc, char **argv)
{
    // open the source file
    FILE* file = fopen("input/input.txt", "r");

    // Initialize some data
    char buffer[1024] = {0};
   
    uint64_t values[2][NB_COUNT] = { 0 };

    // Read the file and compute some elements
    int id = 0;
    if (file != NULL)
    {   
        while (fgets(buffer, sizeof(buffer), file))
        {
            char *pair_str = strtok(buffer, ",");  // Split by comma

            while (pair_str != NULL) {
                uint64_t start, end;
                if (sscanf(pair_str, "%llu-%llu", &start, &end) == 2) {
                    values[0][id] = start;
                    values[1][id] = end;
                    id += 1;
                }
                pair_str = strtok(NULL, ",");
            }
        }
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    // Get doubles
    uint64_t pass[4] = { 0 };
    pass[0] += get_doubles(values);

    // STOP here for stage 1

    printf("\n============== TRIPLES ================\n\n");
    pass[1] = get_triples(values);
    printf("\n==============  QUAD   ================\n\n");
    pass[2] = get_quad(values);
    printf("\n==============  FIVE   ================\n\n");
    pass[3] = get_five(values);

    // Stop here for stage 2

    // Sorting the elements
    qsort(invalids, invalid_count, sizeof(uint64_t), cmp_u64);

    // Suming them
    uint64_t sum = 0;

    for (size_t i = 0; i < invalid_count; i++) {
        if (i == 0 || invalids[i] != invalids[i - 1]) {
            sum += invalids[i];
            printf("Invalid ID: %llu\n", invalids[i]);
        }
        else
        {
            printf("    Duplicate : %llu\n", invalids[i]);
        }
    }

    // Output
    printf("Output sum : %16llu\n\n", sum);


    return EXIT_SUCCESS;
}