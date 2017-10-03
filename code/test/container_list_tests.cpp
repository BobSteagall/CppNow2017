//==================================================================================================
//  File:
//      container_list_tests.cpp
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#define ENABLE_PRINT

#include "container_list_tests.h"

#define RUN_LIST_TESTS(ST)              run_list_normal_tests<ST>(#ST)

#ifndef COMPILER_GCC
    #define RUN_LIST_RELOC_TESTS(ST)    run_list_reloc_tests<ST>(#ST)
#else
    #define RUN_LIST_RELOC_TESTS(ST)
#endif

#define RUN_LIST_POC_TESTS(POCCA, POCMA, POCS, EQ)  \
                                        run_list_poc_tests<POCCA,POCMA,POCS,EQ>();

void
run_container_list_tests()
{
    RUN_LIST_TESTS(wrapper_strategy);
    RUN_LIST_TESTS(based_2dxl_strategy);
    RUN_LIST_RELOC_TESTS(based_2dxl_strategy);

    //- Vary POCCA and POCMA, holding POCS as true_type.
    //
    RUN_LIST_POC_TESTS(std::true_type,  std::true_type,  std::true_type,  true);
    RUN_LIST_POC_TESTS(std::false_type, std::true_type,  std::true_type,  true);
#ifndef COMPILER_GCC
    RUN_LIST_POC_TESTS(std::false_type, std::true_type,  std::true_type,  false);
#endif

    RUN_LIST_POC_TESTS(std::true_type,  std::false_type, std::true_type,  true);
    RUN_LIST_POC_TESTS(std::false_type, std::false_type, std::true_type,  true);
#ifndef COMPILER_GCC
    RUN_LIST_POC_TESTS(std::false_type, std::false_type, std::true_type,  false);
#endif

    RUN_LIST_POC_TESTS(std::true_type,  std::true_type,  std::true_type,  true);
    RUN_LIST_POC_TESTS(std::true_type,  std::false_type, std::true_type,  true);
#ifndef COMPILER_GCC
    RUN_LIST_POC_TESTS(std::true_type,  std::false_type, std::true_type,  false);
#endif

    RUN_LIST_POC_TESTS(std::false_type, std::true_type,  std::true_type,  true);
    RUN_LIST_POC_TESTS(std::false_type, std::false_type, std::true_type,  true);
#ifndef COMPILER_GCC
    RUN_LIST_POC_TESTS(std::false_type, std::false_type, std::true_type,  false);
#endif

    //- Vary POCCA and POCMA, holding POCS as false_type.  Not testing POCS == false_type
    //  and A1 != A2, as this is undefined behavior.
    //
    RUN_LIST_POC_TESTS(std::true_type,  std::true_type,  std::false_type, true);
    RUN_LIST_POC_TESTS(std::false_type, std::true_type,  std::false_type, true);

    RUN_LIST_POC_TESTS(std::true_type,  std::false_type, std::false_type, true);
    RUN_LIST_POC_TESTS(std::false_type, std::false_type, std::false_type, true);

    RUN_LIST_POC_TESTS(std::true_type,  std::true_type,  std::false_type, true);
    RUN_LIST_POC_TESTS(std::true_type,  std::false_type, std::false_type, true);

    RUN_LIST_POC_TESTS(std::false_type, std::true_type,  std::false_type, true);
    RUN_LIST_POC_TESTS(std::false_type, std::false_type, std::false_type, true);
}
