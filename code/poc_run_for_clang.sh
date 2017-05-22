#!/bin/bash

. /usr/local/bin/setenv-for-clang381.sh
which clang++ | tee clang381-poc-report.txt
echo $LD_LIBRARY_PATH | tee -a clang381-poc-report.txt
./alloc381 -c | tee -a clang381-poc-report.txt

. /usr/local/bin/setenv-for-clang391.sh
which clang++ | tee clang391-poc-report.txt
echo $LD_LIBRARY_PATH | tee -a clang391-poc-report.txt
./alloc391 -c | tee -a clang391-poc-report.txt

. /usr/local/bin/setenv-for-clang400.sh
which clang++ | tee clang400-poc-report.txt
echo $LD_LIBRARY_PATH | tee -a clang400-poc-report.txt
./alloc400 -c | tee -a clang400-poc-report.txt
