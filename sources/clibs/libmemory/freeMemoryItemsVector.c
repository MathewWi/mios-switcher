#include <stdlib.h>
#include "freeVector.h"
#include "freeMemoryItemsVector.h"
//version finale
void freeMemoryItemsVector(void **varVector,unsigned int intVectorItemsCount,size_t intMemoryStepSize) {
    if (varVector!=NULL) {
        if (*varVector!=NULL) {
            while(intVectorItemsCount) {
                intVectorItemsCount--;
                freeVector((void **) ((void *) varVector+intVectorItemsCount*intMemoryStepSize));
            }
        }
    }
}
