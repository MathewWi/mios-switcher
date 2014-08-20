#include "../clibs.h"
#include "printJoinedArrayStringMemoryItems.h"
//version finale
unsigned int printJoinedArrayStringItems(const char **strItems,unsigned int *intItemsIndexes,unsigned int intItemsCount,const char *strBeforeItem,const char *strSeparator,const char *strAfterItem,const char *strJoin) {
    return printJoinedArrayStringMemoryItems(strItems,intItemsIndexes,intItemsCount,POINTER_TYPE_SIZE,strBeforeItem,strSeparator,strAfterItem,strJoin);
}
