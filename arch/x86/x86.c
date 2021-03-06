/*
 * x86 feature check
 *
 * Copyright (C) 2013 Intel Corporation. All rights reserved.
 * Author:
 *  Jim Kukunas
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#include "../../zutil.h"

#ifdef _MSC_VER
#  include <intrin.h>
#else
// Newer versions of GCC and clang come with cpuid.h
#  include <cpuid.h>
#endif

ZLIB_INTERNAL int x86_cpu_has_avx2 = 0;
ZLIB_INTERNAL int x86_cpu_has_sse42 = 0;
ZLIB_INTERNAL int x86_cpu_has_pclmulqdq = 0;

static void cpuid(int info, unsigned* eax, unsigned* ebx, unsigned* ecx, unsigned* edx) {
#ifdef _MSC_VER
    int registers[4];
    __cpuid(registers, info);

    *eax = registers[0];
    *ebx = registers[1];
    *ecx = registers[2];
    *edx = registers[3];
#else
    __cpuid(info, *eax, *ebx, *ecx, *edx);
#endif
}

static void cpuidex(int info, int subinfo, unsigned* eax, unsigned* ebx, unsigned* ecx, unsigned* edx) {
#ifdef _MSC_VER
    int registers[4];
    __cpuidex(registers, info, subinfo);

    *eax = registers[0];
    *ebx = registers[1];
    *ecx = registers[2];
    *edx = registers[3];
#else
    __cpuid_count(info, subinfo, *eax, *ebx, *ecx, *edx);
#endif
}

void ZLIB_INTERNAL x86_check_features(void) {
    unsigned eax, ebx, ecx, edx;
    unsigned maxbasic;

    cpuid(0, &maxbasic, &ebx, &ecx, &edx);

    cpuid(1 /*CPU_PROCINFO_AND_FEATUREBITS*/, &eax, &ebx, &ecx, &edx);

    x86_cpu_has_sse42 = ecx & 0x100000;
    x86_cpu_has_pclmulqdq = ecx & 0x2;

    if (maxbasic >= 7) {
        cpuidex(7, 0, &eax, &ebx, &ecx, &edx);

        // check AVX2 bit
        x86_cpu_has_avx2 = ebx & 0x20;
    }
}
