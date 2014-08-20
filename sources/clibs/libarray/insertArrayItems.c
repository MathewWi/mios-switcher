#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../libmemory/reallocBuffer.h"
#include "../libmemory/getMemoryItemSize.h"
#include "../macros.h"
#include "insertArrayItems.h"
//version finale
unsigned int insertArrayItems(void **varItems,unsigned int *intItemsCount,unsigned int intInsertIndex,size_t intItemSize,int intInsertedItemsCount,...) {
unsigned int varout,intAbsInsertedItemsCount=abs(intInsertedItemsCount);
va_list pArguments;
    intItemSize=getMemoryItemSize(intItemSize);
    if (reallocBuffer(varItems,(*intItemsCount+intAbsInsertedItemsCount)*intItemSize,0)==NULL) {
        return *intItemsCount+1;
    }
    else {
        if ((varout=MIN(*intItemsCount,intInsertIndex))<*intItemsCount) {
            memmove(*varItems+(varout+intAbsInsertedItemsCount)*intItemSize,*varItems+varout*intItemSize,intAbsInsertedItemsCount*intItemSize);
        }
        va_start(pArguments,intInsertedItemsCount);
        if (intInsertedItemsCount<0) {
            memcpy(*varItems+varout*intItemSize,va_arg(pArguments,const void *),intAbsInsertedItemsCount*intItemSize);
        }
        else {
            for (intInsertedItemsCount=0;intInsertedItemsCount<intAbsInsertedItemsCount;intInsertedItemsCount++) {
                memcpy(*varItems+(varout+intInsertedItemsCount)*intItemSize,va_arg(pArguments,const void *),intItemSize);
            }
        }
        va_end(pArguments);
        *intItemsCount=*intItemsCount+intAbsInsertedItemsCount;
    }
    return varout;
}
