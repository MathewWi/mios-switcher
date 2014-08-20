#include "getListItemId.h"
unsigned char getBooleanListItemId(unsigned int *intBooleanOptionsSetting,int intBooleanOption,signed char chMoveStep) {
unsigned char varout;
    if ((varout=getListItemId((*intBooleanOptionsSetting & intBooleanOption)/intBooleanOption,chMoveStep,2))) {
        *intBooleanOptionsSetting=*intBooleanOptionsSetting | intBooleanOption;
    }
    else {
        *intBooleanOptionsSetting=*intBooleanOptionsSetting & ~intBooleanOption;
    }
    return varout;
}
