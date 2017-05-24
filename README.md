## Overview

This is the repo for my C++Now 2017 talk entitled **Testing the Limits of Allocator Awareness.**  It contains the source code used to create the results for the talk, as well as the initial results files and a spreadsheet with the graphs used to create the presentation.

## Contents

The source code is contained in the ``code/include``, ``code/src``, and ``code/test`` subdirectories.  The ``code/vs2015`` and ``code/vs2017`` subdirectories contain solution and project files for Visual Studio 2015 and 2017, respectively.  

The files in ``code/include`` and ``code/src`` observe the following naming conventions:
* File names ending in ``_addressing.h/.cpp`` define _addressing models_;
* File names ending in ``_storage.h/.cpp`` define _storage models_;
* File names ending in ``_pointer.h`` define _pointer interfaces_ (there is only one pointer interface used in this project, and it is defined in ``pointer_interface.h``;
* File names ending in ``_allocation_strategy.h/.cpp`` define _allocation strategies_; and,
* File names ending in ``_allocator.h/.cpp`` define C++14-compatible allocator types.

The terms _addressing model_, _storage model_, _pointer interface_, and _allocation strategy_ are all defined in the presentation.

## Building the Tests

On Windows, just open the appropriate Visual Studio solution file - you should be able to immediately build and run.

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

To see how to run the program, invoke it with no arguments or with the ``-h`` argument.

## Running the Batch Scripts

There are several very simple scripts in the ``code`` subdirectory that I used to do batch builds (``make_for_*.sh``) and batch runs (``poc_run_for*.sh`` and ``run_for_*.sh``) of the test program. These scripts were mostly for my convenience when generating the results I used in the presentation.

The batch scripts rely on the naming conventions I use when building compilers.  If you would like to build your own compilers and install them on your system so that they don't step on each other, then take a look at my compiler build scripts, [gcc-builder](https://gitlab.com/BobSteagall/gcc-builder "A set of scripts to automate the process of building GCC on Linux") and [clang-builder](https://gitlab.com/BobSteagall/clang-builder "A set of scripts to automate the process of building Clang and LibC++ on Linux").

## Seeing Conformance Issues

The test are designed to compile and run regardless of the chosen compiler.  That means that code that fails to compile, crashes while running, or gives bad results is ``#ifdef``'d out.  By searching for the ``COMPILER_CLANG``, ``COMPILER_GCC``, ``COMPILER_MS`` macros, you can see which sections of code are affected by possible bugs or nonconformities.
