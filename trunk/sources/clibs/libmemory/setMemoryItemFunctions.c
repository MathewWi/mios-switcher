#include "getMemoryPointerItem.h"
#include "getPointerCmp.h"
#include "setMemoryPointerItem.h"
#include "getMemoryItem.h"
#include "getU8Cmp.h"
#include "setU8Item.h"
#include "getS8Cmp.h"
#include "setS8Item.h"
#include "getU16Cmp.h"
#include "setU16Item.h"
#include "getS16Cmp.h"
#include "setS16Item.h"
#include "getU32Cmp.h"
#include "setU32Item.h"
#include "getS32Cmp.h"
#include "setS32Item.h"
#include "getU64Cmp.h"
#include "setU64Item.h"
#include "getS64Cmp.h"
#include "setS64Item.h"
#include "getFloatCmp.h"
#include "setFloatItem.h"
#include "getDoubleCmp.h"
#include "setDoubleItem.h"
#include "setMemoryItem.h"
#include "getMemoryCmp.h"
#include "libmemory.h"
#include "setMemoryItemFunctions.h"
//version finale
void setMemoryItemFunctions(int intItemSize,void* (**varMemoryItem)(const void *,unsigned int,unsigned int),int (**intMemoryItemCmp)(const void *,const void *,size_t),void* (**varCurrentMemoryItem)(void **,const void *,size_t)) {
    switch (intItemSize) {
        case 0:
            *varMemoryItem=getMemoryPointerItem;
            *intMemoryItemCmp=getPointerCmp;
            *varCurrentMemoryItem=setMemoryPointerItem;
            break;
        case U8_MEMORY_ITEM:
            *varMemoryItem=getMemoryItem;
            *intMemoryItemCmp=getU8Cmp;
            *varCurrentMemoryItem=setU8Item;
            break;
        case S8_MEMORY_ITEM:
            *varMemoryItem=getMemoryItem;
            *intMemoryItemCmp=getS8Cmp;
            *varCurrentMemoryItem=setS8Item;
            break;
        case U16_MEMORY_ITEM:
            *varMemoryItem=getMemoryItem;
            *intMemoryItemCmp=getU16Cmp;
            *varCurrentMemoryItem=setU16Item;
            break;
        case S16_MEMORY_ITEM:
            *varMemoryItem=getMemoryItem;
            *intMemoryItemCmp=getS16Cmp;
            *varCurrentMemoryItem=setS16Item;
            break;
        case U32_MEMORY_ITEM:
            *varMemoryItem=getMemoryItem;
            *intMemoryItemCmp=getU32Cmp;
            *varCurrentMemoryItem=setU32Item;
            break;
        case S32_MEMORY_ITEM:
            *varMemoryItem=getMemoryItem;
            *intMemoryItemCmp=getS32Cmp;
            *varCurrentMemoryItem=setS32Item;
            break;
        case U64_MEMORY_ITEM:
            *varMemoryItem=getMemoryItem;
            *intMemoryItemCmp=getU64Cmp;
            *varCurrentMemoryItem=setU64Item;
            break;
        case S64_MEMORY_ITEM:
            *varMemoryItem=getMemoryItem;
            *intMemoryItemCmp=getS64Cmp;
            *varCurrentMemoryItem=setS64Item;
            break;
        case FLOAT_MEMORY_ITEM:
            *varMemoryItem=getMemoryItem;
            *intMemoryItemCmp=getFloatCmp;
            *varCurrentMemoryItem=setFloatItem;
            break;
        case DOUBLE_MEMORY_ITEM:
            *varMemoryItem=getMemoryItem;
            *intMemoryItemCmp=getDoubleCmp;
            *varCurrentMemoryItem=setDoubleItem;
            break;
        default:
            *varCurrentMemoryItem=setMemoryItem;
            *intMemoryItemCmp=getMemoryCmp;
            if (intItemSize>0) {
                *varMemoryItem=getMemoryItem;
            }
            else {
                *varMemoryItem=getMemoryPointerItem;
            }
            break;
    }
}
