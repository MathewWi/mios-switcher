#ifndef _PRINTTEXTINCOLUMNSRANGE_H_
#define _PRINTTEXTINCOLUMNSRANGE_H_
#include <gctypes.h>
#include "../video/video.h"
void printTextInColumnsRange(u8 chRow,u8 chColumn,u8 chMinColumn,u8 chMaxColumn,struct stConsoleCursorLocation *stTexteLocation,const char *strText);
#endif
