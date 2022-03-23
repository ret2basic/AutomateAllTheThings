# Fuzzing GIMP (Persistent Mode)

For this exercise, we will fuzz GIMP image editor. The goal is to find a crash/PoC for **CVE-2016-4994** in GIMP 2.8.16. In this exercise, we will learn:

- How to use persistent mode to speed up fuzzing
- How to fuzz interactive / GUI applications

## Persistent mode

The AFL persistent mode is based on **in-process fuzzers**: fuzzers that make use of a single one process, injecting code into the target process and changing the input values in memory.

afl-fuzz supports a working mode that combines the benefits of in-process fuzzing with the robustness of a more traditional multi-process tool: **the Persistent Mode**.

In persistent mode, AFL++ fuzzes a target multiple times in a single forked process, instead of forking a new process for each fuzz execution. This mode can improve the fuzzing speed up to 20X times.

The basic structure of the target would be as follows:

```C
  //Program initialization

  while (__AFL_LOOP(10000)) {

    /* Read input data. */
    /* Call library code to be fuzzed. */
    /* Reset state. */
  }
  
  //End of fuzzing
  
```

You can find more information about AFL++ persistent mode at: https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.persistent_mode.md

## Setup

Create a workspace:

```shell
export PROJECT=~/AutomateAllTheThings/Fuzzing_101/05_libxml2 && cd $PROJECT && mkdir fuzzing_gimp && cd fuzzing_gimp
```

Install dependencies:

```shell
sudo apt install build-essential libatk1.0-dev libfontconfig1-dev libcairo2-dev libgudev-1.0-0 libdbus-1-dev libdbus-glib-1-dev libexif-dev libxfixes-dev libgtk2.0-dev python2.7-dev libpango1.0-dev libglib2.0-dev zlib1g-dev intltool libbabl-dev
```

Install GEGL 0.2(Generic Graphics Library), which is another dependency:

```shell
wget https://download.gimp.org/pub/gegl/0.2/gegl-0.2.2.tar.bz2 && tar xvf gegl-0.2.2.tar.bz2 && cd gegl-0.2.2
```

**Note:** The original tutorial uses gegl-0.2.0 but I can't build and install it.

Modify the source code:

```shell
sed -i 's/CODEC_CAP_TRUNCATED/AV_CODEC_CAP_TRUNCATED/g' ./operations/external/ff-load.c && sed -i 's/CODEC_FLAG_TRUNCATED/AV_CODEC_FLAG_TRUNCATED/g' ./operations/external/ff-load.c
```

Build and install Gegl-0.2:

```shell
./configure --enable-debug --disable-glibtest  --without-vala --without-cairo --without-pango --without-pangocairo --without-gdk-pixbuf --without-lensfun --without-libjpeg --without-libpng --without-librsvg --without-openexr --without-sdl --without-libopenraw --without-jasper --without-graphviz --without-lua --without-libavformat --without-libv4l --without-libspiro --without-exiv2 --without-umfpack && make -j$(nproc) && sudo make install
```

Download and extract GIMP 2.8.16:

```shell
cd $PROJECT/fuzzing_gimp && wget https://mirror.klaus-uwe.me/gimp/pub/gimp/v2.8/gimp-2.8.16.tar.bz2 && tar xvf gimp-2.8.16.tar.bz2 && cd $PROJECT/fuzzing_gimp/gimp-2.8.16
```

## AFL++

Build and install GIMP using afl-clang-lto:

```shell
CC=afl-clang-lto CXX=afl-clang-lto++ PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$PROJECT/Fuzzing_gimp/gegl-0.2.0/ CFLAGS="-fsanitize=address" CXXFLAGS="-fsanitize=address" LDFLAGS="-fsanitize=address" ./configure --disable-gtktest --disable-glibtest --disable-alsatest --disable-nls --without-libtiff --without-libjpeg --without-bzip2 --without-gs --without-libpng --without-libmng --without-libexif --without-aa --without-libxpm --without-webkit --without-librsvg --without-print --without-poppler --without-cairo-pdf --without-gvfs --without-libcurl --without-wmf --without-libjasper --without-alsa --without-gudev --disable-python --enable-gimp-console --without-mac-twain --without-script-fu --without-gudev --without-dbus --disable-mp --without-linux-input --without-xvfb-run --with-gif-compression=none --without-xmc --with-shm=none --enable-debug  --prefix="$PROJECT/Fuzzing_gimp/gimp-2.8.16/install" && AFL_USE_ASAN=1 make -j$(nproc) && AFL_USE_ASAN=1 make install
```

To enable the persistent mode, insert the `AFL_LOOP` macro inside the `xcf_load_invoker` function in `gimp-2.8.16/app/xcf/xcf.c`. After `filename = g_value_get_string (&args->values[1]);`, add the following code:

```c
#ifdef __AFL_COMPILER
  while(__AFL_LOOP(10000)){
#endif
```

After `gimp_value_set_image (&return_vals->values[1], image);`, add the following code:

```c
#ifdef __AFL_COMPILER
  }
#endif

  exit(0);
```


