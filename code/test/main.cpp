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


int main(int argc, char* argv[])
{
    for (int i = 1;  i < argc;  ++i)
    {
        if (strcmp(argv[i], "-c") == 0)
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

    return 0;
}
