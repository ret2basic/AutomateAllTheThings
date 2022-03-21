Command line used to find this crash:

afl-fuzz -m none -i /home/ret2basic/AutomateAllTheThings/Fuzzing_101/04_libtiff/fuzzing_tiff/tiff-4.0.4/test/images -o /home/ret2basic/AutomateAllTheThings/Fuzzing_101/04_libtiff/fuzzing_tiff/out -s 123 -- /home/ret2basic/AutomateAllTheThings/Fuzzing_101/04_libtiff/fuzzing_tiff/install/bin/tiffinfo -D -j -c -r -s -w @@

If you can't reproduce a bug outside of afl-fuzz, be sure to set the same
memory limit. The limit used for this fuzzing session was 0 B.

Need a tool to minimize test cases before investigating the crashes or sending
them to a vendor? Check out the afl-tmin that comes with the fuzzer!

Found any cool bugs in open-source tools using afl-fuzz? If yes, please drop
an mail at <afl-users@googlegroups.com> once the issues are fixed

  https://github.com/AFLplusplus/AFLplusplus

