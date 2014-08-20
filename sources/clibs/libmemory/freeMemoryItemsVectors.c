#include <stdarg.h>
#include "freeMemoryItemsVector.h"
#include "freeMemoryItemsVectors.h"
void freeMemoryItemsVectors(size_t intVectorItemsCount,size_t intMemoryStepSize,unsigned int intVectorsCount,...) {
va_list pArguments;
    va_start(pArguments,intVectorsCount);
    while (intVectorsCount) {
        intVectorsCount--;
        freeMemoryItemsVector(va_arg(pArguments,void **),intVectorItemsCount,intMemoryStepSize);
    }
    va_end(pArguments);
}
