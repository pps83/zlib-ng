#ifdef _MSC_VER
#pragma warning(disable: 4334)
#define _CRT_NONSTDC_NO_WARNINGS 
#endif

#if defined(__arm__) || defined(__aarch64__) || defined(_M_ARM) || defined(_M_ARM64)
#error ARM build is not supported
#endif

#ifndef __AVX__
#error Has to compile with Advanced Vector Extensions (/arch:AVX) or greater
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

#include <intrin.h>
#ifdef __clang__ // required for clang-cl build:
#include <avx512fintrin.h>
#include <avx512bwintrin.h>
#include <avx512vnniintrin.h>
#include <avx512vlvnniintrin.h>
#include <avx512vlbwintrin.h>
#include <vpclmulqdqintrin.h>
#endif

#if defined(__clang__) || defined(__GNUC__)
#ifndef _WIN32
#define HAVE_VISIBILITY_HIDDEN
#define HAVE_VISIBILITY_INTERNAL
#endif
#define HAVE_BUILTIN_CTZ
#define HAVE_BUILTIN_CTZLL
#endif

#ifdef _DEBUG
#define ZLIB_DEBUG
#include <ctype.h>
#include <inttypes.h>
#endif

#define ZLIB_AMALGAMATED 1
#define ZLIB_COMPAT 1

#define NO_FSEEKO
#define WITH_GZFILEOP
#define X86_FEATURES
#define X86_AVX2
#define X86_AVX2_ADLER32
#define X86_AVX_CHUNKSET
#define X86_MASK_INTRIN
#define X86_SSE41
#define X86_SSE42_CRC_HASH
#define X86_SSE42_ADLER32
#define X86_SSE42_CRC_INTRIN
#define X86_NOCHECK_TZCNT
#define X86_NOCHECK_SSE2
#define X86_SSE2
#define X86_SSE2_CHUNKSET
#define X86_SSE2_SLIDEHASH
#define X86_SSSE3
#define X86_SSSE3_ADLER32

ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1")

#include "zbuild.h"
#include "zlib.h"

#include "adler32.c"
#   include "zlib_undef.inl"
#include "adler32_fold.c"

#define chunkmemset_2 chunkmemset_2_c
#define chunkmemset_4 chunkmemset_4_c
#define chunkmemset_8 chunkmemset_8_c
#define loadchunk loadchunk_c
#define storechunk storechunk_c
#define chunk_t chunk_c_t
#define GET_CHUNK_MAG GET_CHUNK_MAG_c
#include "chunkset.c"
#   include "zlib_undef.inl"

#include "compare256.c"
#include "compress.c"
#include "cpu_features.c"
#include "crc32_braid.c"
#include "crc32_braid_comb.c"
#include "crc32_fold.c"
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
#include "slide_hash.c"
#include "trees.c"
#include "uncompr.c"
#include "inflate.c"
#   include "zlib_undef.inl"
#include "zutil.c"
#include "arch/x86/x86_features.c"
#include "arch/x86/slide_hash_avx2.c"

#define perm_idx_lut perm_idx_lut_avx
#define chunkmemset_2 chunkmemset_2_avx
#define chunkmemset_4 chunkmemset_4_avx
#define chunkmemset_8 chunkmemset_8_avx
#define loadchunk loadchunk_avx
#define storechunk storechunk_avx
#define chunk_t chunk_avx_t
#define GET_CHUNK_MAG GET_CHUNK_MAG_avx
#include "arch/x86/chunkset_avx.c"
#   include "zlib_undef.inl"

#include "arch/x86/compare256_avx2.c"
#include "arch/x86/adler32_avx2.c"
#   include "zlib_undef.inl"

#define perm_idx_lut perm_idx_lut_sse41
#define chunkmemset_2 chunkmemset_2_sse41
#define chunkmemset_4 chunkmemset_4_sse41
#define chunkmemset_8 chunkmemset_8_sse41
#define loadchunk loadchunk_sse41
#define storechunk storechunk_sse41
#define chunk_t chunk_sse41_t
#define GET_CHUNK_MAG GET_CHUNK_MAG_sse41
#include "arch/x86/chunkset_sse41.c"
#   include "zlib_undef.inl"

#include "arch/x86/adler32_sse42.c"
#include "arch/x86/insert_string_sse42.c"
#   include "zlib_undef.inl"

#define chunkmemset_2 chunkmemset_2_sse2
#define chunkmemset_4 chunkmemset_4_sse2
#define chunkmemset_8 chunkmemset_8_sse2
#define loadchunk loadchunk_sse2
#define storechunk storechunk_sse2
#define chunk_t chunk_sse2_t
#define GET_CHUNK_MAG GET_CHUNK_MAG_sse2
#include "arch/x86/chunkset_sse2.c"
#   include "zlib_undef.inl"

#include "arch/x86/compare256_sse2.c"
#include "arch/x86/slide_hash_sse2.c"
#include "arch/x86/adler32_ssse3.c"

ZLIB_UNTARGET_REGION
ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1,avx512f,avx512bw,avx512vl,vpclmulqdq")

#define X86_VPCLMULQDQ_CRC
#include "arch/x86/crc32_fold_vpclmulqdq.c"
#   include "zlib_undef.inl"

ZLIB_UNTARGET_REGION
ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1")

#define X86_PCLMULQDQ_CRC
#include "arch/x86/crc32_fold_pclmulqdq.c"
#   include "zlib_undef.inl"

ZLIB_UNTARGET_REGION
ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1,avx512f,avx512bw,avx512vl")

#define X86_AVX512
#define X86_AVX512_ADLER32
#include "arch/x86/adler32_avx512.c"
#   include "zlib_undef.inl"

ZLIB_UNTARGET_REGION
ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1,avx512f,avx512bw,avx512vl,avx512vnni")

#define X86_AVX512VNNI
#define X86_AVX512VNNI_ADLER32
#include "arch/x86/adler32_avx512_vnni.c"

ZLIB_UNTARGET_REGION
ZLIB_TARGET_REGION("bmi2,avx2,pclmul,sse4.1")

#include "functable.c"

#ifdef WITH_GZFILEOP
#undef GZIP
#include "gzlib.c"
#include "gzread.c"
#include "gzwrite.c"
#endif

#if defined(__clang__)
#pragma clang attribute pop
#endif
