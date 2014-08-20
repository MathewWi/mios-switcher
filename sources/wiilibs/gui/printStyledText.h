#ifndef _PRINTSTYLEDTEXT_H_
#define _PRINTSTYLEDTEXT_H_
#include <gctypes.h>
#include "../video/video.h"
void printStyledText(u8 chRow,u8 chColumn,enum CONSOLE_FONT_COLORS FONT_BGCOLOR,enum CONSOLE_FONT_COLORS FONT_FGCOLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT,struct stConsoleCursorLocation *stTexteLocation,const char *strText);
#endif
