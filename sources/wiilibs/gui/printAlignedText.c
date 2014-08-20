#include <string.h>
#include <stdlib.h>
#include "../../clibs/libmemory/freeRecursiveVector.h"
#include "../../clibs/libstring/getBreakStrings.h"
#include "../../clibs/libmath/isInRange.h"
#include "../../clibs/libgeometry/getPolyContainerPosition.h"
#include "../../clibs/macros.h"
#include "../video/resetSavedPreviousCursorPosition.h"
#include "printTextInColumnsRange.h"
#include "printLocatedText.h"
#include "printAlignedText.h"
//version finale
void printAlignedText(double dbHorizontalAlign,double dbVerticalAlign,u8 chMinRow,u8 chMinColumn,u8 chMaxRow,u8 chMaxColumn,bool blnMultiLine,bool blnHideOverflowText,struct stConsoleCursorLocation *stTexteLocation,const char *strText) {
unsigned int intBreakLinesCount,intTempValue;
char **strBreakLines=NULL;
double dbTextContainerX[2]={0,0},dbTextContainerY[2]={0,0};
    if (chMinColumn>chMaxColumn) {
        SWAP(&chMinColumn,&chMaxColumn);
    }
    if (chMinRow>chMaxRow) {
        SWAP(&chMinRow,&chMaxRow);
    }
    if (blnMultiLine) {
        intBreakLinesCount=chMaxRow-chMinRow+1;
        dbTextContainerX[1]=chMaxColumn-chMinColumn;
        if ((strBreakLines=getBreakStrings(strText,' ',dbTextContainerX[1]+1,&intBreakLinesCount))!=NULL) {
            if ((intTempValue=intBreakLinesCount)==1) {
                dbTextContainerX[1]=strlen(strText)-1;
            }
            dbTextContainerY[1]=intBreakLinesCount-1;
            dbHorizontalAlign=ROUND(getPolyContainerPosition(dbTextContainerX,2,chMinColumn,chMaxColumn,dbHorizontalAlign));
            dbVerticalAlign=ROUND(getPolyContainerPosition(dbTextContainerY,2,chMinRow,chMaxRow,dbVerticalAlign));
            if (blnHideOverflowText) {
                while ((intBreakLinesCount) && (!isInRange(dbVerticalAlign,chMinRow,chMaxRow,true,true))) {
                    printTextInColumnsRange(dbVerticalAlign,dbHorizontalAlign,chMinColumn,chMaxColumn,stTexteLocation,strText);
                    dbVerticalAlign++;
                    intBreakLinesCount--;
                }
            }
            else {
                while (intBreakLinesCount) {
                    printLocatedText(dbVerticalAlign,dbHorizontalAlign,stTexteLocation,"%s",strText);
                    resetSavedPreviousCursorPosition();
                    dbVerticalAlign++;
                    intBreakLinesCount--;
                }
            }
            freeRecursiveVector((void ***) &strBreakLines,intTempValue);
        }
    }
    else {
        dbTextContainerX[1]=strlen(strText)-1;
        dbHorizontalAlign=ROUND(getPolyContainerPosition(dbTextContainerX,2,chMinColumn,chMaxColumn,dbHorizontalAlign));
        dbVerticalAlign=ROUND(getPolyContainerPosition(dbTextContainerY,2,chMinRow,chMaxRow,dbVerticalAlign));
        if (blnHideOverflowText) {
            if (!isInRange(dbVerticalAlign,chMinRow,chMaxRow,true,true)) {
                printTextInColumnsRange(dbVerticalAlign,dbHorizontalAlign,chMinColumn,chMaxColumn,stTexteLocation,strText);
            }
        }
        else {
            printLocatedText(dbVerticalAlign,dbHorizontalAlign,stTexteLocation,"%s",strText);
            resetSavedPreviousCursorPosition();
        }
    }
}
