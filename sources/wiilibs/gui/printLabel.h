#ifndef _PRINTLABEL_H_
#define _PRINTLABEL_H_
#include <gctypes.h>
#include "../video/video.h"
void printLabel(u8 chRow,u8 chColumn,enum CONSOLE_FONT_COLORS FONT_BGCOLOR,enum CONSOLE_FONT_COLORS FONT_FGCOLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT,unsigned char chLabelSize,struct stConsoleCursorLocation *stConcatLabelLocation,const char *strLabel,const char *strOverflowString);
#endif
