# Fuzzing Adobe Reader (QEMU Mode)

For this exercise, we will fuzz Adobe Reader application. The goal is to find an Out-of-bounds vulnerability in Adobe Reader 9.5.1. In this exercise, we will learn:

- How to use AFL++'s QEMU mode to fuzz closed-source applications
- How to enable persistent mode in QEMU mode
- How to use QASAN, a binary-only sanitizer

## AFL++ QEMU Mode

AFL++ is able to fuzz closed-source application. It is simple: install the software and run `afl-fuzz` with the `-Q` flag. However, the speed can be really *slow*. **The solution is running AFL++ QEMU mode together with persistent mode.** There are two ways of entering persistent mode:

- For open-source application, insert `AFL_LOOP` in the source code.
- For closed-sourse application, 

## Setup

Install `afl-qemu-trace`:

```shell
sudo apt install ninja-build libc6-dev-i386 && cd $HOME/AFLplusplus/qemu_mode && ./build_qemu_support.sh
```

Install the dependency for Adobe Reader:

```shell
sudo apt install libxml2:i386
```

Create a workspace:

```shell
export PROJECT=~/AutomateAllTheThings/Fuzzing_101/08_adobe_reader && cd $PROJECT && rm -rf fuzzing_adobe_reader && mkdir fuzzing_adobe_reader && cd fuzzing_adobe_reader
```

Download and install Adobe Reader 9.5.1:

```shell
wget ftp://ftp.adobe.com/pub/adobe/reader/unix/9.x/9.5.1/enu/AdbeRdr9.5.1-1_i386linux_enu.deb && sudo dpkg -i AdbeRdr9.5.1-1_i386linux_enu.deb
```

Test Adobe Reader:

```shell
/opt/Adobe/Reader9/bin/acroread --help
```

Note that `/opt/Adobe/Reader9/bin/acroread` is just a shell script. The real binary path is `/opt/Adobe/Reader9/Reader/intellinux/bin/acroread`.

For this exercise, I'll make use of a corpus downloaded from SafeDocs "Issue Tracker" Corpus. You can find more information about this PDF Corpus here:

https://www.pdfa.org/a-new-stressful-pdf-corpus/

Download and extract the corpus:

```shell
wget https://corpora.tika.apache.org/base/packaged/pdfs/archive/pdfs_202002/libre_office.zip && unzip libre_office.zip -d extracted
```

Only keep file smaller than 2KB to speed up the fuzzing process:

```shell
mkdir -p $PROJECT/fuzzing_adobe_reader/afl_in && find ./extracted -type f -size -2k -exec cp {} $PROJECT/fuzzing_adobe_reader/afl_in \;
```

## QEMU Persistent Mode

As we see in Exercise 6: Fuzzing GIMP, inserting the `AFL_LOOP` is the way that we have to tell AFL++ that we want to enable the persistent mode. In this case, however, we don't have access to the source code.

We can instead make use of the `AFL_QEMU_PERSISTENT_ADDR` to specify the start of the persistent loop. This address should be set to the beginning of a function. RTFM:

https://github.com/AFLplusplus/AFLplusplus/blob/stable/qemu_mode/README.persistent.md

In this exercise we are going to use the **callgrind** disassembler. RTFM:

https://valgrind.org/docs/manual/cl-manual.html

Install valgrind and kcachegrind:

```shell
sudo apt install valgrind && sudo apt install kcachegrind
```

Generate callgrind report:

```shell
ACRO_INSTALL_DIR=/opt/Adobe/Reader9/Reader ACRO_CONFIG=intellinux LD_LIBRARY_PATH=$LD_LIBRARY_PATH:'/opt/Adobe/Reader9/Reader/intellinux/lib' valgrind --tool=callgrind /opt/Adobe/Reader9/Reader/intellinux/bin/acroread -toPostScript $PROJECT/fuzzing_adobe_reader/extracted/107389-114992/LIBRE_OFFICE-114962-1.pdf
```

Here `LIBRE_OFFICE-114962-1.pdf` is just a random PDF sample coming from the corpus we just downloaded. Visualize this report with kachegrind:

```shell
kcachegrind
```

![]()

## AFL++

Run AFL++!

This time we use **QASan (QEMU-AddressSanitizer)**. QASan is a custom QEMU 3.1.1 that detects memory errors in the guest using AddressSanitizer. As QEMU is a binary code emulator, QASan is a binary-only sanitizer and does not require compiler-based instrumentation. To enable it we only need to set `AFL_USE_QASAN=1`. RTFM:

https://github.com/AFLplusplus/AFLplusplus/tree/dev/qemu_mode/libqasan

Run AFL++ with QASan enabled:

```shell
AFL_USE_QASAN=1 AFL_QEMU_PERSISTENT_ADDR=0x08546a00 AFL_QEMU_PERSISTENT_GPR=1 ACRO_INSTALL_DIR=/opt/Adobe/Reader9/Reader ACRO_CONFIG=intellinux LD_LIBRARY_PATH=$LD_LIBRARY_PATH:'/opt/Adobe/Reader9/Reader/intellinux/lib' afl-fuzz -Q -i $PROJECT/fuzzing_adobe_reader/afl_in -o $PROJECT/fuzzing_adobe_reader/afl_out -t 2000 -- /opt/Adobe/Reader9/Reader/intellinux/bin/acroread -toPostScript @@
```

Explanation:

- `AFL_QEMU_PERSISTENT_ADDR`: 
- `AFL_QEMU_PERSISTENT_GPR`: 
- `ACRO_INSTALL_DIR`: 
- `ACRO_CONFIG`: 
- `LD_LIBRARY_PATH`: 

## Triage

Run `afl-qemu-trace`:

```shell
ACRO_INSTALL_DIR=/opt/Adobe/Reader9/Reader ACRO_CONFIG=intellinux LD_LIBRARY_PATH=$LD_LIBRARY_PATH:'/opt/Adobe/Reader9/Reader/intellinux/lib' /usr/local/bin/afl-qemu-trace -- /opt/Adobe/Reader9/Reader/intellinux/bin/acroread -toPostScript [crashFilePath] 
```
