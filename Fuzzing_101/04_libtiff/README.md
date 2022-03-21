# Fuzzing LibTIFF

This time we will fuzz LibTIFF image library. The goal is to find a crash/PoC for **CVE-2016-9297** in LibTIFF 4.0.4 and to measure the code coverage data of your crash/PoC. In this exercise, we will learn:

- How to measure code coverage using LCOV
- How to use code coverage data to improve the effectiveness of fuzzing

## Setup

Create a workspace:

```shell
export PROJECT=~/AutomateAllTheThings/Fuzzing_101/04_libtiff && cd $PROJECT && mkdir fuzzing_tiff && cd fuzzing_tiff
```

Download and extract LibTIFF 4.0.4:

```shell
wget https://download.osgeo.org/libtiff/tiff-4.0.4.tar.gz && tar -xzvf tiff-4.0.4.tar.gz
```

Build and install LibTIFF:

```shell
cd tiff-4.0.4 && ./configure --prefix="$PROJECT/fuzzing_tiff/install/" --disable-shared && make && make install
```

LibTIFF provides a harness `tiffinfo` located in the `/bin` directory, and we can use the sample images in `/test/images` as corpus. Test our setup:

```shell
$PROJECT/fuzzing_tiff/install/bin/tiffinfo -D -j -c -r -s -w $PROJECT/fuzzing_tiff/tiff-4.0.4/test/images/palette-1c-1b.tiff
```

Here we enabled all flags in order to improve code coverage.

## LCOV

**Code coverage** is a software metric that show the number of times each line of code is triggered. By using code coverage we will get to know which parts of the code have been reached by the fuzzer and visualizes the fuzzing process. In this exercise, we are going to use **LCOV** to measure code coverage. Install it:

```shell
sudo apt install lcov
```

Rebuild libTIFF with the `--coverage` flag for both compiler and linker:

```shell
rm -rf $PROJECT/fuzzing_tiff/install && cd $PROJECT/fuzzing_tiff/tiff-4.0.4 && make clean && CFLAGS="--coverage" LDFLAGS="--coverage" ./configure --prefix="$PROJECT/fuzzing_tiff/install" --disable-shared && make && make install
```

Collect code coverage data:

```shell
cd $PROJECT/fuzzing_tiff/tiff-4.0.4 && lcov --zerocounters --directory ./ && lcov --capture --initial --directory ./ --output-file app.info && $PROJECT/fuzzing_tiff/install/bin/tiffinfo -D -j -c -r -s -w $PROJECT/fuzzing_tiff/tiff-4.0.4/test/images && palette-1c-1b.tiff && lcov --no-checksum --directory ./ --capture --output-file app2.info
```

Explanation:

- `lcov --zerocounters --directory ./`: 
- `lcov --capture --initial --directory ./ --output-file app.info`: 
- `$PROJECT/fuzzing_tiff/install/bin/tiffinfo -D -j -c -r -s -w $PROJECT/fuzzing_tiff/tiff-4.0.4/test/images/palette-1c-1b.tiff`: 
- `lcov --no-checksum --directory ./ --capture --output-file app2.info`: 

Generate the report in HTML format:

```shell
genhtml --highlight --legend -output-directory ./html-coverage ./app2.info
```

The report can be found at the `html-coverage` directory.

## Compilation

Clean all previously compiled object files and executables:

```shell
rm -rf $PROJECT/fuzzing_tiff/install && cd $HOME/fuzzing_tiff/tiff-4.0.4 && make clean
```

Build and intall LibTIFF with A

## AFL



## Triage

