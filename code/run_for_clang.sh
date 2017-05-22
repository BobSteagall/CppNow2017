#!/bin/bash

runs=99

. /usr/local/bin/setenv-for-clang381.sh
which clang++ | tee clang381-timings-report381.txt
echo $LD_LIBRARY_PATH | tee -a clang381-timings-report.txt
./alloc381 -t -p $runs | tee -a clang381-timings-report.txt

. /usr/local/bin/setenv-for-clang391.sh
which clang++ | tee clang391-timings-report.txt
echo $LD_LIBRARY_PATH | tee -a clang391-timings-report.txt
./alloc391 -t -p $runs | tee -a clang391-timings-report.txt

. /usr/local/bin/setenv-for-clang400.sh
which clang++ | tee clang400-timings-report.txt
echo $LD_LIBRARY_PATH | tee -a clang400-timings-report.txt
./alloc400 -t -p $runs | tee -a clang400-timings-report.txt
