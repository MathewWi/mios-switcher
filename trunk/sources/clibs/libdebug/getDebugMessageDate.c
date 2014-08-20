#include "libdebug.h"
#include "getDebugMessageDate.h"
extern struct stDebugMessage stDebugMessages[DEBUG_MESSAGES_COUNT];
time_t *getDebugMessageDate(unsigned char chDebugMessageIndex) {
    return &stDebugMessages[chDebugMessageIndex].lngTime;
}
