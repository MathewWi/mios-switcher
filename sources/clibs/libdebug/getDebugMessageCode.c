#include "libdebug.h"
extern struct stDebugMessage stDebugMessages[DEBUG_MESSAGES_COUNT];
int getDebugMessageCode(unsigned char chDebugMessageIndex) {
    return stDebugMessages[chDebugMessageIndex].intCode;
}
