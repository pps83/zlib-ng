/* zutil_p.h -- Private inline functions used internally in zlib-ng
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#ifndef ZUTIL_P_H
#define ZUTIL_P_H

#include <stdlib.h>

/* Function to allocate 64-byte aligned memory */
static inline void *zng_alloc(size_t size) {
    uint8_t* align_buf = NULL;
    uint8_t* buf = (uint8_t*)malloc(size + 63 + sizeof(void**));
    if (buf)
    {
        align_buf = buf + 63 + sizeof(void**);
        align_buf -= (intptr_t)align_buf & 63;
        *((void**)(align_buf - sizeof(void**))) = buf;
    }
    return align_buf;
}

/* Function that can free aligned memory */
static inline void zng_free(void *ptr) {
    if (ptr)
        free(*(((void**)ptr) - 1));
}

#endif
