//==================================================================================================
//  File:
//      main.cpp
//
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#include <cstdio>
#include <cstdlib>
#include <cstring>

void    run_container_tests();
void    run_pointer_tests();

bool    contnrs_only = false;
bool    timings_only = false;
bool    verbose_flag = false;
size_t  max_elem_idx = 13;

bool
verbose_output()
{
    return verbose_flag;
}

size_t
max_ptr_op_count_index()
{
    return max_elem_idx;
}

void
print_help()
{
    printf("usage: alloc [-c] [-t] [-p N]\n");
    printf("\n");
    printf("       -c       run only allocator awareness conformance tests\n\n");
    printf("       -t       run only synthetic pointer timing tests\n\n");
    printf("       -p N     run synthetic pointer performance tests on the first thru\n");
    printf("                the Nth element set, where N = [1, 13] and the element\n");
    printf("                counts are:\n");
    printf("                   N     Elem Count\n");
    printf("                  ---    ----------\n");
    printf("                   1          100\n");
    printf("                   2          200\n");
    printf("                   3          500\n");
    printf("                   4         1000\n");
    printf("                   5         2000\n");
    printf("                   6         5000\n");
    printf("                   7        10000\n");
    printf("                   8        20000\n");
    printf("                   9        50000\n");
    printf("                  10       100000\n");
    printf("                  11       200000\n");
    printf("                  12       500000\n");
    printf("                  13      1000000\n\n");
}

int 
main(int argc, char* argv[])
{
    if (argc == 1)
    {
        print_help();
    }
    else
    {
        for (int i = 1;  i < argc;  ++i)
        {
            if (strcmp(argv[i], "-h") == 0)
            {
                print_help();
                return 0;
            }
            else if (strcmp(argv[i], "-c") == 0)
            {
                contnrs_only = true;
            }
            else if (strcmp(argv[i], "-t") == 0)
            {
                timings_only = true;
            }
            else if (strcmp(argv[i], "-v") == 0)
            {
                verbose_flag = true;
            }
            else if (strcmp(argv[i], "-p") == 0)
            {
                if (++i < argc)
                {
                    max_elem_idx = (size_t) atoi(argv[i]);

                }
            }
        }

        if (!timings_only)
        {
            run_container_tests();
        }

        if (!contnrs_only)
        {
            run_pointer_tests();
        }
    }
    return 0;
}
