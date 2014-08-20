#ifndef _INITCONSOLE_H_
#define _INITCONSOLE_H_
#include <ogc/consol.h>
#include <ogc/gx_struct.h>
#include "video.h"
GXRModeObj *initConsole(enum CONSOLE_COLORS CONSOLE_COLOR,const char *strSplashScreenMessage,struct stVideoSettings *stConsoleParameters);
#endif
