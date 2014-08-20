#include "libdebug.h"
extern struct stDebugMessage stDebugMessages[DEBUG_MESSAGES_COUNT];
char *getDebugMessage(unsigned char chDebugMessageIndex) {
    return stDebugMessages[chDebugMessageIndex].strMessage;
}
