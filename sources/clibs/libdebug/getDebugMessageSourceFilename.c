#include "libdebug.h"
extern struct stDebugMessage stDebugMessages[DEBUG_MESSAGES_COUNT];
char *getDebugMessageSourceFilename(unsigned char chDebugMessageIndex) {
    return stDebugMessages[chDebugMessageIndex].strSourceFilename;
}
