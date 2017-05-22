//==================================================================================================
//  File:
//      container_list_tests.h
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#ifndef CONTAINER_LIST_TESTS_H_DEFINED
#define CONTAINER_LIST_TESTS_H_DEFINED

#include "container_tests.h"

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_simple_list_test<AS>
//
//  Summary:
//      This function template performs a very simple, sanity-checking test.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
do_simple_list_test()
{
    //- Various type aliases to aid readability.
    //
    using strategy     = AllocStrategy;
    using syn_string   = test_string<strategy>;
    using syn_str_list = list<syn_string, rhx_allocator<syn_string, strategy>>;

    auto    spl = allocate<syn_str_list, strategy>();
    char    str[256];

    for (int i = 107;  i <= 117;  ++i)
    {
        sprintf(str, "this is very long test string #%d created especially for list<string>", i);
        spl->push_back(str);
    }

    cout << "************************" << endl;
    cout << "*****  TEST LIST  ******" << endl;

    for (auto e : *spl)
    {
        cout << e << endl;
    }

    cout << endl;
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_normal_list_tests<AllocStrategy, DataType>
//
//  Summary:
//      This function template performs basic functionality testing (basic/copy/move ops).
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy, typename DataType>
void
do_normal_list_tests(size_t nelem)
{
    //- Various type aliases to aid readability.
    //
    using strategy      = AllocStrategy;
    using data_traits   = test_data_type_traits<DataType, AllocStrategy>;
    using nat_data_type = typename data_traits::nat_type;
    using syn_data_type = typename data_traits::syn_type;
    using nat_list_type = list<nat_data_type>;
    using syn_list_type = list<syn_data_type, rhx_allocator<syn_data_type, strategy>>;

    //- Some lists.
    //
    nat_list_type   nat_list;
    syn_list_type   syn_list_1;
    auto            p_syn_list_A = allocate<syn_list_type, strategy>();

    //- Basic operations.
    //
    CHECK(contents_match(nat_list, syn_list_1));
    CHECK(contents_match(nat_list, *p_syn_list_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_data_type   nat_data;
        syn_data_type   syn_data;

        data_traits::generate(nat_data, syn_data);

        nat_list.push_back(nat_data);
        syn_list_1.push_back(syn_data);
        p_syn_list_A->push_back(syn_data);
    }

    CHECK(contents_match(nat_list, syn_list_1));
    CHECK(contents_match(nat_list, *p_syn_list_A));

    PRINT(nat_list, syn_list_1);
    PRINT(nat_list, *p_syn_list_A);

    nat_list.clear();
    syn_list_1.clear();
    p_syn_list_A->clear();

    CHECK(contents_match(nat_list, syn_list_1));
    CHECK(contents_match(nat_list, *p_syn_list_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_data_type   nat_data;
        syn_data_type   syn_data;

        data_traits::generate(nat_data, syn_data);

        nat_list.push_back(nat_data);
        syn_list_1.push_back(syn_data);
        p_syn_list_A->push_back(syn_data);
    }

    CHECK(contents_match(nat_list, syn_list_1));
    CHECK(contents_match(nat_list, *p_syn_list_A));

    nat_list.pop_back();
    nat_list.pop_front();
    syn_list_1.pop_back();
    syn_list_1.pop_front();
    p_syn_list_A->pop_back();
    p_syn_list_A->pop_front();

    CHECK(contents_match(nat_list, syn_list_1));
    CHECK(contents_match(nat_list, *p_syn_list_A));

    PRINT(nat_list, syn_list_1);
    PRINT(nat_list, *p_syn_list_A);

    //- Copy operations.
    //
    syn_list_type   syn_list_2(syn_list_1);
    syn_list_type   syn_list_3;

    syn_list_3 = syn_list_1;

    CHECK(contents_match(nat_list, syn_list_2));
    CHECK(contents_match(nat_list, syn_list_3));

    auto    p_syn_list_B = allocate<syn_list_type, strategy>(syn_list_1);
    auto    p_syn_list_C = allocate<syn_list_type, strategy>();

    *p_syn_list_C = syn_list_1;

    CHECK(contents_match(nat_list, *p_syn_list_B));
    CHECK(contents_match(nat_list, *p_syn_list_C));

    //- Move operations.
    //
    syn_list_type   syn_list_4(std::move(syn_list_2));
    syn_list_type   syn_list_5;

    CHECK(syn_list_2.size() == 0u);
    CHECK(contents_match(nat_list, syn_list_4));

    syn_list_5 = std::move(syn_list_3);

    CHECK(syn_list_3.size() == 0);
    CHECK(contents_match(nat_list, syn_list_5));

    auto    p_syn_list_D = allocate<syn_list_type, strategy>(std::move(*p_syn_list_B));
    auto    p_syn_list_E = allocate<syn_list_type, strategy>();

    CHECK(p_syn_list_B->size() == 0u);
    CHECK(contents_match(nat_list, *p_syn_list_D));

    *p_syn_list_E = std::move(*p_syn_list_C);

    CHECK(p_syn_list_C->size() == 0);
    CHECK(contents_match(nat_list, *p_syn_list_E));
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_list_normal_tests<AllocStrategy>
//
//  Summary:
//      This function template manages the sequence of actual list test function calls.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
run_list_normal_tests(char const* stype) {
    cout << "================================================================" << endl;
    cout << "Running basic operation tests for " << stype << endl;
    cout << "Using container std::list" << endl;

    do_simple_list_test<AllocStrategy>();

    do_normal_list_tests<AllocStrategy, test_struct>(10);

    if (verbose_output())
    {
        cout << "------------------------------------------------" << endl << endl;
    }

    do_normal_list_tests<AllocStrategy, string>(10);

    cout << "Done." << endl;
    AllocStrategy::reset_buffers();
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_reloc_list_tests<AllocStrategy, DataType>
//
//  Summary:
//      This function template performs basic functionality testing (basic/copy/move ops).
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy, typename DataType>
void
do_reloc_list_tests(size_t nelem)
{
    //- Various type aliases to aid readability.
    //
    using strategy      = AllocStrategy;
    using data_traits   = test_data_type_traits<DataType, AllocStrategy>;
    using nat_data_type = typename data_traits::nat_type;
    using syn_data_type = typename data_traits::syn_type;
    using nat_list_type = list<nat_data_type>;
    using syn_list_type = list<syn_data_type, rhx_allocator<syn_data_type, strategy>>;

    //- Some lists.
    //
    nat_list_type   nat_list;
    auto            p_syn_list_A = allocate<syn_list_type, strategy>();

    //- Basic operations.
    //
    CHECK(contents_match(nat_list, *p_syn_list_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_data_type   nat_data;
        syn_data_type   syn_data;

        data_traits::generate(nat_data, syn_data);

        nat_list.push_back(nat_data);
        p_syn_list_A->push_back(syn_data);
    }

    CHECK(contents_match(nat_list, *p_syn_list_A));
    PRINT(nat_list, *p_syn_list_A);

    auto    pc_1 = addressof(*p_syn_list_A);
    auto    pe_1 = addressof(p_syn_list_A->front());

    strategy::swap_buffers();

    auto    pc_2 = addressof(*p_syn_list_A);
    auto    pe_2 = addressof(p_syn_list_A->front());

    CHECK(pc_1 != pc_2);
    CHECK(pe_1 != pe_2);
    CHECK(contents_match(nat_list, *p_syn_list_A));
    PRINT(nat_list, *p_syn_list_A);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_list_reloc_tests<AllocStrategy>
//
//  Summary:
//      This function template manages the sequence of actual list test function calls.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
run_list_reloc_tests(char const* stype)
{
    cout << "================================================================" << endl;
    cout << "Running relocation tests for " << stype << endl;
    cout << "Using container std::list" << endl << endl;

    do_reloc_list_tests<AllocStrategy, test_struct>(10);

    if (verbose_output())
    {
        cout << "------------------------------------------------" << endl << endl;
    }

    do_reloc_list_tests<AllocStrategy, string>(10);

    cout << "Done." << endl;
    AllocStrategy::reset_buffers();
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_list_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template does list deque POC* testing, using natural pointers.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
do_list_poc_tests()
{
    using test_alloc = poc_allocator<test_struct, POCCA, POCMA, POCS, EQ>;
    using test_list  = list<test_struct, test_alloc>;

    test_list       l1;
    size_t const    start_count = 10;

    for (size_t i = 0;  i < start_count; ++i)
    {
        test_struct     ts = generate_test_struct();
        l1.push_back(ts);
    }

    test_list   l0(l1), l2(l1);
    test_list   l3(std::move(l1));
    test_list   l4(l1), l5(l1);

    CHECK(l1.size() == 0);
    CHECK(l2.size() == start_count);
    CHECK(l3.size() == start_count);
    CHECK(l2 == l3);

    l3.pop_back();
    l3.pop_back();
    CHECK(l3.size() == (start_count - 2));

    l4 = l3;
    l5 = std::move(l3);
    CHECK(l4 == l5);

    swap(l2, l5);
    CHECK(l2 == l4);
    CHECK(l5 == l0);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_list_syn_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template does simple list POC* testing, using synthetic pointers.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
do_list_syn_poc_tests()
{
    using test_alloc = syn_poc_allocator<test_struct, POCCA, POCMA, POCS, EQ>;
    using test_list  = list<test_struct, test_alloc>;

    test_list       l1;
    size_t const    start_count = 10;

    for (size_t i = 0;  i < start_count; ++i)
    {
        test_struct     ts = generate_test_struct();
        l1.push_back(ts);
    }

    test_list   l0(l1), l2(l1);
    test_list   l3(std::move(l1));
    test_list   l4(l1), l5(l1);

    CHECK(l1.size() == 0);
    CHECK(l2 == l3);

    l3.pop_back();
    l3.pop_back();

    l4 = l3;
    l5 = std::move(l3);
    CHECK(l4 == l5);

    swap(l2, l5);
    CHECK(l2 == l4);
    CHECK(l5 == l0);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_list_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template manages the sequence of actual list POC* test function calls.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
run_list_poc_tests()
{
    cout << "Running POC tests for native pointer" << endl;
    do_list_poc_tests<POCCA,POCMA,POCS,EQ>();

#ifndef COMPILER_MS
    cout << "Running POC tests for synthetic pointer" << endl;
    do_list_syn_poc_tests<POCCA,POCMA,POCS,EQ>();
#endif

#if defined(COMPILER_MS) && (_MSC_VER > 1900)
    cout << "Running POC tests for synthetic pointer" << endl;
    do_list_syn_poc_tests<POCCA,POCMA,POCS,EQ>();
#endif
}

#endif  //- CONTAINER_LIST_TESTS_H_DEFINED
