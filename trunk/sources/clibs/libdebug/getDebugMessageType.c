#include "getDebugMessageType.h"
//version finale
extern struct stDebugMessage stDebugMessages[DEBUG_MESSAGES_COUNT];
enum LOG_MESSAGES getDebugMessageType(unsigned char chDebugMessageIndex) {
    return stDebugMessages[chDebugMessageIndex].MESSAGE_TYPE;
}
