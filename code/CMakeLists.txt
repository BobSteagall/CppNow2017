cmake_minimum_required (VERSION 3.5)
project (AllocatorAware)

include_directories(include)

set(Sources
        include/based_1d_addressing.h
        include/based_1d_storage.h
        include/based_2d_addressing.h
        include/based_2d_storage.h
        include/based_2dxl_addressing.h
        include/based_2dxl_storage.h
        include/leaky_allocation_strategy.h
        include/offset_addressing.h
        include/offset_storage.h
        include/poc_allocator.h
        include/rhx_allocator.h
        include/storage_base.h
        include/synthetic_pointer.h
        include/wrapper_addressing.h
        include/wrapper_storage.h

        src/based_1d_storage.cpp
        src/based_2d_storage.cpp
        src/based_2dxl_storage.cpp
        src/leaky_allocation_strategy.cpp
        src/offset_storage.cpp
        src/storage_base.cpp
        src/wrapper_storage.cpp

        test/common.h
        test/common.cpp
        test/container_deque_tests.h
        test/container_deque_tests.cpp
        test/container_fwdlist_tests.h
        test/container_fwdlist_tests.cpp
        test/container_list_tests.h
        test/container_list_tests.cpp
        test/container_map_tests.h
        test/container_map_tests.cpp
        test/container_tests.cpp
        test/container_tests.h
        test/container_unordered_map_tests.h
        test/container_unordered_map_tests.cpp
        test/container_vector_tests.h
        test/container_vector_tests.cpp
        test/main.cpp
        test/pointer_cast_tests.h
        test/pointer_copy_tests.h
        test/pointer_sort_tests.h
        test/pointer_stable_sort_tests.h
        test/pointer_tests.cpp
        test/pointer_tests.h
        test/stopwatch.h
)

add_executable(alloc ${Sources})

set(CMAKE_VERBOSE_MAKEFILE 1)

if(CXX_COMPILER STREQUAL clang++)
    set(CMAKE_CXX_COMPILER clang++)
elseif(CXX_COMPILER STREQUAL g++)
    set(CMAKE_CXX_COMPILER g++)
else()
    set(CMAKE_CXX_COMPILER g++)
endif()

if(CMAKE_CXX_COMPILER STREQUAL clang++)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++14 -stdlib=libc++ -Wall -pedantic -Wextra")
    set(CMAKE_CXX_FLAGS_RELEASE-CLANG "${CMAKE_CXX_FLAGS_RELEASE-CLANG} -O2 -std=c++14 -stdlib=libc++ -Wall -pedantic -Wextra")
elseif(CMAKE_CXX_COMPILER STREQUAL g++)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -std=c++14 -Wall -pedantic -Wextra")
    set(CMAKE_CXX_FLAGS_RELEASE-GCC "${CMAKE_CXX_FLAGS_RELEASE-GCC} -O2 -std=c++14 -Wall -pedantic -Wextra")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic -Wextra")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pedantic -Wextra")
endif()