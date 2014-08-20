#include <stdint.h>
#include "../clibs.h"
#include "libmemory.h"
#include "getMemoryItemSize.h"
//version finale
size_t getMemoryItemSize(int intItemSize) {
    if (intItemSize<1) {
        return POINTER_TYPE_SIZE;
    }
    else {
        switch (intItemSize) {
            case U8_MEMORY_ITEM:
            case S8_MEMORY_ITEM:
                return CHAR_TYPE_SIZE;
                break;
            case U16_MEMORY_ITEM:
            case S16_MEMORY_ITEM:
                return SHORTINT_TYPE_SIZE;
                break;
            case U32_MEMORY_ITEM:
            case S32_MEMORY_ITEM:
                return INT_TYPE_SIZE;
                break;
            case U64_MEMORY_ITEM:
            case S64_MEMORY_ITEM:
                return LONGINT_TYPE_SIZE;
                break;
            case FLOAT_MEMORY_ITEM:
                return FLOAT_TYPE_SIZE;
                break;
            case DOUBLE_MEMORY_ITEM:
                return DOUBLE_TYPE_SIZE;
                break;
        }
    }
    return intItemSize;
}
