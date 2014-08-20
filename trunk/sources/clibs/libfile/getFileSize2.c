#include "getFileSize2.h"
//version finale
long getFileSize2(FILE *fp) {
    if (fseek(fp,0,SEEK_END)) {
        return -1;
    }
    else {
        return ftell(fp);
    }
}
