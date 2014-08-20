#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "isExpiredTimer.h"
//version finale
bool isExpiredTimer(struct stTimer *stTimerSettings) {
struct timeval stTv;
bool varout=false;
    if (stTimerSettings->intInterval) {
        gettimeofday(&stTv,NULL);
        if ((varout=(((double) (stTv.tv_sec-stTimerSettings->stTvStartTime.tv_sec)*1000+(double) (stTv.tv_usec-stTimerSettings->stTvStartTime.tv_usec)/1000)>=stTimerSettings->intInterval))) {
            memcpy(&stTimerSettings->stTvStartTime,&stTv,sizeof(struct timeval));
        }
    }
    return varout;
}
