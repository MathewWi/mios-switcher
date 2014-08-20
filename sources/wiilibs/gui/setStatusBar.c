#include <unistd.h>
#include "../video/getConsoleColumnsCount.h"
#include "printLabel.h"
#include "setStatusBar.h"
//version finale
void setStatusBar(struct stCommandsBar *stCommandsBarSettings,enum CONSOLE_FONT_COLORS BGCOLOR,enum CONSOLE_FONT_COLORS FONT_COLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT,unsigned char intSleepTime,const char *strStatusText) {
struct stConsoleCursorLocation stConcatLabelLocation;
    if (stCommandsBarSettings->stStatusBarLocation.intRow!=-1) {
        printLabel(stCommandsBarSettings->stStatusBarLocation.intRow,stCommandsBarSettings->stStatusBarLocation.intColumn,BGCOLOR,FONT_COLOR,FONT_WEIGHT,getConsoleColumnsCount()-1,&stConcatLabelLocation,strStatusText,"");
        sleep(intSleepTime);
    }
}
