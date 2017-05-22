#!/bin/bash

. /usr/local/bin/setenv-for-clang381.sh
which clang++
make clean
make -j4
mv -v alloc alloc381

echo ""
echo "***********************************************************************"
echo ""

. /usr/local/bin/setenv-for-clang391.sh
which clang++
make clean
make -j4
mv -v alloc alloc391

echo ""
echo "***********************************************************************"
echo ""

. /usr/local/bin/setenv-for-clang400.sh
which clang++
make clean
make -j4
mv -v alloc alloc400

