#ifndef _DRAWLABEL_H_
#define _DRAWLABEL_H_
#include <gctypes.h>
#include "../video/video.h"
#include "gui.h"
void drawLabel(u8 chRow,u8 chColumn,enum CONSOLE_FONT_COLORS FONT_BGCOLOR,enum CONSOLE_FONT_COLORS FONT_FGCOLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT,const char *strLabelCaption,u8 chLabelSize,struct stLabel *stLabelSettings,struct stConsoleCursorLocation *stLabelCaptionLocation);
#endif
