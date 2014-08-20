#include <sys/types.h>
#include <sys/stat.h>
#include "isDirectory.h"
//version finale
bool isDirectory(const char *strDirectory) {
struct stat stFileInfos;
    return ((stat(strDirectory,&stFileInfos)==0) && ((stFileInfos.st_mode & S_IFDIR)!=0));
}
