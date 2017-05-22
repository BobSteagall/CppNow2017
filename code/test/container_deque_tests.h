//==================================================================================================
//  File:
//      container_deque_tests.h
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#ifndef CONTAINER_DEQUE_TESTS_H_DEFINED
#define CONTAINER_DEQUE_TESTS_H_DEFINED

#include "container_tests.h"

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_simple_deque_test<AS>
//
//  Summary:
//      This function template performs a very simple, sanity-checking test.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
do_simple_deque_test()
{
    //- Various type aliases to aid readability.
    //
    using strategy      = AllocStrategy;
    using syn_string    = test_string<strategy>;
    using syn_str_deque = deque<syn_string, rhx_allocator<syn_string, strategy>>;

    auto    spl = allocate<syn_str_deque, strategy>();
    char    str[256];

    for (int i = 162;  i <= 172;  ++i)
    {
        sprintf(str, "this is very long test string #%d created especially for deque<string>", i);
        spl->push_back(str);
    }

    cout << "*************************" << endl;
    cout << "*****  TEST DEQUE  ******" << endl;

    for (auto e : *spl)
    {
        cout << e << endl;
    }

    cout << endl;
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_normal_deque_tests<AllocStrategy, DataType>
//
//  Summary:
//      This function template performs basic functionality testing (basic/copy/move ops).
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy, typename DataType>
void
do_normal_deque_tests(size_t nelem)
{
    //- Various type aliases to aid readability.
    //
    using strategy       = AllocStrategy;
    using data_traits    = test_data_type_traits<DataType, AllocStrategy>;
    using nat_data_type  = typename data_traits::nat_type;
    using syn_data_type  = typename data_traits::syn_type;
    using nat_deque_type = deque<nat_data_type>;
    using syn_deque_type = deque<syn_data_type, rhx_allocator<syn_data_type, strategy>>;

    //- Some deques.
    //
    nat_deque_type  nat_deque;
    syn_deque_type  syn_deque_1;
    auto            p_syn_deque_A = allocate<syn_deque_type, strategy>();

    //- Basic operations.
    //
    CHECK(contents_match(nat_deque, syn_deque_1));
    CHECK(contents_match(nat_deque, *p_syn_deque_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_data_type   nat_data;
        syn_data_type   syn_data;

        data_traits::generate(nat_data, syn_data);

        nat_deque.push_back(nat_data);
        syn_deque_1.push_back(syn_data);
        p_syn_deque_A->push_back(syn_data);
    }

    CHECK(contents_match(nat_deque, syn_deque_1));
    CHECK(contents_match(nat_deque, *p_syn_deque_A));

    PRINT(nat_deque, syn_deque_1);
    PRINT(nat_deque, *p_syn_deque_A);

    nat_deque.clear();
    syn_deque_1.clear();
    p_syn_deque_A->clear();

    CHECK(contents_match(nat_deque, syn_deque_1));
    CHECK(contents_match(nat_deque, *p_syn_deque_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_data_type   nat_data;
        syn_data_type   syn_data;

        data_traits::generate(nat_data, syn_data);

        nat_deque.push_back(nat_data);
        syn_deque_1.push_back(syn_data);
        p_syn_deque_A->push_back(syn_data);
    }

    CHECK(contents_match(nat_deque, syn_deque_1));
    CHECK(contents_match(nat_deque, *p_syn_deque_A));

    nat_deque.pop_back();
    nat_deque.pop_front();
    syn_deque_1.pop_back();
    syn_deque_1.pop_front();
    p_syn_deque_A->pop_back();
    p_syn_deque_A->pop_front();

    CHECK(contents_match(nat_deque, syn_deque_1));
    CHECK(contents_match(nat_deque, *p_syn_deque_A));

    PRINT(nat_deque, syn_deque_1);
    PRINT(nat_deque, *p_syn_deque_A);

    //- Copy operations.
    //
    syn_deque_type  syn_deque_2(syn_deque_1);
    syn_deque_type  syn_deque_3;

    syn_deque_3 = syn_deque_1;

    CHECK(contents_match(nat_deque, syn_deque_2));
    CHECK(contents_match(nat_deque, syn_deque_3));

    auto    p_syn_deque_B = allocate<syn_deque_type, strategy>(syn_deque_1);
    auto    p_syn_deque_C = allocate<syn_deque_type, strategy>();

    *p_syn_deque_C = syn_deque_1;

    CHECK(contents_match(nat_deque, *p_syn_deque_B));
    CHECK(contents_match(nat_deque, *p_syn_deque_C));

    //- Move operations.
    //
    syn_deque_type  syn_deque_4(std::move(syn_deque_2));
    syn_deque_type  syn_deque_5;

    CHECK(syn_deque_2.size() == 0u);
    CHECK(contents_match(nat_deque, syn_deque_4));

    syn_deque_5 = std::move(syn_deque_3);

    CHECK(syn_deque_3.size() == 0);
    CHECK(contents_match(nat_deque, syn_deque_5));

    auto    p_syn_deque_D = allocate<syn_deque_type, strategy>(std::move(*p_syn_deque_B));
    auto    p_syn_deque_E = allocate<syn_deque_type, strategy>();

    CHECK(p_syn_deque_B->size() == 0u);
    CHECK(contents_match(nat_deque, *p_syn_deque_D));

    *p_syn_deque_E = std::move(*p_syn_deque_C);

    CHECK(p_syn_deque_C->size() == 0);
    CHECK(contents_match(nat_deque, *p_syn_deque_E));
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_deque_normal_tests<AllocStrategy>
//
//  Summary:
//      This function template manages the sequence of actual deque test function calls.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
run_deque_normal_tests(char const* stype)
{
    cout << "================================================================" << endl;
    cout << "Running basic operation tests for " << stype << endl;
    cout << "Using container std::deque" << endl;

    do_simple_deque_test<AllocStrategy>();

    do_normal_deque_tests<AllocStrategy, test_struct>(10);

    if (verbose_output())
    {
        cout << "------------------------------------------------" << endl << endl;
    }

    do_normal_deque_tests<AllocStrategy, string>(10);

    AllocStrategy::reset_buffers();
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_reloc_deque_tests<AllocStrategy, DataType>
//
//  Summary:
//      This function template performs basic functionality testing (basic/copy/move ops).
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy, typename DataType>
void
do_reloc_deque_tests(size_t nelem)
{
    //- Various type aliases to aid readability.
    //
    using strategy       = AllocStrategy;
    using data_traits    = test_data_type_traits<DataType, AllocStrategy>;
    using nat_data_type  = typename data_traits::nat_type;
    using syn_data_type  = typename data_traits::syn_type;
    using nat_deque_type = deque<nat_data_type>;
    using syn_deque_type = deque<syn_data_type, rhx_allocator<syn_data_type, strategy>>;

    //- Some deques.
    //
    nat_deque_type  nat_deque;
    auto            p_syn_deque_A = allocate<syn_deque_type, strategy>();

    //- Basic operations.
    //
    CHECK(contents_match(nat_deque, *p_syn_deque_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_data_type   nat_data;
        syn_data_type   syn_data;

        data_traits::generate(nat_data, syn_data);

        nat_deque.push_back(nat_data);
        p_syn_deque_A->push_back(syn_data);
    }

    CHECK(contents_match(nat_deque, *p_syn_deque_A));
    PRINT(nat_deque, *p_syn_deque_A);

    auto    pc_1 = addressof(*p_syn_deque_A);
    auto    pe_1 = addressof(p_syn_deque_A->front());

    strategy::swap_buffers();

    auto    pc_2 = addressof(*p_syn_deque_A);
    auto    pe_2 = addressof(p_syn_deque_A->front());

    CHECK(pc_1 != pc_2);
    CHECK(pe_1 != pe_2);
    CHECK(contents_match(nat_deque, *p_syn_deque_A));
    PRINT(nat_deque, *p_syn_deque_A);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_deque_reloc_tests<AllocStrategy>
//
//  Summary:
//      This function template manages the sequence of actual deque test function calls.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
run_deque_reloc_tests(char const* stype)
{
    cout << "================================================================" << endl;
    cout << "Running relocation tests for " << stype << endl;
    cout << "Using container std::deque" << endl << endl;

    do_reloc_deque_tests<AllocStrategy, test_struct>(10);

    if (verbose_output())
    {
        cout << "------------------------------------------------" << endl << endl;
    }

    do_reloc_deque_tests<AllocStrategy, string>(10);

    AllocStrategy::reset_buffers();
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_deque_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template does simple deque POC* testing, using natural pointers.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
do_deque_poc_tests()
{
    using test_alloc = poc_allocator<test_struct, POCCA, POCMA, POCS, EQ>;
    using test_deque = deque<test_struct, test_alloc>;

    test_deque      d1;
    size_t const    start_count = 10;

    for (size_t i = 0;  i < start_count; ++i)
    {
        test_struct     ts = generate_test_struct();
        d1.push_back(ts);
    }

    test_deque  d0(d1), d2(d1);
    test_deque  d3(std::move(d1));
    test_deque  d4(d1), d5(d1);

    CHECK(d1.size() == 0);
    CHECK(d2.size() == start_count);
    CHECK(d3.size() == start_count);
    CHECK(d2 == d3);

    d3.pop_back();
    d3.pop_back();
    CHECK(d3.size() == (start_count - 2));

    d4 = d3;
    d5 = std::move(d3);
    CHECK(d4 == d5);

    swap(d2, d5);
    CHECK(d2 == d4);
    CHECK(d5 == d0);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_deque_syn_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template does simple deque POC* testing, using synthetic pointers.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
do_deque_syn_poc_tests()
{
    using test_alloc = syn_poc_allocator<test_struct, POCCA, POCMA, POCS, EQ>;
    using test_deque = deque<test_struct, test_alloc>;

    test_deque       d1;
    size_t const    start_count = 10;

    for (size_t i = 0;  i < start_count; ++i)
    {
        test_struct     ts = generate_test_struct();
        d1.push_back(ts);
    }

    test_deque  d0(d1), d2(d1);
    test_deque  d3(std::move(d1));
    test_deque  d4(d1), d5(d1);

    CHECK(d1.size() == 0);
    CHECK(d2 == d3);

    d3.pop_back();
    d3.pop_back();

    d4 = d3;
    d5 = std::move(d3);
    CHECK(d4 == d5);

    swap(d2, d5);
    CHECK(d2 == d4);
    CHECK(d5 == d0);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_deque_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template manages the sequence of actual deque POC* test function calls.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
run_deque_poc_tests()
{
    cout << "Running POC tests for native pointer" << endl;
    do_deque_poc_tests<POCCA,POCMA,POCS,EQ>();
    cout << "Running POC tests for synthetic pointer" << endl;
    do_deque_syn_poc_tests<POCCA,POCMA,POCS,EQ>();
}

#endif  //- CONTAINER_DEQUE_TESTS_H_DEFINED
