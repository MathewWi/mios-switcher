#include <string.h>
#include "setMemoryItem.h"
//version finale
void *setMemoryItem(void **varMemory,const void *varItem,size_t intMemorySize) {
    return memcpy(*varMemory,varItem,intMemorySize);
}
