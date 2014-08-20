#ifndef _SETDEBUGMESSAGE_H_
#define _SETDEBUGMESSAGE_H_
#include "libdebug.h"
unsigned char setDebugMessage(enum LOG_MESSAGES MESSAGE_TYPE,int intCode,const char *strSourceFilename,unsigned int intSourceLineNumber,const char *strFormat,...);
#endif
