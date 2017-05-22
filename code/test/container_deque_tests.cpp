//==================================================================================================
//  File:
//      container_deque_tests.cpp
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#define ENABLE_PRINT

#include "container_deque_tests.h"

#define RUN_DEQUE_TESTS(ST)             run_deque_normal_tests<ST>(#ST)

#ifndef COMPILER_GCC
    #define RUN_DEQUE_RELOC_TESTS(ST)   run_deque_reloc_tests<ST>(#ST)
#else
    #define RUN_DEQUE_RELOC_TESTS(ST)
#endif

#define RUN_DEQUE_POC_TESTS(POCCA, POCMA, POCS, EQ)  \
                                        run_deque_poc_tests<POCCA,POCMA,POCS,EQ>();

void
run_container_deque_tests()
{
    RUN_DEQUE_TESTS(wrapper_strategy);
    RUN_DEQUE_TESTS(based_2d_strategy);
    RUN_DEQUE_RELOC_TESTS(based_2d_strategy);

    //- Vary POCCA and POCMA, holding POCS as true_type.
    //
    RUN_DEQUE_POC_TESTS(std::true_type,  std::true_type,  std::true_type,  true);
    RUN_DEQUE_POC_TESTS(std::false_type, std::true_type,  std::true_type,  true);
    RUN_DEQUE_POC_TESTS(std::false_type, std::true_type,  std::true_type,  false);

    RUN_DEQUE_POC_TESTS(std::true_type,  std::false_type, std::true_type,  true);
    RUN_DEQUE_POC_TESTS(std::false_type, std::false_type, std::true_type,  true);
    RUN_DEQUE_POC_TESTS(std::false_type, std::false_type, std::true_type,  false);

    RUN_DEQUE_POC_TESTS(std::true_type,  std::true_type,  std::true_type,  true);
    RUN_DEQUE_POC_TESTS(std::true_type,  std::false_type, std::true_type,  true);
    RUN_DEQUE_POC_TESTS(std::true_type,  std::false_type, std::true_type,  false);

    RUN_DEQUE_POC_TESTS(std::false_type, std::true_type,  std::true_type,  true);
    RUN_DEQUE_POC_TESTS(std::false_type, std::false_type, std::true_type,  true);
    RUN_DEQUE_POC_TESTS(std::false_type, std::false_type, std::true_type,  false);

    //- Vary POCCA and POCMA, holding POCS as false_type.  Not testing POCS == false_type
    //  and A1 != A2, as this is undefined behavior.
    //
    RUN_DEQUE_POC_TESTS(std::true_type,  std::true_type,  std::false_type, true);
    RUN_DEQUE_POC_TESTS(std::false_type, std::true_type,  std::false_type, true);

    RUN_DEQUE_POC_TESTS(std::true_type,  std::false_type, std::false_type, true);
    RUN_DEQUE_POC_TESTS(std::false_type, std::false_type, std::false_type, true);

    RUN_DEQUE_POC_TESTS(std::true_type,  std::true_type,  std::false_type, true);
    RUN_DEQUE_POC_TESTS(std::true_type,  std::false_type, std::false_type, true);

    RUN_DEQUE_POC_TESTS(std::false_type, std::true_type,  std::false_type, true);
    RUN_DEQUE_POC_TESTS(std::false_type, std::false_type, std::false_type, true);
}
