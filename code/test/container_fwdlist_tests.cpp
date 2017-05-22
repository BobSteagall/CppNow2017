//==================================================================================================
//  File:
//      container_fwdlist_tests.cpp
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#define ENABLE_PRINT

#include "container_fwdlist_tests.h"

#define RUN_FWDLIST_TESTS(ST)               run_fwdlist_normal_tests<ST>(#ST)

#ifndef COMPILER_GCC
    #define RUN_FWDLIST_RELOC_TESTS(ST)     run_fwdlist_reloc_tests<ST>(#ST)
#else
    #define RUN_FWDLIST_RELOC_TESTS(ST)
#endif

#define RUN_FWDLIST_POC_TESTS(POCCA, POCMA, POCS, EQ)  \
                                            run_fwdlist_poc_tests<POCCA,POCMA,POCS,EQ>();

void
run_container_fwdlist_tests()
{
    RUN_FWDLIST_TESTS(wrapper_strategy);
    RUN_FWDLIST_TESTS(based_2d_strategy);
    RUN_FWDLIST_RELOC_TESTS(based_2d_strategy);

    //- Vary POCCA and POCMA, holding POCS as true_type.
    //
    RUN_FWDLIST_POC_TESTS(std::true_type,  std::true_type,  std::true_type,  true);
    RUN_FWDLIST_POC_TESTS(std::false_type, std::true_type,  std::true_type,  true);
    RUN_FWDLIST_POC_TESTS(std::false_type, std::true_type,  std::true_type,  false);

    RUN_FWDLIST_POC_TESTS(std::true_type,  std::false_type, std::true_type,  true);
    RUN_FWDLIST_POC_TESTS(std::false_type, std::false_type, std::true_type,  true);
    RUN_FWDLIST_POC_TESTS(std::false_type, std::false_type, std::true_type,  false);

    RUN_FWDLIST_POC_TESTS(std::true_type,  std::true_type,  std::true_type,  true);
    RUN_FWDLIST_POC_TESTS(std::true_type,  std::false_type, std::true_type,  true);
    RUN_FWDLIST_POC_TESTS(std::true_type,  std::false_type, std::true_type,  false);

    RUN_FWDLIST_POC_TESTS(std::false_type, std::true_type,  std::true_type,  true);
    RUN_FWDLIST_POC_TESTS(std::false_type, std::false_type, std::true_type,  true);
    RUN_FWDLIST_POC_TESTS(std::false_type, std::false_type, std::true_type,  false);

    //- Vary POCCA and POCMA, holding POCS as false_type.  Not testing POCS == false_type
    //  and A1 != A2, as this is undefined behavior.
    //
    RUN_FWDLIST_POC_TESTS(std::true_type,  std::true_type,  std::false_type, true);
    RUN_FWDLIST_POC_TESTS(std::false_type, std::true_type,  std::false_type, true);

    RUN_FWDLIST_POC_TESTS(std::true_type,  std::false_type, std::false_type, true);
    RUN_FWDLIST_POC_TESTS(std::false_type, std::false_type, std::false_type, true);

    RUN_FWDLIST_POC_TESTS(std::true_type,  std::true_type,  std::false_type, true);
    RUN_FWDLIST_POC_TESTS(std::true_type,  std::false_type, std::false_type, true);

    RUN_FWDLIST_POC_TESTS(std::false_type, std::true_type,  std::false_type, true);
    RUN_FWDLIST_POC_TESTS(std::false_type, std::false_type, std::false_type, true);
}
