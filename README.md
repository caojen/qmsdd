# QMSDD

C++ Implementation of QMSDD

## Dev Environment
```bash
# g++ --version
Apple clang version 12.0.5 (clang-1205.0.22.9)
Target: x86_64-apple-darwin20.4.0
```
C++11 is required.

## build
Use ``make`` to build the program ``./bin/qmsdd``

## usage

After building ``./bin/qmsdd``, you can simply use:
```bash
./bin/qmsdd <filename>
```
to run test cases.

All test cases are stored in ``inputs`` directory. You can simply use ``./run_all_tests.sh`` to run all tests. The test results will show in ``stdout``.

For example, ``./bin/qmsdd inputs/5qbitcode.real`` runs the file ``inputs/5qbitcode.real``.

There are 2 kinds of files, one is ``*.real`` files which are from the [QMDD package](http://www.informatik.uni-bremen.de/agra/eng/qmdd.php). We use QMDD package to resolve these ``*.real`` files. The other kind of file is ``*.table`` which can be used to build the example in the paper.

``*.table`` files are formatted as follows:
1. The first line is an integer, donated as $n$, represents the number of variables.
2. The second line is an integer, donated as $x$, represents the number of functions.
3. For the third to $(x+2)^{th}$ lines, each line contains $2^n$ integers, splited with `' '`. The $(i^{th})_{10}=(x_1x_2...x_n)_2$ integer, represents the terminator that the path from $x_1$ to $x_n$ can reach. If it's a ``char`` like ``a``, but not an integer, it represents a complex number.

An example of ``*.table`` file is ``inputs/test2.table``:
```
5
5
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1
0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0
0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
```