# QMSDD

+ C++ Implementation of QMSDD

## Dev Environment
```bash
# g++ --version
Apple clang version 12.0.5 (clang-1205.0.22.9)
Target: x86_64-apple-darwin20.4.0
```

## build
Use ``make`` to build the program ``./bin/main``

## usage

```bash
# after building
./bin/main <filename>
```

*.table file format:
```
<n, an Integer: variable count>
<fn, an Integer: function count>
loop for fn lines:
  for each line, there are 2^n symbol, 0, 1, or other ascii
```
