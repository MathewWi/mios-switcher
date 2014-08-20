#include <stdlib.h>
#include "freeVector.h"
//version finale
void freeRecursiveVector(void ***varVector,unsigned int intVectorItemsCount) {
    if (varVector!=NULL) {
        if (*varVector!=NULL) {
            while (intVectorItemsCount) {
                intVectorItemsCount--;
                freeVector(*varVector+intVectorItemsCount);
            }
            freeVector((void **) varVector);
        }
    }
}
