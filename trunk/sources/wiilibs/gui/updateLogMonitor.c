#include <stdio.h>
#include <unistd.h>
#include "../../clibs/libdebug/libdebug.h"
#include "../../clibs/libdebug/getDebugMessage.h"
#include "../../clibs/libdebug/setDebugMessage.h"
#include "../../clibs/macros.h"
#include "../video/getCursorPositions.h"
#include "../video/setFontFgColor.h"
#include "../video/resetPreviousFgColor.h"
#include "../video/getFgColorPattern.h"
#include "printLocatedText.h"
#include "getStylePatternsCharsCount.h"
#include "updateLogMonitor.h"
int updateLogMonitor(const char *strLogMessage,enum CONSOLE_FONT_COLORS FONT_FGCOLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT,unsigned char chNewMessageDelay,struct stLogMonitor *stLogMonitorSettings) {
int varout;
char *strDebugMessage;
    if (chNewMessageDelay) {
        usleep(chNewMessageDelay*1000);
        setDebugMessage(INFO_LOG_MESSAGE,0,__FILE__,__LINE__,"%s%s",getFgColorPattern(FONT_FGCOLOR,FONT_WEIGHT),strLogMessage);
        if ((stLogMonitorSettings->stCurrentCursorPositions.intRow=stLogMonitorSettings->stCurrentCursorPositions.intRow+1)>stLogMonitorSettings->chRowsCount) {
            for (varout=stLogMonitorSettings->chRow;varout<stLogMonitorSettings->chRowsCount;varout++) {
                strDebugMessage=getDebugMessage(LAST_DEBUG_MESSAGE_INDEX-stLogMonitorSettings->chRowsCount+varout);
                stLogMonitorSettings->stCurrentCursorPositions.intColumn=stLogMonitorSettings->chColumnsCount+getStylePatternsCharsCount(strDebugMessage);
                printLocatedText(varout,stLogMonitorSettings->chColumn,&stLogMonitorSettings->stCurrentCursorPositions,"%-*.*s",stLogMonitorSettings->stCurrentCursorPositions.intColumn,stLogMonitorSettings->stCurrentCursorPositions.intColumn,strDebugMessage);
            }
            printLocatedText(stLogMonitorSettings->chRowsCount,stLogMonitorSettings->chColumn,&stLogMonitorSettings->stCurrentCursorPositions,"%*s",stLogMonitorSettings->chColumnsCount,"");
        }
        stLogMonitorSettings->stCurrentCursorPositions.intColumn=stLogMonitorSettings->chColumn;
    }
    else {
        strDebugMessage=getDebugMessage(LAST_DEBUG_MESSAGE_INDEX);
        snprintf(strDebugMessage,DEBUG_MESSAGE_SIZE,"%s%s%s",strDebugMessage,getFgColorPattern(FONT_FGCOLOR,FONT_WEIGHT),strLogMessage);
    }
    setFontFgColor(FONT_FGCOLOR,FONT_WEIGHT);
    varout=printLocatedText(stLogMonitorSettings->stCurrentCursorPositions.intRow,stLogMonitorSettings->stCurrentCursorPositions.intColumn,&stLogMonitorSettings->stCurrentCursorPositions,"%.*s",stLogMonitorSettings->chColumn+stLogMonitorSettings->chColumnsCount-stLogMonitorSettings->stCurrentCursorPositions.intColumn,strLogMessage);
    resetPreviousFgColor();
    getCursorPositions(&stLogMonitorSettings->stCurrentCursorPositions.intColumn,&stLogMonitorSettings->stCurrentCursorPositions.intRow);
    return varout;
}
