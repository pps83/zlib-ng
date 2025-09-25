#ifdef _MSC_VER
#pragma warning(disable: 4127 4244 4324 4334)
#define _CRT_NONSTDC_NO_WARNINGS
#endif

#if defined(__arm__) || defined(__aarch64__) || defined(_M_ARM) || defined(_M_ARM64)
#error ARM build is not supported
#endif

#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
#define __SSE__ 1
#define __SSE2__ 1
#define __SSE3__ 1
#define __SSSE3__ 1
#define __SSE4_1__ 1
#define __SSE4_2__ 1
#define __BMI__ 1
#define __BMI2__ 1
#define __AVX__ 1
#define __AVX2__ 1
#endif

#undef STRINGIFY_IMPLEMENTATION_
#undef STRINGIFY_
#define STRINGIFY_IMPLEMENTATION_(a) #a
#define STRINGIFY_(a) STRINGIFY_IMPLEMENTATION_(a)

#ifdef __clang__
#define ZLIB_TARGET_REGION(T) _Pragma(STRINGIFY_(clang attribute push(__attribute__((target(T))), apply_to = function)))
#define ZLIB_UNTARGET_REGION  _Pragma("clang attribute pop")
#elif defined(__GNUC__)
#define ZLIB_TARGET_REGION(T) _Pragma("GCC push_options") _Pragma(STRINGIFY_(GCC target(T)))
#define ZLIB_UNTARGET_REGION  _Pragma("GCC pop_options")
#else
#define ZLIB_TARGET_REGION(T)
#define ZLIB_UNTARGET_REGION
#endif

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#include <cpuid.h>
#endif
#ifdef __clang__ // required for clang-cl build:
#include <avx512fintrin.h>
#include <avx512bwintrin.h>
#include <avx512vnniintrin.h>
#include <avx512vlvnniintrin.h>
#include <avx512vlbwintrin.h>
#include <vpclmulqdqintrin.h>
#endif

#ifdef _DEBUG
#define ZLIB_DEBUG
#include <ctype.h>
#include <inttypes.h>
#endif
#include <assert.h>

#if defined(__clang__) || defined(__GNUC__)
#if !defined(_WIN32) && !defined(__CYGWIN__)
#define HAVE_VISIBILITY_HIDDEN
#define HAVE_VISIBILITY_INTERNAL
#endif
#define HAVE_BUILTIN_CTZ
#define HAVE_BUILTIN_CTZLL
#endif

#define ZLIB_AMALGAMATED 1
#define ZLIB_COMPAT 1

#if _MSC_VER
#define HAVE_CPUID_MS
#elif defined(__GNUC__) || defined(__clang__)
#define HAVE_CPUID_GNU
#endif

//#define WITH_GZFILEOP
#define HAVE_BUILTIN_ASSUME_ALIGNED
#define X86_AVX2
#define X86_AVX512
#define X86_AVX512VNNI
#define X86_FEATURES
#define X86_HAVE_XSAVE_INTRIN
#define X86_MASK_INTRIN
#define X86_PCLMULQDQ_CRC
#define X86_SSE2
#define X86_SSE41
#define X86_SSE42
#define X86_SSSE3
#define X86_VPCLMULQDQ_CRC
#if defined(__GNUC__) || defined(__clang__)
#define HAVE_ATTRIBUTE_ALIGNED
#pragma GCC diagnostic ignored "-Wattributes"
#endif

#include "zbuild.h"
#include "zlib.h"
#include "cpu_features.h"
#include "functable.h"
#include "arch_functions.h"

ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1")
#include "adler32.c"
#include "arch/generic/adler32_c.c"
#include "arch/generic/adler32_fold_c.c"
#include "arch/x86/adler32_avx2.c"
#include "arch/x86/adler32_sse42.c"
#include "arch/x86/adler32_ssse3.c"
ZLIB_UNTARGET_REGION
#define partial_hsum partial_hsum_avx512
#define adler32_fold_copy_impl adler32_fold_copy_impl_avx512
ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1,avx512f,avx512bw")
#include "arch/x86/adler32_avx512.c"
ZLIB_UNTARGET_REGION
ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1,avx512f,avx512bw,avx512vl,avx512vnni")
#include "arch/x86/adler32_avx512_vnni.c"
#   include "zlib_undef.inl"
#undef DO1
#undef DO8
ZLIB_UNTARGET_REGION

ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1")
#include "crc32_braid_comb.c"
#include "arch/generic/crc32_c.c"
#include "arch/generic/crc32_chorba_c.c"
#include "arch/generic/crc32_braid_c.c"
#include "arch/generic/crc32_fold_c.c"
#include "arch/x86/chorba_sse41.c"
#include "arch/x86/crc32_pclmulqdq.c"
#   include "zlib_undef.inl"
#include "crc32.c"
ZLIB_UNTARGET_REGION
ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1,avx512f,vpclmulqdq")
#define crc32_small crc32_small_v
#include "arch/x86/crc32_vpclmulqdq.c"
#   include "zlib_undef.inl"
#undef DO1
#undef DO8
ZLIB_UNTARGET_REGION

ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1")
#define chunkmemset_2 chunkmemset_2_c
#define chunkmemset_4 chunkmemset_4_c
#define chunkmemset_8 chunkmemset_8_c
#define loadchunk loadchunk_c
#define storechunk storechunk_c
#define chunk_t chunk_t_c
#define GET_CHUNK_MAG GET_CHUNK_MAG_c
#define CHUNKCOPY_SAFE CHUNKCOPY_SAFE_c
#include "arch/generic/chunkset_c.c"
#   include "zlib_undef.inl"

#include "arch/generic/compare256_c.c"
#include "compress.c"
#include "cpu_features.c"
#include "deflate.c"
#include "deflate_fast.c"
#include "deflate_huff.c"
#include "deflate_medium.c"
#include "deflate_quick.c"
#include "deflate_rle.c"
#include "deflate_slow.c"
#include "deflate_stored.c"
#include "infback.c"
#   include "zlib_undef.inl"
#include "inftrees.c"
#include "insert_string.c"
#   include "zlib_undef.inl"
#include "insert_string_roll.c"
#   include "zlib_undef.inl"
#include "arch/generic/slide_hash_c.c"
#include "trees.c"
#include "uncompr.c"
#include "inflate.c"
#   include "zlib_undef.inl"
#include "zutil.c"
#include "arch/x86/x86_features.c"

#define slide_hash_chain slide_hash_chain_avx2
#include "arch/x86/slide_hash_avx2.c"
#undef slide_hash_chain

#define perm_idx_lut perm_idx_lut_avx2
#define chunkmemset_2 chunkmemset_2_avx2
#define chunkmemset_4 chunkmemset_4_avx2
#define chunkmemset_8 chunkmemset_8_avx2
#define loadchunk loadchunk_avx2
#define storechunk storechunk_avx2
#define chunk_t chunk_t_avx2
#define GET_CHUNK_MAG GET_CHUNK_MAG_avx2
#define CHUNKCOPY_SAFE CHUNKCOPY_SAFE_avx2
#include "arch/x86/chunkset_avx2.c"
#   include "zlib_undef.inl"

#include "arch/x86/compare256_avx2.c"

#define perm_idx_lut perm_idx_lut_ssse3
#define chunkmemset_2 chunkmemset_2_ssse3
#define chunkmemset_4 chunkmemset_4_ssse3
#define chunkmemset_8 chunkmemset_8_ssse3
#define loadchunk loadchunk_ssse3
#define storechunk storechunk_ssse3
#define chunk_t chunk_t_ssse3
#define GET_CHUNK_MAG GET_CHUNK_MAG_ssse3
#define CHUNKCOPY_SAFE CHUNKCOPY_SAFE_ssse3
#include "arch/x86/chunkset_ssse3.c"
#   include "zlib_undef.inl"

#define chunkmemset_2 chunkmemset_2_sse2
#define chunkmemset_4 chunkmemset_4_sse2
#define chunkmemset_8 chunkmemset_8_sse2
#define loadchunk loadchunk_sse2
#define storechunk storechunk_sse2
#define chunk_t chunk_t_sse2
#define GET_CHUNK_MAG GET_CHUNK_MAG_sse2
#define CHUNKCOPY_SAFE CHUNKCOPY_SAFE_sse2
#include "arch/x86/chunkset_sse2.c"
#   include "zlib_undef.inl"

#include "arch/x86/chorba_sse2.c"
#include "arch/x86/compare256_sse2.c"
#include "arch/x86/slide_hash_sse2.c"
ZLIB_UNTARGET_REGION

ZLIB_TARGET_REGION("bmi2,avx512vl,avx512bw")
#define perm_idx_lut perm_idx_lut_avx2
#define chunkmemset_2 chunkmemset_2_avx512
#define chunkmemset_4 chunkmemset_4_avx512
#define chunkmemset_8 chunkmemset_8_avx512
#define loadchunk loadchunk_avx512
#define storechunk storechunk_avx512
#define chunk_t chunk_t_avx512
#define GET_CHUNK_MAG GET_CHUNK_MAG_avx512
#define CHUNKCOPY_SAFE CHUNKCOPY_SAFE_avx512

#define chunkmemset_16 chunkmemset_16_avx512
#define HALFCHUNKCOPY HALFCHUNKCOPY_avx512
#define GET_HALFCHUNK_MAG GET_HALFCHUNK_MAG_avx512
#define loadhalfchunk loadhalfchunk_avx512
#define storehalfchunk storehalfchunk_avx512
#define halfchunk2whole halfchunk2whole_avx512

#include "arch/x86/chunkset_avx512.c"
#   include "zlib_undef.inl"
#include "arch/x86/compare256_avx512.c"
#   include "zlib_undef.inl"
ZLIB_UNTARGET_REGION

#include "functable.c"

#ifdef WITH_GZFILEOP
#undef GZIP
#include "gzlib.c"
#include "gzread.c"
#include "gzwrite.c"
#endif
