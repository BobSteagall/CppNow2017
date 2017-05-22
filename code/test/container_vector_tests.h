//==================================================================================================
//  File:
//      container_vector_tests.h
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#ifndef CONTAINER_VECTOR_TESTS_H_DEFINED
#define CONTAINER_VECTOR_TESTS_H_DEFINED

#include "container_tests.h"

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_simple_vector_test<AS>
//
//  Summary:
//      This function template performs a very simple, sanity-checking test.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
do_simple_vector_test()
{
    //- Various type aliases to aid readability.
    //
    using strategy       = AllocStrategy;
    using syn_string     = test_string<strategy>;
    using syn_str_vector = vector<syn_string, rhx_allocator<syn_string, strategy>>;

    auto    spl = allocate<syn_str_vector, strategy>();
    char    str[256];

    for (int i = 1729;  i <= 1739;  ++i)
    {
        sprintf(str, "this is very long test string #%d created especially for vector<string>", i);
        spl->push_back(str);
    }

    cout << "**************************" << endl;
    cout << "*****  TEST VECTOR  ******" << endl;

    for (auto e : *spl)
    {
        cout << e << endl;
    }

    cout << endl;
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_normal_vector_tests<AllocStrategy, DataType>
//
//  Summary:
//      This function template performs basic functionality testing (basic/copy/move ops).
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy, typename DataType>
void
do_normal_vector_tests(size_t nelem)
{
    //- Various type aliases to aid readability.
    //
    using strategy        = AllocStrategy;
    using data_traits     = test_data_type_traits<DataType, AllocStrategy>;
    using nat_data_type   = typename data_traits::nat_type;
    using syn_data_type   = typename data_traits::syn_type;
    using nat_vector_type = vector<nat_data_type>;
    using syn_vector_type = vector<syn_data_type, rhx_allocator<syn_data_type, strategy>>;

    //- Some vectors.
    //
    nat_vector_type     nat_vector;
    syn_vector_type     syn_vector_1;
    auto                p_syn_vector_A = allocate<syn_vector_type, strategy>();

    //- Basic operations.
    //
    CHECK(contents_match(nat_vector, syn_vector_1));
    CHECK(contents_match(nat_vector, *p_syn_vector_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_data_type   nat_data;
        syn_data_type   syn_data;

        data_traits::generate(nat_data, syn_data);

        nat_vector.push_back(nat_data);
        syn_vector_1.push_back(syn_data);
        p_syn_vector_A->push_back(syn_data);
    }

    CHECK(contents_match(nat_vector, syn_vector_1));
    CHECK(contents_match(nat_vector, *p_syn_vector_A));

    PRINT(nat_vector, syn_vector_1);
    PRINT(nat_vector, *p_syn_vector_A);

    nat_vector.clear();
    syn_vector_1.clear();
    p_syn_vector_A->clear();

    CHECK(contents_match(nat_vector, syn_vector_1));
    CHECK(contents_match(nat_vector, *p_syn_vector_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_data_type   nat_data;
        syn_data_type   syn_data;

        data_traits::generate(nat_data, syn_data);

        nat_vector.push_back(nat_data);
        syn_vector_1.push_back(syn_data);
        p_syn_vector_A->push_back(syn_data);
    }

    CHECK(contents_match(nat_vector, syn_vector_1));
    CHECK(contents_match(nat_vector, *p_syn_vector_A));

    nat_vector.pop_back();
    syn_vector_1.pop_back();
    p_syn_vector_A->pop_back();

    CHECK(contents_match(nat_vector, syn_vector_1));
    CHECK(contents_match(nat_vector, *p_syn_vector_A));

    PRINT(nat_vector, syn_vector_1);
    PRINT(nat_vector, *p_syn_vector_A);

    //- Copy operations.
    //
    syn_vector_type     syn_vector_2(syn_vector_1);
    syn_vector_type     syn_vector_3;

    syn_vector_3 = syn_vector_1;

    CHECK(contents_match(nat_vector, syn_vector_2));
    CHECK(contents_match(nat_vector, syn_vector_3));

    auto    p_syn_vector_B = allocate<syn_vector_type, strategy>(syn_vector_1);
    auto    p_syn_vector_C = allocate<syn_vector_type, strategy>();

    *p_syn_vector_C = syn_vector_1;

    CHECK(contents_match(nat_vector, *p_syn_vector_B));
    CHECK(contents_match(nat_vector, *p_syn_vector_C));

    //- Move operations.
    //
    syn_vector_type   syn_vector_4(std::move(syn_vector_2));
    syn_vector_type   syn_vector_5;

    CHECK(syn_vector_2.size() == 0u);
    CHECK(contents_match(nat_vector, syn_vector_4));

    syn_vector_5 = std::move(syn_vector_3);

    CHECK(syn_vector_3.size() == 0);
    CHECK(contents_match(nat_vector, syn_vector_5));

    auto    p_syn_vector_D = allocate<syn_vector_type, strategy>(std::move(*p_syn_vector_B));
    auto    p_syn_vector_E = allocate<syn_vector_type, strategy>();

    CHECK(p_syn_vector_B->size() == 0u);
    CHECK(contents_match(nat_vector, *p_syn_vector_D));

    *p_syn_vector_E = std::move(*p_syn_vector_C);

    CHECK(p_syn_vector_C->size() == 0);
    CHECK(contents_match(nat_vector, *p_syn_vector_E));
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_vector_normal_tests<AllocStrategy>
//
//  Summary:
//      This function template manages the sequence of actual vector test function calls.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
run_vector_normal_tests(char const* stype)
{
    cout << "================================================================" << endl;
    cout << "Running basic operation tests for " << stype << endl;
    cout << "Using container std::vector" << endl;

    do_simple_vector_test<AllocStrategy>();

    do_normal_vector_tests<AllocStrategy, test_struct>(10);

    if (verbose_output())
    {
        cout << "------------------------------------------------" << endl << endl;
    }

    do_normal_vector_tests<AllocStrategy, string>(10);

    AllocStrategy::reset_buffers();
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_reloc_vector_tests<AllocStrategy, DataType>
//
//  Summary:
//      This function template performs basic functionality testing (basic/copy/move ops).
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy, typename DataType>
void
do_reloc_vector_tests(size_t nelem)
{
    //- Various type aliases to aid readability.
    //
    using strategy        = AllocStrategy;
    using data_traits     = test_data_type_traits<DataType, AllocStrategy>;
    using nat_data_type   = typename data_traits::nat_type;
    using syn_data_type   = typename data_traits::syn_type;
    using nat_vector_type = vector<nat_data_type>;
    using syn_vector_type = vector<syn_data_type, rhx_allocator<syn_data_type, strategy>>;

    //- Some vectors.
    //
    nat_vector_type     nat_vector;
    auto                p_syn_vector_A = allocate<syn_vector_type, strategy>();

    //- Basic operations.
    //
    CHECK(contents_match(nat_vector, *p_syn_vector_A));

    for (size_t i = 0;  i < nelem;  ++i)
    {
        nat_data_type   nat_data;
        syn_data_type   syn_data;

        data_traits::generate(nat_data, syn_data);

        nat_vector.push_back(nat_data);
        p_syn_vector_A->push_back(syn_data);
    }

    CHECK(contents_match(nat_vector, *p_syn_vector_A));
    PRINT(nat_vector, *p_syn_vector_A);

    auto    pc_1 = addressof(*p_syn_vector_A);
    auto    pe_1 = addressof(p_syn_vector_A->front());

    strategy::swap_buffers();

    auto    pc_2 = addressof(*p_syn_vector_A);
    auto    pe_2 = addressof(p_syn_vector_A->front());

    CHECK(pc_1 != pc_2);
    CHECK(pe_1 != pe_2);
    CHECK(contents_match(nat_vector, *p_syn_vector_A));
    PRINT(nat_vector, *p_syn_vector_A);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_vector_reloc_tests<AllocStrategy>
//
//  Summary:
//      This function template manages the sequence of actual vector test function calls.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy>
void
run_vector_reloc_tests(char const* stype)
{
    cout << "================================================================" << endl;
    cout << "Running relocation tests for " << stype << endl;
    cout << "Using container std::vector" << endl << endl;

    do_reloc_vector_tests<AllocStrategy, test_struct>(10);

    if (verbose_output())
    {
        cout << "------------------------------------------------" << endl << endl;
    }

    do_reloc_vector_tests<AllocStrategy, string>(10);

    AllocStrategy::reset_buffers();
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_vector_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template does simple vector POC* testing, using natural pointers.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
do_vector_poc_tests()
{
    using test_alloc  = poc_allocator<test_struct, POCCA, POCMA, POCS, EQ>;
    using test_vector = vector<test_struct, test_alloc>;

    test_vector     v1;
    size_t const    start_count = 10;

    for (size_t i = 0;  i < start_count; ++i)
    {
        test_struct     ts = generate_test_struct();
        v1.push_back(ts);
    }

    test_vector     v0(v1), v2(v1);
    test_vector     v3(std::move(v1));
    test_vector     v4(v1), v5(v1);

    CHECK(v1.size() == 0);
    CHECK(v2.size() == start_count);
    CHECK(v3.size() == start_count);
    CHECK(v2 == v3);

    v3.pop_back();
    v3.pop_back();
    CHECK(v3.size() == (start_count - 2));

    v4 = v3;
    v5 = std::move(v3);
    CHECK(v4 == v5);

    swap(v2, v5);
    CHECK(v2 == v4);
    CHECK(v5 == v0);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_vector_syn_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template does simple vector POC* testing, using synthetic pointers.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
do_vector_syn_poc_tests()
{
    using test_alloc  = syn_poc_allocator<test_struct, POCCA, POCMA, POCS, EQ>;
    using test_vector = vector<test_struct, test_alloc>;

    test_vector     v1;
    size_t const    start_count = 10;

    for (size_t i = 0;  i < start_count; ++i)
    {
        test_struct     ts = generate_test_struct();
        v1.push_back(ts);
    }

    test_vector     v0(v1), v2(v1);
    test_vector     v3(std::move(v1));
    test_vector     v4(v1), v5(v1);

    CHECK(v1.size() == 0);
    CHECK(v2 == v3);

    v3.pop_back();
    v3.pop_back();

    v4 = v3;
    v5 = std::move(v3);
    CHECK(v4 == v5);

    swap(v2, v5);
    CHECK(v2 == v4);
    CHECK(v5 == v0);
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_vector_poc_tests<class POCCA, class POCMA, class POCS, bool EQ>
//
//  Summary:
//      This function template manages the sequence of actual vector POC* test function calls.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
void
run_vector_poc_tests()
{
    cout << "Running POC tests for native pointer" << endl;
    do_vector_poc_tests<POCCA,POCMA,POCS,EQ>();
    cout << "Running POC tests for synthetic pointer" << endl;
    do_vector_syn_poc_tests<POCCA,POCMA,POCS,EQ>();
}

#endif  //- CONTAINER_VECTOR_TESTS_H_DEFINED
