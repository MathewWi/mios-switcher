#include "setMemoryPointerItem.h"
//version finale
void *setMemoryPointerItem(void **varPointer,const void *varPointerItem,size_t intMemorySize) {
    *varPointer=(void *) varPointerItem;
    return *varPointer;
}
