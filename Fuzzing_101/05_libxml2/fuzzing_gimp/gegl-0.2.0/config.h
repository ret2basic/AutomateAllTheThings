/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to 1 if you are compiling for PowerPC. */
/* #undef ARCH_PPC */

/* Define to 1 if you are compiling for PowerPC64. */
/* #undef ARCH_PPC64 */

/* Define to 1 if you are compiling for ix86. */
#define ARCH_X86 1

/* Define to 1 if you are compiling for amd64. */
#define ARCH_X86_64 1

/* always defined to indicate that i18n is enabled */
#define ENABLE_NLS 1

/* Define if the C pre-processor supports GNU style variadic macros */
#define GEGL_GNUC_VARIADIC_MACROS 1

/* Define if the C++ pre-processor supports variadic macros */
#define GEGL_ISO_CXX_VARIADIC_MACROS 1

/* Define if the C pre-processor supports variadic macros */
#define GEGL_ISO_VARIADIC_MACROS 1

/* The name of the GEGL library */
#define GEGL_LIBRARY "gegl-0.2"

/* Define to 1 if this is an unstable version of GEGL */
/* #undef GEGL_UNSTABLE */

/* Our gettext translation domain. */
#define GETTEXT_PACKAGE "gegl-0.2"

/* Define to 1 if you have the `bind_textdomain_codeset' function. */
#define HAVE_BIND_TEXTDOMAIN_CODESET 1

/* Define to 1 if you have the `dcgettext' function. */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <execinfo.h> header file. */
#define HAVE_EXECINFO_H 1

/* Define to 1 if you have the `fsync' function. */
#define HAVE_FSYNC 1

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if your <locale.h> file defines LC_MESSAGES. */
#define HAVE_LC_MESSAGES 1

/* define to 1 if avformat.h is found in libavformat */
/* #undef HAVE_LIBAVFORMAT_AVFORMAT_H */

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the rint function. */
#define HAVE_RINT 1

/* Define to 1 if the spiro library is available */
/* #undef HAVE_SPIRO */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <suitesparse/umfpack.h> header file. */
/* #undef HAVE_SUITESPARSE_UMFPACK_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <umfpack.h> header file. */
/* #undef HAVE_UMFPACK_H */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "gegl"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "gegl 0.2.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "gegl"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.2.0"

/* File extension for shared libraries */
#define SHREXT ".so"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if MMX assembly is available. */
#define USE_MMX 1

/* Define to 1 if SSE assembly is available. */
#define USE_SSE 1

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to the equivalent of the C99 'restrict' keyword, or to
   nothing if this is not supported.  Do not define if restrict is
   supported directly.  */
#define restrict __restrict
/* Work around a bug in Sun C++: it does not support _Restrict or
   __restrict__, even though the corresponding Sun C compiler ends up with
   "#define restrict _Restrict" or "#define restrict __restrict__" in the
   previous line.  Perhaps some future version of Sun C++ will work with
   restrict; if so, hopefully it defines __RESTRICT like Sun C does.  */
#if defined __SUNPRO_CC && !defined __RESTRICT
# define _Restrict
# define __restrict__
#endif
