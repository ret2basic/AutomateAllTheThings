# Fuzzing TCPdump (ASAN)

In this exercise we will fuzz TCPdump packet analyzer. The goal is to find a crash/PoC for **CVE-2017-13028** in TCPdump 4.9.2. In this exercise, we will learn:

- What is **ASAN (Address Sanitizer)**, a runtime memory error detection tool
- How to use ASAN to fuzz a target
- How much easy is to triage the crashes using ASAN

## Setup

Create a workspace:

```shell
export PROJECT=~/AutomateAllTheThings/Fuzzing_101/03_tcpdump && cd $PROJECT && rm -rf fuzzing_tcpdump && cde45gftrmkdir fuzzing_tcpdump
```

Download and extract libpcap (a dependency of TCPdump). We also have to rename it, otherwise TCPdump won't find it:

```shell
cd $PROJECT/fuzzing_tcpdump && wget https://github.com/the-tcpdump-group/libpcap/archive/refs/tags/libpcap-1.8.0.tar.gz && tar -xzvf libpcap-1.8.0.tar.gz && mv libpcap-libpcap-1.8.0 libpcap-1.8.0
```

Build libpcap:

```shell
cd $PROJECT/fuzzing_tcpdump/libpcap-1.8.0 && ./configure --enable-shared=no && make
```

Download and extract TCPdump 4.9.2:

```shell
cd $PROJECT/fuzzing_tcpdump && wget https://github.com/the-tcpdump-group/tcpdump/archive/refs/tags/tcpdump-4.9.2.tar.gz && tar -xzvf tcpdump-4.9.2.tar.gz
```

Build and install TCPdump:

```shell
cd $PROJECT/fuzzing_tcpdump/tcpdump-tcpdump-4.9.2 && ./configure --prefix="$PROJECT/fuzzing_tcpdump/install/" && make && make install
```

Test TCPdump:

```shell
$PROJECT/fuzzing_tcpdump/install/sbin/tcpdump -h
```

TCPdump comes with some sample `.pcap` files in the `tests` directory. We can use them directly, for example:

```shell
$PROJECT/fuzzing_tcpdump/install/sbin/tcpdump -vvvvXX -ee -nn -r ./tests/geneve.pcap
```

# ASAN

**AddressSanitizer (ASAN)** is a fast memory error detector for C and C++. It consists of a compiler instrumentation module and a run-time library. The tool is capable of finding out-of-bounds accesses to heap, stack, and global objects, as well as use-after-free, double-free and memory leaks bugs.

Clean all previously compiled object files and executables:

```shell
rm -rf $PROJECT/fuzzing_tcpdump/install && cd $PROJECT/fuzzing_tcpdump/libpcap-1.8.0 && make clean && cd $PROJECT/fuzzing_tcpdump/tcpdump-tcpdump-4.9.2 && make clean
```

Build TCPdump and libpcap with ASAN enabled:

```shell
cd $PROJECT/fuzzing_tcpdump/libpcap-1.8.0 && export LLVM_CONFIG="llvm-config-12" && CC=afl-clang-lto ./configure --enable-shared=no --prefix="$PROJECT/fuzzing_tcpdump/install" && AFL_USE_ASAN=1 make && cd $PROJECT/fuzzing_tcpdump/tcpdump-tcpdump-4.9.2 && AFL_USE_ASAN=1 CC=afl-clang-lto ./configure --prefix="$PROJECT/fuzzing_tcpdump/install" && AFL_USE_ASAN=1 make && AFL_USE_ASAN=1 make install
```

## AFL

Run AFL!

```shell
afl-fuzz -m none -i $PROJECT/fuzzing_tcpdump/tcpdump-tcpdump-4.9.2/tests -o $PROJECT/fuzzing_tcpdump/out -s 123 -- $PROJECT/fuzzing_tcpdump/install/sbin/tcpdump -vvvvXX -ee -nn -r @@
```

Here the `-m none` flag stands for "no memory limit". This flag is needed since ASAN consumes a lot of memory on 64-bit machine. It took me more than an hour to find a crash. I am sure there are more potential crashes but I don't want to waste time here:

![AFL++](https://raw.githubusercontent.com/ret2basic/AutomateAllTheThings/main/Fuzzing_101/03_tcpdump/AFL.png)

## Triage

Since we compiled the binary with ASAN enabled, we can simply feed the crash payload into the binary and ASAN will generate a report for us automatically:

```shell
$PROJECT/fuzzing_tcpdump/install/sbin/tcpdump -vvvvXX -ee -nn -r "$PROJECT/fuzzing_tcpdump/out/default/crashes/<payload>"
```

For me, it is:

```shell
$PROJECT/fuzzing_tcpdump/install/sbin/tcpdump -vvvvXX -ee -nn -r "$PROJECT/fuzzing_tcpdump/out/default/crashes/id:000000,sig:06,src:001759,time:4539881,execs:2339170,op:havoc,rep:2"
```
