#ifndef _LIBMEMORY_H_
#define _LIBMEMORY_H_
#include <malloc.h>
#include "../macros.h"
#if defined(_WIN64) || defined(_WIN32)
#define GET_ALIGNED_MEMORY(m,s) malloc(CEIL((m),(s)))
#else
#define GET_ALIGNED_MEMORY(m,s) memalign((s),CEIL((m),(s)))
#endif
#define GET_MEMORY_CAST_VALUE(m,t) (*((t *) (m)))
#define SET_MEMORY_CAST_VALUE(m,t,v) *((t *) (m))=(v)
#define REALLOC_ALIGNED_BUFFER(m,s,b) realloc(*(m),((b))?CEIL((s),(b)):(s))
enum MEMORY_ITEM_TYPES {
    U8_MEMORY_ITEM=2147483647,
    S8_MEMORY_ITEM=2147483646,
    U16_MEMORY_ITEM=2147483645,
    S16_MEMORY_ITEM=2147483644,
    U32_MEMORY_ITEM=2147483643,
    S32_MEMORY_ITEM=2147483642,
    U64_MEMORY_ITEM=2147483641,
    S64_MEMORY_ITEM=2147483640,
    FLOAT_MEMORY_ITEM=2147483639,
    DOUBLE_MEMORY_ITEM=2147483638
};
#endif
