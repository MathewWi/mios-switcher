#include <malloc.h>
#include <stdlib.h>
#include "getDynamicMemory.h"
//version finale
void *getDynamicMemory(size_t intMemorySize) {
    if (intMemorySize) {
        return malloc(intMemorySize);
    }
    else {
        return NULL;
    }
}
