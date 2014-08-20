#ifndef _LIBTIME_H_
#define _LIBTIME_H_
#include <sys/time.h>
#include <stdbool.h>
struct stTimer {
    struct timeval stTvStartTime;
    unsigned short int intInterval;
    bool blnRunning;
};
#endif
