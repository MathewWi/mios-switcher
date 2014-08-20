#ifndef _PRINTALIGNEDTEXT_H_
#define _PRINTALIGNEDTEXT_H_
#include <gctypes.h>
#include "../video/video.h"
void printAlignedText(double dbHorizontalAlign,double dbVerticalAlign,u8 chMinRow,u8 chMinColumn,u8 chMaxRow,u8 chMaxColumn,bool blnMultiLine,bool blnHideOverflowText,struct stConsoleCursorLocation *stTexteLocation,const char *strText);
#endif
