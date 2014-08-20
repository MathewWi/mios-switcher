#ifndef _PRINTLISTITEM_H_
#define _PRINTLISTITEM_H_
#include <gctypes.h>
#include "../video/video.h"
void printListItem(u8 chRow,u8 chColumn,const char *strListLabel,unsigned int intCurrentItemId,unsigned int intListItemsCount,enum CONSOLE_FONT_COLORS HIGHLIGHT_ITEM_COLOR,const char *strPrependString,const char *strAppendString,unsigned char chFieldSize,const char *strItemValue,const char *strOverflowString);
#endif
