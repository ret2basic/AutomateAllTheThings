# Fuzzing LibXML2 (Dictionary, Shared Instances)

For this exercize we will fuzz LibXML2 XML parsing library. The goal is to find a crash/PoC for **CVE-2017-9048** in LibXML2 2.9.4. In this exercise, we will learn:

- To use custom dictionaries for helping the fuzzer to find new execution paths
- To parallelize the fuzzing job accross multiple cores

## Dictionaries

When we want to fuzz complex text-based file formats (such as XML), it’s useful to provide the fuzzer with a dictionary containing a list of basic syntax tokens.

In the case of AFL, such a dictionary is simply a set of words or values which is used by AFL to apply changes to the current in-memory file. Specifically, AFL performs the following changes with the values provided in the dictionary:
- Override: Replaces a specific position with n number of bytes, where n is the length of a dictionary entry.
- Insert: Inserts the dictionary entry at the current file position, forcing all characters to move n positions down and increasing file size.

You can find a good bunch of examples [here](https://github.com/AFLplusplus/AFLplusplus/tree/stable/dictionaries)

## Paralellization

If you have a multi-core system is a good idea to parallelize your fuzzing job to make the most of your CPU resources.

### Independent instances

This is the simplest parallelization strategy. In this mode, we run fully separate instances of afl-fuzz.

It is important to remember that AFL uses a non-deterministic testing algorithm. So, if we run multiples AFL instances, We increase our chances of success.

For this, you only need to run multiple instances of "afl-fuzz" on multiple terminal windows, setting a different "output folder" for each one of them. A simple approach is to run as many fuzzing jobs as cores are on your system.

Note: If you're using the -s flag, you need to use a different seed for each instance

### Shared instances

The use of shared instances is a better approach to parallel fuzzing. In this case, each fuzzer instance gathers any test cases found by other fuzzers.

You will usually have only one master instance at a time:

```shell
./afl-fuzz -i afl_in -o afl_out -M Master -- ./program @@
```

and N-1 number of slaves:

```shell
./afl-fuzz -i afl_in -o afl_out -S Slave1 -- ./program @@
./afl-fuzz -i afl_in -o afl_out -S Slave2 -- ./program @@
...
./afl-fuzz -i afl_in -o afl_out -S SlaveN -- ./program @@
```

## Setup

Create a workspace:

```shell
export PROJECT=~/AutomateAllTheThings/Fuzzing_101/05_libxml2 && cd $PROJECT && rm -rf fuzzing_libxml2 && mkdir fuzzing_libxml2 && cd fuzzing_libxml2
```

Download and extract LibXML 2.9.4:

```shell
wget http://xmlsoft.org/download/libxml2-2.9.4.tar.gz && tar xvf libxml2-2.9.4.tar.gz && cd libxml2-2.9.4
```

Build and install LibXML2:

```shell
sudo apt-get install python-dev && ./configure --prefix="$PROJECT/fuzzing_libxml2/libxml2-2.9.4/install" --disable-shared --without-debug --without-ftp --without-http --without-legacy --without-python LIBS='-ldl' && make -j$(nproc) && make install
```

Here `nproc` is a command that prints the number of CPUs. Test LibXML2:

```shell
$PROJECT/fuzzing_libxml2/libxml2-2.9.4/xmllint --memory $PROJECT/fuzzing_libxml2/libxml2-2.9.4/test/wml.xml
```

Get some XML samples from Github:

```shell
cd $PROJECT/fuzzing_libxml2 && mkdir afl_in && cd afl_in && wget https://raw.githubusercontent.com/antonio-morales/Fuzzing101/main/Exercise%205/SampleInput.xml && cd $PROJECT/fuzzing_libxml2
```

Get the XML dictionary provided with AFL++:

```shell
cd $PROJECT/fuzzing_libxml2 && mkdir dictionaries && cd dictionaries && wget https://raw.githubusercontent.com/AFLplusplus/AFLplusplus/stable/dictionaries/xml.dict && cd $PROJECT/fuzzing_libxml2
```

## Compilation

Clean all previously compiled object files and executables:

```shell
rm -rf $PROJECT/fuzzing_libxml2/install && cd $PROJECT/fuzzing_libxml2/libxml2-2.9.4 && make clean
```

Build and intall LibXML2 with ASAN enabled:

```shell
export LLVM_CONFIG="llvm-config-12" && CC=afl-clang-fast CXX=afl-clang-fast++ CFLAGS="-fsanitize=address" CXXFLAGS="-fsanitize=address" LDFLAGS="-fsanitize=address" ./configure --prefix="$PROJECT/fuzzing_libxml2/libxml2-2.9.4/install" --disable-shared --without-debug --without-ftp --without-http --without-legacy --without-python LIBS='-ldl' && AFL_USE_ASAN=1 make -j$(nproc) && AFL_USE_ASAN=1 make install
```

**Note:** The original tutorial uses afl-clang-lto but it will take forever to find a crash, so I changed it to afl-clang-fast.

## AFL++

Run AFL++!

This time we are going to run **two shared instances** of AFL++ and call them *"master"* and *"slave1"* respectively. In order to catch the bug, is mandatory to enable the `--valid` parameter. I also set the dictionary path with the `-x` flag and enabled the deterministic mutations with the `-D` flag (only for the master fuzzer). Also, it may take many hours for AFL++ to find a crash, so it is a good idea to run AFL++ in the cloud. Use the `screen` command to run it in background.

Run the master fuzzer:

```shell
screen export PROJECT=~/AutomateAllTheThings/Fuzzing_101/05_libxml2 && afl-fuzz -m none -i $PROJECT/fuzzing_libxml2/afl_in -o $PROJECT/fuzzing_libxml2/afl_out -s 123 -x $PROJECT/fuzzing_libxml2/dictionaries/xml.dict -D -M master -- $PROJECT/fuzzing_libxml2/libxml2-2.9.4/xmllint --memory --noenc --nocdata --dtdattr --loaddtd --valid --xinclude @@
```

Spawn another shell and run the slave fuzzer:

```shell
export PROJECT=~/AutomateAllTheThings/Fuzzing_101/05_libxml2 && afl-fuzz -m none -i $PROJECT/fuzzing_libxml2/afl_in -o $PROJECT/fuzzing_libxml2/afl_out -s 234 -S slave1 -- $PROJECT/fuzzing_libxml2/libxml2-2.9.4/xmllint --memory --noenc --nocdata --dtdattr --loaddtd --valid --xinclude @@
```

Within  minutes, AFL++ found crashes:



## Triage

Generate the ASAN report:

```shell
$PROJECT/fuzzing_libxml2/libxml2-2.9.4/xmllint --memory --noenc --nocdata --dtdattr --loaddtd --valid --xinclude "$PROJECT/fuzzing_libxml2/afl_out/default/crashes/"
```
