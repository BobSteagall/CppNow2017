//==================================================================================================
//  File:
//      container_tests.cpp
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#include "container_tests.h"

void    run_container_deque_tests();
void    run_container_fwdlist_tests();
void    run_container_list_tests();
void    run_container_vector_tests();

void    run_container_map_tests();
void    run_container_umap_tests();

void
run_container_tests()
{
    run_container_deque_tests();
    run_container_fwdlist_tests();
    run_container_list_tests();
    run_container_vector_tests();

    run_container_map_tests();
    run_container_umap_tests();

    printf("\n\n\n");
}
