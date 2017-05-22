#!/bin/bash

runs=99

. /usr/local/bin/setenv-for-gcc540.sh
which g++ | tee gcc540-poc-report.txt
echo $LD_LIBRARY_PATH | tee -a gcc540-poc-report.txt
./alloc540 -c | tee -a gcc540-poc-report.txt

. /usr/local/bin/setenv-for-gcc630.sh
which g++ | tee gcc630-poc-report.txt
echo $LD_LIBRARY_PATH | tee -a gcc630-poc-report.txt
./alloc630 -c | tee -a gcc630-poc-report.txt

. /usr/local/bin/setenv-for-gcc710.sh
which g++ | tee gcc710-poc-report.txt
echo $LD_LIBRARY_PATH | tee -a gcc710-poc-report.txt
./alloc710 -c | tee -a gcc710-poc-report.txt
