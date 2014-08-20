#include <stdio.h>
#include <stdlib.h>
#include "../../clibs/libarray/printJoinedArrayStringItems.h"
#include "../controllers/controllers.h"
#include "../video/saveCursorPosition.h"
#include "../video/getConsoleColumnsCount.h"
#include "../video/setCursorPosition.h"
#include "../controllers/getPadsKeyLabels.h"
#include "../video/resetSavedCursorPosition.h"
#include "addCommandsBarItem.h"
//version finale
void addCommandsBarItem(struct stCommandsBar *stCommandsBarSettings,s32 *intMappedPadKeys,unsigned char chMappedPadKeysCount,const char *strCommandText) {
char chColumnCounts,chPadsKeyLabels;
static char *strPadsKeyLabels[CONTROLLERS_COUNT];
    if (stCommandsBarSettings->chCommandItemsCount<stCommandsBarSettings->chCommandsCount) {
        saveCursorPosition();
        chColumnCounts=((getConsoleColumnsCount()-1)/2)-1;
        setCursorPosition(stCommandsBarSettings->stCommandsBarLocation.intRow+stCommandsBarSettings->chCommandItemsCount/2,stCommandsBarSettings->stCommandsBarLocation.intColumn+(stCommandsBarSettings->chCommandItemsCount % 2)*(2+chColumnCounts));
        while (chMappedPadKeysCount) {
            chMappedPadKeysCount--;
            chPadsKeyLabels=getPadsKeyLabels(intMappedPadKeys[chMappedPadKeysCount],strPadsKeyLabels);
            chColumnCounts=chColumnCounts-printJoinedArrayStringItems((const char **) strPadsKeyLabels,NULL,chPadsKeyLabels,"","","","/");
            if (chMappedPadKeysCount) {
                printf("|");
                chColumnCounts--;
            }
        }
        if (chColumnCounts>0) {
            printf("%-*.*s",(unsigned int) chColumnCounts,(unsigned int) chColumnCounts,strCommandText);
        }
        resetSavedCursorPosition();
        stCommandsBarSettings->chCommandItemsCount=stCommandsBarSettings->chCommandItemsCount+1;
    }
}
