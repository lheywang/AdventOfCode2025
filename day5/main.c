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

#define ID_CNT 1000
#define RANGE_CNT 179

uint64_t values[ID_CNT] = { 0 };
uint64_t ranges[RANGE_CNT][2] = { 0 };

typedef struct {
    uint64_t start;
    uint64_t end;
} Range;

int cmp(const void *a, const void *b) {
    const Range *ra = a;
    const Range *rb = b;
    if (ra->start < rb->start) return -1;
    if (ra->start > rb->start) return 1;
    return 0;
}

static Range st_ranges[RANGE_CNT] = { 0 };

int main(int argc, char **argv)
{
    // open the source file
    FILE* file = fopen("input/input.txt", "r");

    // Initialize some data
    char buffer[64] = {0};

    // Read the file and compute some elements
    bool mode = false;

    int value_id = 0;
    int range_id = 0;

    if (file != NULL)
    {   
        while (fgets(buffer, sizeof(buffer), file))
        {
            if (isdigit(buffer[0]) == 0)
                mode = true;

            if (buffer[0] == '\n')
                continue;

            switch (mode)
            {
                case false:
                    char *t1 = strtok(buffer, "-");
                    ranges[range_id][0] = (uint64_t)strtoul(t1, NULL, 10);
                    char *t2 = strtok(NULL, "-");
                    ranges[range_id][1] = (uint64_t)strtoul(t2, NULL, 10);
                    range_id += 1;
                    break;

                case true:
                    values[value_id] = (uint64_t)strtoul(buffer, NULL, 10);
                    value_id += 1;
                    break;
            }   
        }
        fclose(file);
    }
    else 
    {
        printf("Cannot open file !\n");
    }

    printf("\n\nRANGES\n\n");
    for (int i = 0; i < RANGE_CNT; i++)
    {
        printf("%lld - %lld\n", ranges[i][0], ranges[i][1]);
    }

    printf("\n\nVALUES\n\n");
    for (int i = 0; i < ID_CNT; i++)
    {
        printf("%lld\n", values[i]);
    }

    // Checking the fresh
    int fresh = 0;
    for (int i = 0; i < ID_CNT; i++)
    {
        for (int range_id = 0; range_id < RANGE_CNT; range_id ++)
        {
            if ((values[i] >= ranges[range_id][0]) && (values[i] <= ranges[range_id][1])) // Check if within ranges
            {
                fresh += 1;
                break; // We don't need to check others options, at least one was good
            }
        }
    }

    // Couting how many ID are okay
    // First sorting the array
    for (int i = 0; i < RANGE_CNT; i ++)
    {
        st_ranges[i].start = ranges[i][0];
        st_ranges[i].end = ranges[i][1];
    }

    qsort(st_ranges, RANGE_CNT, sizeof(Range), cmp);

    uint64_t total = 0;
    uint64_t cur_start = st_ranges[0].start;
    uint64_t cur_end   = st_ranges[0].end;

    for (size_t i = 1; i < RANGE_CNT; i++) {
        if (st_ranges[i].start <= cur_end + 1) {
            // Overlapping or adjacent
            if (st_ranges[i].end > cur_end)
                cur_end = st_ranges[i].end;
        } else {
            // Disjoint range → close previous
            total += cur_end - cur_start + 1;
            cur_start = st_ranges[i].start;
            cur_end   = st_ranges[i].end;
        }
    }

    // Last interval
    total += cur_end - cur_start + 1;

    printf("\n\nResult  : %d\n", fresh);
    printf("Result2 : %lld\n\n", total);

    return EXIT_SUCCESS;
}