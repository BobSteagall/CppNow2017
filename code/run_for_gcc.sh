#!/bin/bash

runs=99

. /usr/local/bin/setenv-for-gcc540.sh
which g++ | tee gcc540-timings-report.txt
echo $LD_LIBRARY_PATH | tee -a gcc540-timings-report.txt
./alloc540 -t -p $runs | tee -a gcc540-timings-report.txt

. /usr/local/bin/setenv-for-gcc630.sh
which g++ | tee gcc630-timings-report.txt
echo $LD_LIBRARY_PATH | tee -a gcc630-timings-report.txt
./alloc630 -t -p $runs | tee -a gcc630-timings-report.txt

. /usr/local/bin/setenv-for-gcc710.sh
which g++ | tee gcc710-timings-report.txt
echo $LD_LIBRARY_PATH | tee -a gcc710-timings-report.txt
./alloc710 -t -p $runs | tee -a gcc710-timings-report.txt
