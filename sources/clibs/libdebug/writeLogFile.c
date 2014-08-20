#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "getDebugMessage.h"
#include "getDebugMessageType.h"
#include "getDebugMessageDate.h"
#include "getDebugMessageCode.h"
#include "getDebugMessageSourceFilename.h"
#include "getDebugMessageSourceLineNumber.h"
#include "libdebug.h"
//version finale
void writeLogFile(const char *strFileName,int intLogMessageFilter) {
unsigned char i;
enum LOG_MESSAGES LOG_MESSAGE_TYPE;
FILE *fhLog;
char *strDebugMessage;
    if ((fhLog=fopen(strFileName,"w"))!=NULL) {
        for (i=0;i<DEBUG_MESSAGES_COUNT;i++) {
            strDebugMessage=getDebugMessage(i);
            if (*strDebugMessage) {
                LOG_MESSAGE_TYPE=getDebugMessageType(i);
                if ((intLogMessageFilter & LOG_MESSAGE_TYPE)) {
                    fprintf(fhLog,"[%.24s] %s%s (%d)|%s:%u\n",ctime(getDebugMessageDate(i)),(LOG_MESSAGE_TYPE==DEBUG_LOG_MESSAGE)?"DEBUG: ":(LOG_MESSAGE_TYPE==INFO_LOG_MESSAGE)?"INFO: ":(LOG_MESSAGE_TYPE==WARNING_LOG_MESSAGE)?"WARNING :":(LOG_MESSAGE_TYPE==ERROR_LOG_MESSAGE)?"ERROR :":(LOG_MESSAGE_TYPE==SUCCESS_LOG_MESSAGE)?"SUCCESS :":"",strDebugMessage,getDebugMessageCode(i),getDebugMessageSourceFilename(i),getDebugMessageSourceLineNumber(i));
                }
            }
        }
        fclose(fhLog);
    }
}
