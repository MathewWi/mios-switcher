#ifndef _PRINTLOCATEDTEXT_H_
#define _PRINTLOCATEDTEXT_H_
#include <gctypes.h>
#include "../video/video.h"
int printLocatedText(u8 chRow,u8 chColumn,struct stConsoleCursorLocation *stTexteLocation,const char *strTexteFormat,...);
#endif
