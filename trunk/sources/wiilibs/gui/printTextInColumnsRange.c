#include <string.h>
#include "../../clibs/libmath/isInRange.h"
#include "../../clibs/macros.h"
#include "../video/resetSavedPreviousCursorPosition.h"
#include "printLocatedText.h"
#include "printTextInColumnsRange.h"
//version finale
void printTextInColumnsRange(u8 chRow,u8 chColumn,u8 chMinColumn,u8 chMaxColumn,struct stConsoleCursorLocation *stTexteLocation,const char *strText) {
    if (chMinColumn>chMaxColumn) {
        SWAP(&chMinColumn,&chMaxColumn);
    }
    if (!isInRange(chColumn,(double) chMinColumn-strlen(strText)+1,chMaxColumn,true,true)) {
        if (chColumn>chMinColumn) {
            printLocatedText(chRow,chColumn,stTexteLocation,"%.*s",chMaxColumn-chColumn+1,strText);
        }
        else {
            printLocatedText(chRow,chColumn,stTexteLocation,"%.*s",chMaxColumn-chMinColumn+1,&strText[chMinColumn-chColumn]);
        }
        resetSavedPreviousCursorPosition();
    }
}
