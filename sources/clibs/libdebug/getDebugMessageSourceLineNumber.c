#include "libdebug.h"
extern struct stDebugMessage stDebugMessages[DEBUG_MESSAGES_COUNT];
unsigned int getDebugMessageSourceLineNumber(unsigned char chDebugMessageIndex) {
    return stDebugMessages[chDebugMessageIndex].intSourceLineNumber;
}
