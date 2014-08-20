#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../libfile/basename.h"
#include "setDebugMessage.h"
//version finale
extern struct stDebugMessage stDebugMessages[DEBUG_MESSAGES_COUNT];
unsigned char setDebugMessage(enum LOG_MESSAGES MESSAGE_TYPE,int intCode,const char *strSourceFilename,unsigned int intSourceLineNumber,const char *strFormat,...) {
va_list pArguments;
    memcpy(&stDebugMessages[0],&stDebugMessages[1],LAST_DEBUG_MESSAGE_INDEX*DEBUG_MESSAGE_STRUCTURE_SIZE);
    stDebugMessages[LAST_DEBUG_MESSAGE_INDEX].intCode=intCode;
    va_start(pArguments,strFormat);
    intCode=vsnprintf(stDebugMessages[LAST_DEBUG_MESSAGE_INDEX].strMessage,DEBUG_MESSAGE_SIZE,strFormat,pArguments);
    va_end(pArguments);
    stDebugMessages[LAST_DEBUG_MESSAGE_INDEX].intSourceLineNumber=intSourceLineNumber;
    strcpy(stDebugMessages[LAST_DEBUG_MESSAGE_INDEX].strSourceFilename,basename(strSourceFilename));
    stDebugMessages[LAST_DEBUG_MESSAGE_INDEX].lngTime=time(NULL);
    return intCode;
}
