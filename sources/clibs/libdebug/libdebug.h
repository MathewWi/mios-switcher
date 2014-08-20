#ifndef _LIBDEBUG_H_
#define _LIBDEBUG_H_
#include <time.h>
#define DEBUG_MESSAGE_SIZE 256
#define DEBUG_MESSAGES_COUNT 256
enum LOG_MESSAGES {
    DEBUG_LOG_MESSAGE=1,
    INFO_LOG_MESSAGE=2,
    WARNING_LOG_MESSAGE=4,
    ERROR_LOG_MESSAGE=8,
    SUCCESS_LOG_MESSAGE=16,
    ALL_LOG_MESSAGES=DEBUG_LOG_MESSAGE | INFO_LOG_MESSAGE | WARNING_LOG_MESSAGE | ERROR_LOG_MESSAGE | SUCCESS_LOG_MESSAGE
};
struct stDebugMessage {
    int intCode;
    enum LOG_MESSAGES MESSAGE_TYPE;
    char strMessage[DEBUG_MESSAGE_SIZE];
    char strSourceFilename[256];
    unsigned int intSourceLineNumber;
    time_t lngTime;
};
enum {
    LAST_DEBUG_MESSAGE_INDEX=DEBUG_MESSAGES_COUNT-1,
    DEBUG_MESSAGE_STRUCTURE_SIZE=sizeof(struct stDebugMessage)
};
#endif

