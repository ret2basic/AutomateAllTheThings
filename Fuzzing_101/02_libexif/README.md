# Fuzzing libexif

This time we will fuzz **libexif EXIF parsing library**. The goal is to find a crash/PoC for **CVE-2009-3895** and another crash for **CVE-2012-2836** in libexif 0.6.15. In this exercise, we will learn:

- To fuzz a library using an external application
- To use afl-clang-lto, a collision free instrumentation that is faster and provides better results than afl-clang-fast
- To use Eclipse IDE as an easy alternative to GDB console for triaging

**Note:** the original tutorial sets libexif 0.6.14 as fuzzing target. However, I can't build and install on my Ubuntu 20.04, so I changed my target to libexif 0.6.15. The fuzzing experience will be the same.

## Setup

Create a new directory for our project:

```shell
export PROJECT=~/AutomateAllTheThings/Fuzzing_101/02_libexif && cd $PROJECT && mkdir fuzzing_libexif && cd fuzzing_libexif
```

Download and extract libexif-0.6.15:

```shell
wget https://github.com/libexif/libexif/archive/refs/tags/libexif-0_6_15-release.tar.gz && tar -xzvf libexif-0_6_15-release.tar.gz
```

Build and install libexif:

```shell
cd libexif-libexif-0_6_15-release && sudo apt install autopoint libtool gettext libpopt-dev && autoreconf -fvi && ./configure --enable-shared=no --prefix="$PROJECT/fuzzing_libexif/install" && make && make install
```

## Harness

AFL++ targets an executable that takes user input. In our case, we are fuzzing a library (libexif) and the functions in libexif are not invoked. Therefore, we need an interface application that calls functions in libexif and this application must take user input and exits smoothly. Such an interface application is usually called **harness**.

Of course, we can write our own harness and compile it into executable, but there is **exif command-line** that does the job so we don't need reinvent the wheel. Download and extract exif command-line:

```shell
cd $PROJECT/fuzzing_libexif && wget https://github.com/libexif/exif/archive/refs/tags/exif-0_6_15-release.tar.gz && tar -xzvf exif-0_6_15-release.tar.gz
```

Build and install exif command-line:

```shell
cd exif-exif-0_6_15-release && autoreconf -fvi && ./configure --enable-shared=no --prefix="$PROJECT/fuzzing_libexif/install" PKG_CONFIG_PATH=$PROJECT/fuzzing_libexif/install/lib/pkgconfig && make && make install
```

Test exif command-line:

```shell
$PROJECT/fuzzing_libexif/install/bin/exif
```

## Seed Corpus

The seed for exif command-line should be exif samples. We can get some sample images directly from Github:

```shell
cd $PROJECT/fuzzing_libexif && wget https://github.com/ianare/exif-samples/archive/refs/heads/master.zip && unzip master.zip
```

Test this corpus:

```shell
$PROJECT/fuzzing_libexif/install/bin/exif $PROJECT/fuzzing_libexif/exif-samples-master/jpg/Canon_40D_photoshop_import.jpg
```

## AFL

This time we try a new compiler: **afl-clang-lto**. In general, afl-clang-lto is the best option if  clang/clang++ 11+ is available. Quote from the [afl-clang-lto documentation](https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.lto.md):

> This version requires a current llvm 11+ compiled from the GitHub master.
> - Use afl-clang-lto/afl-clang-lto++ because it is faster and gives better coverage than anything else that is out there in the AFL world.
> - You can use it together with llvm_mode: laf-intel and the instrument file listing features and can be combined with cmplog/Redqueen.
> - It only works with llvm 11+.
> - AUTODICTIONARY feature (see below)!
> - If any problems arise, be sure to set AR=llvm-ar RANLIB=llvm-ranlib. Some targets might need LD=afl-clang-lto and others LD=afl-ld-lto.

Build libexif using afl-clang-lto:

```shell
rm -rf $PROJECT/fuzzing_libexif/install && cd $PROJECT/fuzzing_libexif/libexif-libexif-0_6_15-release && make clean && export LLVM_CONFIG="llvm-config-11" && CC=afl-clang-lto ./configure --enable-shared=no --prefix="$PROJECT/fuzzing_libexif/install/" && make && make install
```

Build exif using afl-clang-lto:

```shell
cd $PROJECT/fuzzing_libexif/exif-exif-0_6_15-release && make clean && export LLVM_CONFIG="llvm-config-11" && CC=afl-clang-lto ./configure --enable-shared=no --prefix="$PROJECT/fuzzing_libexif/install" PKG_CONFIG_PATH=$PROJECT/fuzzing_libexif/install/lib/pkgconfig && make && make install
```

Run AFL!

```shell
afl-fuzz -i $PROJECT/fuzzing_libexif/exif-samples-master/jpg/ -o $PROJECT/fuzzing_libexif/out/ -s 123 -- $PROJECT/fuzzing_libexif/install/bin/exif @@
```

In about 8 minutes, AFL++ found 14 unique crashes:

[AFL++](https://raw.githubusercontent.com/ret2basic/AutomateAllTheThings/main/Fuzzing_101/02_libexif/AFL.png)

## Triage

In Exercise, we used GDB for analyzing the crash. This time we use **Eclipse-CDT**. Download it from the official website:

https://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/2022-03/R/eclipse-cpp-2022-03-R-linux-gtk-x86_64.tar.gz

Extract it:

```shell
tar zxvf eclipse-cpp-2022-03-R-linux-gtk-x86_64.tar.gz && rm eclipse-cpp-2022-03-R-linux-gtk-x86_64.tar.gz
```

Don't forget to install JDK:

```shell
sudo apt install default-jdk
```

Start Eclipse-CDT:

```shell
cd eclipse && ./eclipse
```

Once we have started Eclipse-CDT, we need to import our source code into the Project Explorer. For that, we need to go to File -> Import -> and then we need to choose C/C++ -> "Existing Code as Makefile Project". Set "Project Name"=libexif and "Existing Code Location"=`$PROJECT/fuzzing_libexif/exif-exif-0_6_15-release`. Then we need to select "Linux GCC" and browse for the Exif source code folder.

Now we're going to configure the debug parameters. For that we need to go to "Run => Debug Configurations". Go to the "Arguments" tab and provide the saved crash payload as argument. For me, it is:

```
/home/ret2basic/AutomateAllTheThings/Fuzzing_101/02_libexif/fuzzing_libexif/out/default/crashes/id:000000,sig:11,src:000320,time:62014,execs:67639,op:havoc,rep:16
```

Now click "Apply", and then "Debug". The debugger will stop before the main function. Click "Run => Resume" to trigger the segfault. Once the segfault is triggered, the debugger highlights the problematic source code:

![Eclipse](https://raw.githubusercontent.com/ret2basic/AutomateAllTheThings/main/Fuzzing_101/02_libexif/Eclipse.png)
