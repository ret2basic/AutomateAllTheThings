# Fuzzing 101

"Fuzzing 101" is a project where we are going to fuzz 10 real-world applications in order to learn the basics of fuzzing. We are going to use AFL++ throughout the project.

## Setup

Install the dependencies:

```shell
sudo apt update && sudo apt install -y build-essential python3-dev automake git flex bison libglib2.0-dev libpixman-1-dev python3-setuptools && sudo apt install -y lld-11 llvm-11 llvm-11-dev clang-11 || sudo apt install -y lld llvm llvm-dev clang && sudo apt install -y gcc-$(gcc --version|head -n1|sed 's/.* //'|sed 's/\..*//')-plugin-dev libstdc++-$(gcc --version|head -n1|sed 's/.* //'|sed 's/\..*//')-dev
```

Install AFL++:

```shell
cd $HOME && git clone https://github.com/AFLplusplus/AFLplusplus && cd AFLplusplus && export LLVM_CONFIG="llvm-config-11" && make distrib && sudo make install
```

Clone this repo:

```shell
cd ~ && git clone https://github.com/ret2basic/AutomateAllTheThings.git
```

## Exercises

| Exercise No.  | Target | CVEs to find | Time estimated | Main topics |
| ------------- | ------------- | ------------- |  ------------- | ------------- |
| [Exercise 1](./01_xpdf/) | Xpdf  | CVE-2019-13288 | 120 mins | Afl-clang-fast, Afl-fuzz, GDB |
| [Exercise 2](./02_libexif/)  | libexif  |  CVE-2009-3895, CVE-2012-2836 | 6 hours | Afl-clang-lto, Fuzz libraries, Eclipse IDE|
| [Exercise 3](./03_tcpdump/)  | TCPdump  | CVE-2017-13028 | 4 hours | ASan, Sanitizers |
| [Exercise 4](./04_libtiff/)  | LibTIFF  | CVE-2016-9297 | 3 hours | Code coverage, LCOV |
| [Exercise 5](./05_libxml2/)  | Libxml2  | CVE-2017-9048 | 3 hours | Dictionaries, Basic parallelization, Fuzzing command-line arguments  |
| [Exercise 6](./06_gimp)  | GIMP  | CVE-2016-4994, Bonus bugs | 7 hours | Persistent fuzzing, Fuzzing interactive applications|
| [Exercise 7](./07_vlcmediaplayer/)  | VLC media player | CVE-2019-14776 | 6 hours | Partial instrumentation, Fuzzing harness |
| [Exercise 8](./08_adobereader/)  | Adobe Reader  | | 8 hours | Fuzzing closed-source applications, QEMU instrumentation|
| [Exercise 9](./09_7zip/)  | 7-Zip  | CVE-2016-2334 | 8 hours | WinAFL, Fuzzing Windows Applications|
| [**Exercise 10 (Final Challenge)**](./10_v8/)  | **Google Chrome / V8**  | **CVE-2019-5847** | **8 hours** | **Fuzzilli, Fuzzing Javascript engines** |
