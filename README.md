## Overview

This is the repo for my C++Now 2017 talk entitled **Testing the Limits of Allocator Awareness.**  It contains the source code used to create the results for the talk, as well as the initial results files and a spreadsheet with the graphs used to create the presentation.

## Contents

The source code is contained in the ``code/include``, ``code/src``, and ``code/test`` subdirectories.  The ``code/vs2015`` and ``code/vs2017`` subdirectories contain solution and project files for Visual Studio 2015 and 2017, respectively.

## Building the Tests

On Windows, just open the appropriate Visual Studio solution file -- you should be able to immediately build and run.

On Linux, you will need CMake 3.5 or higher installed. Change directory to ``code`` and run the ``do_cmake_stuff.sh`` shell script.  At that point you can ``cd`` to the appropriate subdirectory and make the tests.

```
$ cd code
$ ./do_cmake_stuff.sh
$ cd cmake-build-release-gcc       # If you have GCC 5.4 or higher installed
$ make
$ ./alloc [args]
$ cd ..
$ cd cmake-build-release-clang     # If you have Clang 3.8 or higher installed
$ make
$ ./alloc [args]
```




