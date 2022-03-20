# Fuzzing libexif

This time we will fuzz **libexif EXIF parsing library**. The goal is to find a crash/PoC for **CVE-2009-3895** and another crash for **CVE-2012-2836** in libexif 0.6.14. In this exercise, we will learn:

- To fuzz a library using an external application
- To use afl-clang-lto, a collision free instrumentation that is faster and provides better results than afl-clang-fast
- To use Eclipse IDE as an easy alternative to GDB console for triaging

## Setup

Create a new directory for our project:

```shell
cd $HOME && mkdir fuzzing_libexif && cd fuzzing_libexif/
```

Download and extract libexif-0.6.14:

```shell
wget https://github.com/libexif/libexif/archive/refs/tags/libexif-0_6_14-release.tar.gz && tar -xzvf libexif-0_6_14-release.tar.gz
```

Build and install libexif:

```shell
cd libexif-libexif-0_6_14-release/ && apt install autopoint libtool gettext libpopt-dev && autoreconf -fvi && ./configure --enable-shared=no --prefix="$HOME/fuzzing_libexif/install/" && make && make install
```

# CVE-2009-3895





# CVE-2012-2836

