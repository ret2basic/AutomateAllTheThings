# Fuzzing VNC Media Player (Partial Instrumentation, Harness)

For this exercise, we will fuzz VLC media player. The goal is to find a crash/PoC for **CVE-2019-14776** in VLC 3.0.7.1. In this exercise, we will learn:

- How to use Partial Instrumentation to only instrument the relevant parts of the program
- How to write fuzzing harnesses to test large applications more efficiently

## Partial Instrumentation

One of the advantages of using an evolutionary coverage-guided fuzzer is that it's capable of finding new execution paths all by itself. However, this can often also be a disadvantage. This is particularly true when we face software with a highly modular architecture (as in the case of VLC media player), where each module performs a specific task.

So, let's assume we fed the fuzzer with a valid MKV file. But after several mutations of the input file, the file “magic bytes” have changed and now the input file is viewed as an AVI file by our program. Therefore, this “mutated MKV file” is now processed by AVI Demux. After some time, the file magic bytes change once again and now the file is viewed as an MPEG file. In both cases, the potential of this newly mutated file to increase our code coverage is very poor because this new file won't have any valid syntax structure.

In short, if we don't put constraints on code coverage, the fuzzer can easily choose a wrong path which in turn makes the fuzzing process less effective.

To address this problem, AFL++ includes a Partial Instrumentation feature that allows you to specify which functions/files should be compiled with or without instrumentation. This helps the fuzzer focus on the important parts of the program, avoiding undesired noise and disturbance by exercising uninteresting code paths.

To use it, we set the environment AFL_LLVM_ALLOWLIST variable when compiling. This environment variable must point to a file containing all the functions/filenames that should be instrumented.

You can find more information about AFL++ partial instrumentation at:

https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.instrument_list.md

## Setup