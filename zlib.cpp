#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

#define ZLIB_COMPAT

#if defined(__arm__) || defined(__aarch64__) || defined(_M_ARM) || defined(_M_ARM64)
#define UNALIGNED_OK
#define ARM_NEON_ADLER32
#define ARM_ACLE_CRC_HASH
#else
#define UNALIGNED_OK
#define X86_CPUID
#define X86_SSE2
#define X86_AVX2
#define X86_SSE42_CRC_HASH
#define X86_SSE42_CRC_INTRIN
#define X86_QUICK_STRATEGY
#define X86_PCLMULQDQ_CRC
#endif


#include <stdio.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#include "zutil.h"

#include "adler32.c"
#include "crc32.c"
#include "compress.c"
#include "deflate.c"
#include "deflate_fast.c"
#include "deflate_slow.c"
#include "deflate_medium.c"
#include "functable.c"
#include "infback.c"
#include "inffast.c"
#include "inflate.c"
#include "inftrees.c"
#include "trees.c"
#include "uncompr.c"

#if 1 // defined(__arm__) || defined(__aarch64__) || defined(_M_ARM) || defined(_M_ARM64)
#include "arch/arm/armfeature.c"
#include "arch/arm/insert_string_acle.c"
#include "arch/arm/fill_window_arm.c"
#include "arch/arm/crc32_acle.c"
#include "arch/arm/adler32_neon.c"
#endif

#ifdef X86_SSE2
#include "arch/x86/crc_folding.c"
#include "arch/x86/deflate_quick.c"
#include "arch/x86/fill_window_sse.c"
#include "arch/x86/insert_string_sse.c"
#include "arch/x86/slide_avx.c"
#include "arch/x86/slide_sse.c"
#include "arch/x86/x86.c"
#endif

#undef GZIP
#include "zutil.c"
#include "gzlib.c"
#include "gzread.c"
#include "gzwrite.c"
#include "gzclose.c"

