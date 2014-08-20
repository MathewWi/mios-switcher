#ifndef _UPDATELOGMONITOR_H_
#define _UPDATELOGMONITOR_H_
#include <stdbool.h>
#include "../video/video.h"
#include "gui.h"
int updateLogMonitor(const char *strLogMessage,enum CONSOLE_FONT_COLORS FONT_FGCOLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT,unsigned char chNewMessageDelay,struct stLogMonitor *stLogMonitorSettings);
#endif
