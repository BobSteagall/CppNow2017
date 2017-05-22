#!/bin/bash

. /usr/local/bin/setenv-for-gcc540.sh
which g++
make clean
make -j4
mv -v alloc alloc540

echo ""
echo "***********************************************************************"
echo ""

. /usr/local/bin/setenv-for-gcc630.sh
which g++
make clean
make -j4
mv -v alloc alloc630

echo ""
echo "***********************************************************************"
echo ""

. /usr/local/bin/setenv-for-gcc710.sh
which g++
make clean
make -j4
mv -v alloc alloc710

