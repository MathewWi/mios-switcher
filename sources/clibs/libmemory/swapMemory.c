#include <string.h>
#include <stdlib.h>
#include "reallocBuffer.h"
#include "freeVector.h"
#include "swapMemory.h"
void **swapMemory(void *varMemory0,void *varMemory1,size_t intMemorySize) {
static void *varSwapMemory=NULL;
static size_t intSwapMemorySize=0;
    if ((intMemorySize>intSwapMemorySize) || (varSwapMemory==NULL)) {
        if (reallocBuffer(&varSwapMemory,intMemorySize,0)==NULL) {
            freeVector(&varSwapMemory);
            intSwapMemorySize=0;
            return NULL;
        }
        else {
            intSwapMemorySize=intMemorySize;
        }
    }
    memcpy(varSwapMemory,varMemory0,intMemorySize);
    memcpy(varMemory0,varMemory1,intMemorySize);
    memcpy(varMemory1,varSwapMemory,intMemorySize);
    return &varSwapMemory;
}
