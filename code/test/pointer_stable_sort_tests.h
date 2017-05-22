//==================================================================================================
//  File:
//      pointer_stable_sort_tests.h
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#ifndef POINTER_STABLE_SORT_TESTS_H_DEFINED
#define POINTER_STABLE_SORT_TESTS_H_DEFINED

#include "pointer_tests.h"

//--------------------------------------------------------------------------------------------------
//  Function:
//      do_pointer_stable_sort_test<AS,DT>
//
//  Summary:
//      This function template measures the time it takes to sort elements in an array.  It
//      measures elapsed time twice: once for the case when the destination is accessed with
//      native pointers, and once for the case when the destination is accessed with synthetic
//      pointers.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy, typename DataType>
timing_pair
do_pointer_stable_sort_test(size_t nelem)
{
    using syn_ptr_void = typename AllocStrategy::void_pointer;
    using syn_ptr_data = typename AllocStrategy::template rebind_pointer<DataType>;

    //- Instantiate a std::vector and fill it with some randomly-generated test data.  Instantiate
    //  a second vector that will contain the sorted version of the first.
    //
    vector<DataType>    random_data(generate_test_data<DataType>(nelem));   //- Random source data
    vector<DataType>    sorted_data(random_data);                           //- Sorted reference data

    sort(begin(sorted_data), end(sorted_data));

    //- Instantiate the allocation strategy object and allocate a buffer of appropriate size using
    //  the pointer types expressed in the strategy's public interface.
    //
    AllocStrategy   heap;
    syn_ptr_void    psyn_void  = heap.allocate(nelem*sizeof(DataType));
    syn_ptr_data    psyn_begin = static_cast<syn_ptr_data >(psyn_void);
    syn_ptr_data    psyn_end   = psyn_begin + nelem;

    //- Initialize the raw storage with dummy values so we can just use copy() below.
    //
    uninitialized_fill(psyn_begin, psyn_end, DataType());

    //- Get a couple of corresponding natural pointers for comparison purposes.
    //
    DataType*   pnat_begin = psyn_begin;
    DataType*   pnat_end   = psyn_end;

    //- Get ready to time the sorts.
    //
    static bool native_first = true;
    stopwatch   sw;
    int64_t     el_nat, el_syn;

    //- We're going to alternate between native operations first and synthetic operations first
    //  in order to avoid any bias in the average due to the order.
    //
    if (native_first)
    {
        //- Copy the random data into the buffer using native pointers and verify its integrity.
        //
        copy(cbegin(random_data), cend(random_data), pnat_begin);

        auto    mm1_copy_nat = mismatch(pnat_begin, pnat_end, cbegin(random_data), cend(random_data));
        CHECK(mm1_copy_nat.first == pnat_end);

        //- Sort the buffer using native pointers as iterators.
        //
        sw.start();
        stable_sort(pnat_begin, pnat_end);
        sw.stop();
        el_nat = sw.elapsed_nsec();

        //- Verify that the newly-sorted buffer matches the sorted reference vector.
        //
        auto    mm1_stable_sort_nat = mismatch(pnat_begin, pnat_end, cbegin(sorted_data), cend(sorted_data));
        CHECK(mm1_stable_sort_nat.first == pnat_end);

        //- Copy the random data into the buffer using synthetic pointers and verify its integrity.
        //
        copy(cbegin(random_data), cend(random_data), psyn_begin);

        auto    mm2_copy_syn = mismatch(psyn_begin, psyn_end, cbegin(random_data), cend(random_data));
        CHECK(mm2_copy_syn.first == psyn_end);
        auto    mm2_copy_nat = mismatch(pnat_begin, pnat_end, cbegin(random_data), cend(random_data));
        CHECK(mm2_copy_nat.first == pnat_end);

        //- Sort the buffer using synthetic pointers as iterators.
        //
        sw.start();
        stable_sort(psyn_begin, psyn_end);
        sw.stop();
        el_syn = sw.elapsed_nsec();

        //- Verify that the newly-sorted buffer matches the sorted reference vector.
        //
        auto    mm2_stable_sort_syn = mismatch(psyn_begin, psyn_end, cbegin(sorted_data), cend(sorted_data));
        CHECK(mm2_stable_sort_syn.first == psyn_end);
        auto    mm2_stable_sort_nat = mismatch(pnat_begin, pnat_end, cbegin(sorted_data), cend(sorted_data));
        CHECK(mm2_stable_sort_nat.first == pnat_end);
    }
    else    //- synthetic first.
    {
        //- Copy the random data into the buffer using synthetic pointers and verify its integrity.
        //
        copy(cbegin(random_data), cend(random_data), psyn_begin);

        auto    mm2_copy_syn = mismatch(psyn_begin, psyn_end, cbegin(random_data), cend(random_data));
        CHECK(mm2_copy_syn.first == psyn_end);
        auto    mm2_copy_nat = mismatch(pnat_begin, pnat_end, cbegin(random_data), cend(random_data));
        CHECK(mm2_copy_nat.first == pnat_end);

        //- Sort the buffer using synthetic pointers as iterators.
        //
        sw.start();
        stable_sort(psyn_begin, psyn_end);
        sw.stop();
        el_syn = sw.elapsed_nsec();

        //- Verify that the newly-sorted buffer matches the sorted reference vector.
        //
        auto    mm2_stable_sort_syn = mismatch(psyn_begin, psyn_end, cbegin(sorted_data), cend(sorted_data));
        CHECK(mm2_stable_sort_syn.first == psyn_end);
        auto    mm2_stable_sort_nat = mismatch(pnat_begin, pnat_end, cbegin(sorted_data), cend(sorted_data));
        CHECK(mm2_stable_sort_nat.first == pnat_end);

        //- Copy the random data into the buffer using native pointers and verify its integrity.
        //
        copy(cbegin(random_data), cend(random_data), pnat_begin);

        auto    mm1_copy_nat = mismatch(pnat_begin, pnat_end, cbegin(random_data), cend(random_data));
        CHECK(mm1_copy_nat.first == pnat_end);

        //- Sort the buffer using native pointers as iterators.
        //
        sw.start();
        sort(pnat_begin, pnat_end);
        sw.stop();
        el_nat = sw.elapsed_nsec();

        //- Verify that the newly-sorted buffer matches the sorted reference vector.
        //
        auto    mm1_stable_sort_nat = mismatch(pnat_begin, pnat_end, cbegin(sorted_data), cend(sorted_data));
        CHECK(mm1_stable_sort_nat.first == pnat_end);
    }

    destroy_range(pnat_begin, pnat_end);
    heap.reset_buffers();
    native_first = !native_first;

    return timing_pair{el_nat, el_syn};
}

//--------------------------------------------------------------------------------------------------
//  Function:
//      run_pointer_stable_sort_test<AS,DT>
//
//  Summary:
//      This function template manages the process of calling do_pointer_stable_sort_test() multiple
//      times, accumulating the timings, and reporting the results.
//--------------------------------------------------------------------------------------------------
//
template<typename AllocStrategy, typename DataType>
void
run_pointer_stable_sort_tests(char const* stype, char const* dtype)
{
    std::ios    old_state(nullptr);
    old_state.copyfmt(std::cout);

    size_t const    stat_repeats = 16;      //- Times to repeat the test.
    size_t const    stat_rejects = 6;       //- Measurements to drop; highest & lowest.

    //- Time the stable sort operation for variously-sized arrays.
    //
    for (size_t i = 0;  i < max_element_index();  ++i)
    {
        size_t          nelem = elem_counts[i];
        timing_pair     timing;
        timing_vector   timings;

        for (size_t j = 0;  j < stat_repeats;  ++j)
        {
            timing = do_pointer_stable_sort_test<AllocStrategy, DataType>(nelem);
            timings.push_back(timing);
        }

        //- Sort the timings vector so we can reject highest/lowest timings.
        //
        sort(begin(timings), end(timings));

        //- Compute the synthetic-to-natural ratio, dropping outliers.
        //
        double      ratio;
        int64_t     el_nat_total = 0;
        int64_t     el_syn_total = 0;

        for (size_t j = 0;  j < timings.size();  ++j)
        {
            el_nat_total += timings[j].m_el_nat;
            el_syn_total += timings[j].m_el_syn;
        }

        el_nat_total = 0;
        el_syn_total = 0;

        for (size_t j = (stat_rejects/2);  j < (timings.size() - stat_rejects);  ++j)
        {
            el_nat_total += timings[j].m_el_nat;
            el_syn_total += timings[j].m_el_syn;
        }

        ratio = (double) el_syn_total / (double) el_nat_total;

        cout << "stable_sort, " << stype << ", " << dtype << ", "
             << showpoint << setw(7) << setprecision((ratio >= 1.0) ? 5 : 4) << ratio << ", "
             << nelem << endl;
        cout.copyfmt(old_state);
    }
    cout << endl;
}

#endif  //- POINTER_STABLE_SORT_TESTS_H_DEFINED
