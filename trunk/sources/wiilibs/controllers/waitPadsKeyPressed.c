#include <stdio.h>
#include <stdlib.h>
#include <ogc/pad.h>
#include "getPadsKeyPressed.h"
#include "waitPadsKeyPressed.h"
//version finale
s32 waitPadsKeyPressed(const char *strMessage,unsigned short int intWaitingTime) {
    printf("%s",strMessage);
    return getPadsKeyPressed(NULL,0,false,intWaitingTime,PAD_BUTTON_A);
}
