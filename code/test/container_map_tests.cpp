//==================================================================================================
//  File:
//      container_map_tests.cpp
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#define ENABLE_PRINT

#include "container_map_tests.h"

#define RUN_MAP_TESTS(ST)               run_map_normal_tests<ST>(#ST)

#ifndef COMPILER_GCC
    #define RUN_MAP_RELOC_TESTS(ST)     run_map_reloc_tests<ST>(#ST)
#else
    #define RUN_MAP_RELOC_TESTS(ST)
#endif

#define RUN_MAP_POC_TESTS(POCCA, POCMA, POCS, EQ)  \
                                        run_map_poc_tests<POCCA,POCMA,POCS,EQ>();

void
run_container_map_tests()
{
    RUN_MAP_TESTS(wrapper_strategy);
    RUN_MAP_TESTS(based_2dxl_strategy);

#ifndef COMPILER_MS
    RUN_MAP_RELOC_TESTS(based_2d_strategy); 
#endif

#if defined(COMPILER_MS) && (_MSC_VER > 1900)
    RUN_MAP_RELOC_TESTS(based_2dxl_strategy);
#endif

    //- Vary POCCA and POCMA, holding POCS as true_type.
    //
    RUN_MAP_POC_TESTS(std::true_type,  std::true_type,  std::true_type,  true);
    RUN_MAP_POC_TESTS(std::false_type, std::true_type,  std::true_type,  true);
    RUN_MAP_POC_TESTS(std::false_type, std::true_type,  std::true_type,  false);

    RUN_MAP_POC_TESTS(std::true_type,  std::false_type, std::true_type,  true);
    RUN_MAP_POC_TESTS(std::false_type, std::false_type, std::true_type,  true);
    RUN_MAP_POC_TESTS(std::false_type, std::false_type, std::true_type,  false);

    RUN_MAP_POC_TESTS(std::true_type,  std::true_type,  std::true_type,  true);
    RUN_MAP_POC_TESTS(std::true_type,  std::false_type, std::true_type,  true);
    RUN_MAP_POC_TESTS(std::true_type,  std::false_type, std::true_type,  false);

    RUN_MAP_POC_TESTS(std::false_type, std::true_type,  std::true_type,  true);
    RUN_MAP_POC_TESTS(std::false_type, std::false_type, std::true_type,  true);
    RUN_MAP_POC_TESTS(std::false_type, std::false_type, std::true_type,  false);

    //- Vary POCCA and POCMA, holding POCS as false_type.  Not testing POCS == false_type
    //  and A1 != A2, as this is undefined behavior.
    //
    RUN_MAP_POC_TESTS(std::true_type,  std::true_type,  std::false_type, true);
    RUN_MAP_POC_TESTS(std::false_type, std::true_type,  std::false_type, true);

    RUN_MAP_POC_TESTS(std::true_type,  std::false_type, std::false_type, true);
    RUN_MAP_POC_TESTS(std::false_type, std::false_type, std::false_type, true);

    RUN_MAP_POC_TESTS(std::true_type,  std::true_type,  std::false_type, true);
    RUN_MAP_POC_TESTS(std::true_type,  std::false_type, std::false_type, true);

    RUN_MAP_POC_TESTS(std::false_type, std::true_type,  std::false_type, true);
    RUN_MAP_POC_TESTS(std::false_type, std::false_type, std::false_type, true);
}
