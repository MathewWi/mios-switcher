#include <stdlib.h>
#include <sys/time.h>
#include "initTimer.h"
//version finale
void initTimer(struct stTimer *stTimerSettings,unsigned short int intTimerInterval) {
    gettimeofday(&stTimerSettings->stTvStartTime,NULL);
    stTimerSettings->intInterval=intTimerInterval;
    stTimerSettings->blnRunning=true;
}
