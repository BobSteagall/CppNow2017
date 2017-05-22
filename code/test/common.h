//==================================================================================================
//  File:
//      common.h
//
//  Summary:
//      Defines services that generate data for testing.
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#ifndef COMMON_H_DEFINED
#define COMMON_H_DEFINED

//- Disable compilation noise from Windows before including any headers.
//
#ifdef _WIN32
#pragma warning (disable: 4100 4101 4189 4390 4494 4503 4661 4996)
#endif

#include <cstdint>
#include <cstring>

#include <algorithm>
#include <deque>
#include <forward_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "stopwatch.h"
#include "based_1d_storage.h"
#include "based_2d_storage.h"
#include "based_2dxl_storage.h"
#include "offset_storage.h"
#include "wrapper_storage.h"
#include "leaky_allocation_strategy.h"
#include "rhx_allocator.h"
#include "poc_allocator.h"

#undef max
#undef min

//- Compiler ID.
//
#if defined(__GNUG__) && !defined(__clang__)
    #define COMPILER_GCC
#elif defined(__clang__)
    #define COMPILER_CLANG
#elif defined(_WIN32)
    #define COMPILER_MS
#endif

//- Function signature string.
//
#ifdef _WIN32
    #define FNSIG __FUNCSIG__
#else
    #define FNSIG __PRETTY_FUNCTION__
#endif

//- Very simple assertions.
//
#undef  CHECK
#define CHECK(EXPR) \
     ((void)((EXPR) ? cout : cout << "FAILURE: in file: " << __FILE__ << " at line " << __LINE__ << \
                             "\n in function: " << FNSIG << endl))

//- Printing.
//
#define PRINT(C1, C2)   if (verbose_output()) print_sequences(C1, C2)


using namespace std;        //- Yes, I know it's bad, but...

using wrapper_strategy    = leaky_allocation_strategy<wrapper_storage_model>;
using based_2d_strategy   = leaky_allocation_strategy<based_2d_storage_model>;
using based_2dxl_strategy = leaky_allocation_strategy<based_2dxl_storage_model>;
using based_1d_strategy   = leaky_allocation_strategy<based_1d_storage_model>;
using offset_strategy     = leaky_allocation_strategy<offset_storage_model>;

bool    verbose_output();
size_t  max_ptr_op_count_index();


template<typename T, size_t N>
inline constexpr size_t array_size(T (&)[N]) { return N; }


struct test_struct
{
    uint64_t    m1;
    uint64_t    m2;
    char        m3[48];

    test_struct() { memset(this, 0, sizeof(test_struct)); m1 = m2 = 999; }
    test_struct(test_struct const& other) { memcpy(this, &other, sizeof(test_struct)); m1 = other.m1; }
};

inline bool
operator ==(test_struct const& lhs, test_struct const& rhs)
{
    return memcmp(&lhs, &rhs, sizeof(test_struct)) == 0;
}

inline bool
operator !=(test_struct const& lhs, test_struct const& rhs)
{
    return memcmp(&lhs, &rhs, sizeof(test_struct)) != 0;
}

inline bool
operator <(test_struct const& lhs, test_struct const& rhs)
{
    return memcmp(&lhs, &rhs, sizeof(test_struct)) < 0;
}

inline std::ostream&
operator <<(std::ostream& os, test_struct const& ts)
{
    os << "[" << ts.m1 << ",  " << ts.m2 << ",  '" << ts.m3 << "']";
    return os;
}

template<typename T, typename U>
inline std::ostream&
operator <<(std::ostream& os, std::pair<T,U> const& p)
{
    os << "{ " << p.first << ", " << p.second << " }";
    return os;
}

struct timing_pair
{
    int64_t     m_el_nat;
    int64_t     m_el_syn;

    int64_t     diff() const;
};

inline int64_t
timing_pair::diff() const
{
    return m_el_syn - m_el_nat;
}

inline bool
operator <(timing_pair const& lhs, timing_pair const& rhs)
{
    return lhs.diff() < rhs.diff();
}

using timing_vector = std::vector<timing_pair>;


std::string     generate_test_string(size_t max_size);
std::string     generate_test_string();
test_struct     generate_test_struct();

template<typename T>
T   generate_data();

template<typename T>
std::vector<T>  generate_test_data(size_t num_elements);

template<typename IT>
void
destroy_range(IT first, IT last)
{
    using value_type = typename std::iterator_traits<IT>::value_type;

    for (;  first != last;  ++first)
    {
        first->~value_type();
    }
}

#endif  //- COMMON_H_DEFINED
