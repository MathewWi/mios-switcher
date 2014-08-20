#ifndef _SETSTATUSBAR_H_
#define _SETSTATUSBAR_H_
#include "gui.h"
#include "../video/video.h"
void setStatusBar(struct stCommandsBar *stCommandsBarSettings,enum CONSOLE_FONT_COLORS BGCOLOR,enum CONSOLE_FONT_COLORS FONT_COLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT,unsigned char intSleepTime,const char *strStatusText);
#endif
