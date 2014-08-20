#include "../../clibs/macros.h"
//version finale
int getListItemId(unsigned int intCurrentItemId,int intMoveStep,unsigned int intListItemsCount) {
int intItemId=(int) intCurrentItemId+intMoveStep;
int intMaxItemId=MAX(intItemId,0);
    intItemId=(int) intListItemsCount-1;
    return MIN(intMaxItemId,intItemId);
}
