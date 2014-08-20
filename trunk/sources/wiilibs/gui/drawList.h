#ifndef _DRAWLIST_H_
#define _DRAWLIST_H_
#include <stddef.h>
#include <gctypes.h>
#include "../video/video.h"
#include "../menu/menu.h"
#include "gui.h"
void drawList(u8 chRow,u8 chColumn,unsigned char chFieldSize,enum CONSOLE_FONT_COLORS LIST_FONT_COLOR,enum CONSOLE_FONT_COLORS ACTIVE_ITEM_COLOR,struct stListItem *stListItems,unsigned int intListItemsCount,unsigned char chVisibleListItemsCount,size_t intListItemsHiddenPrefixSize,unsigned char chItemsInterlines,unsigned int intSelectedListItemIndex,const char *strPrependItemString,const char *strAppendItemString,signed char chMarkerOffset,struct stGuiList *stListSettings);
#endif
