#ifndef _LIBTOOLS_H_
#define _LIBTOOLS_H_
#include <stddef.h>
struct stAppArgument {
    const char *strArgumentSwitch;
    char *strArgumentValue;
};
enum METADATA_CHECKING_STATUS {
    MISSING_METADATA_STATUS=-1,
    MATCHING_METADATA_STATUS=0,
    NOTFOUND_METADATA_STATUS=1
};
struct stBytesPattern {
    unsigned char *chPattern;
    unsigned int intOffset;
    size_t intSize;
};
#endif
