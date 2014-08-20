#include "../../clibs/libmemory/freeVector.h"
#include "../../clibs/libmemory/freeMemoryItemsVectors.h"
#include "freeListItems.h"
void freeListItems(struct stListItem **stListItems,unsigned int intListItemsCount) {
    freeMemoryItemsVectors(intListItemsCount,LIST_ITEM_STRUCTURE_SIZE,2,(void **) &stListItems[0]->strLabel,&stListItems[0]->varMetaDatas);
    freeVector((void **) stListItems);
}
