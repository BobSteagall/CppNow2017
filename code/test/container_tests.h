//==================================================================================================
//  File:
//      container_tests.h
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#ifndef CONTAINER_TESTS_H_DEFINED
#define CONTAINER_TESTS_H_DEFINED

#include "common.h"

//- These are some utilities for working with string types that employ synthetic pointers.
//
template<class AS> using test_string = basic_string<char, char_traits<char>, rhx_allocator<char, AS>>;

template<typename AS>
inline ostream&
operator <<(ostream& os, test_string<AS> const& str)
{
    os << str.data();
    return os;
}

template<typename AS>
inline bool
operator ==(string const& lhs, test_string<AS> const& rhs)
{
    return (lhs.size() == rhs.size()) && (memcmp(lhs.data(), rhs.data(), lhs.size()) == 0);
}

//- Determine whether or not two sequences have the same length, by directly measuring the lengths_match.
//  This test will never allocate more than 1,000,000 elements, so if the distance gets to 2,000,000, then
//  we know there's a problem.
//
template<typename C1, typename C2>
bool
lengths_match(C1 const& c1, C2 const& c2)
{
    ptrdiff_t   c1_dst = 0;
    auto        c1_itr = cbegin(c1);
    auto        c1_end = cend(c1);

    for (;  c1_itr != c1_end;  ++c1_itr, ++c1_dst)
    {
        if (c1_dst == 2000000) return false;
    }

    ptrdiff_t   c2_dst = 0;
    auto        c2_itr = cbegin(c2);
    auto        c2_end = cend(c2);

    for (;  c2_itr != c2_end;  ++c2_itr, ++c2_dst)
    {
        if (c2_dst == 2000000) return false;
    }

    return c1_dst == c2_dst;
}

//- Determine whether or not the contents of two sequences contents_match.
//
template<typename C1, typename C2>
bool
contents_match(C1 const& c1, C2 const& c2)
{
    if (lengths_match(c1, c2))
    {
        auto    mm     = mismatch(cbegin(c1), cend(c1), cbegin(c2), cend(c2));
        auto    c1_res = mm.first;
        auto    c1_end = cend(c1);
        auto    c2_res = mm.second;
        auto    c2_end = cend(c2);

        return (c1_res == c1_end) && (c2_res == c2_end);
    }
    else
    {
        return false;
    }
}

//- Print out the contents of two sequences.
//
template<typename C1, typename C2>
void
print_sequences(C1 const& c1, C2 const& c2)
{
    ptrdiff_t   dist = min(distance(cbegin(c1), cend(c1)), distance(cbegin(c2), cend(c2)));
    auto        it1  = cbegin(c1);
    auto        it2  = cbegin(c2);

    for (ptrdiff_t i = 0;  i < dist;  ++i, ++it1, ++it2)
    {
        cout << "(NAT) " << *it1 << endl;
        cout << "(SYN) " << *it2 << endl;
    }
    cout << endl;
}

//--------------------------------------------------------------------------------------------------
//  struct:
//      test_data_type_traits<DataType, AllocStrategy>
//
//  Summary:
//      This simple traits class defines natural and synthetic element data types and a means of
//      generating some test data.  It really only exists to provide the partial specialization
//      for the std::string data type.
//--------------------------------------------------------------------------------------------------
//
template<typename DT, typename AS>
struct test_data_type_traits
{
    using nat_type = DT;
    using syn_type = nat_type;

    static  void    generate(nat_type& nat, syn_type& syn);
};

template<typename DT, typename AS>
void
test_data_type_traits<DT,AS>::generate(nat_type& nat, syn_type& syn)
{
    nat = generate_data<DT>();
    syn = nat;
}

//- Partial specialization to handle case of std::string.
//
template<typename AS>
struct test_data_type_traits<string, test_string<AS>>
{
    using nat_type = string;
    using syn_type = test_string<AS>;

    static  void    generate(nat_type& nat, syn_type& syn);
};

template<typename AS>
void
test_data_type_traits<string,test_string<AS>>::generate(nat_type& nat, syn_type& syn)
{
    nat = generate_data<string>();
    syn.assign(nat.data(), nat.size());
}

#endif  //- CONTAINER_TESTS_H_DEFINED
