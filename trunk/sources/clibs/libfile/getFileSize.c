#include <sys/types.h>
#include <sys/stat.h>
long getFileSize(const char *strFileName) {
struct stat stFileInfos;
    if (stat(strFileName,&stFileInfos)) {
        return -1;
    }
    return stFileInfos.st_size;
}
