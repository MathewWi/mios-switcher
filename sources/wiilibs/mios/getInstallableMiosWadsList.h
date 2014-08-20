#ifndef _GETINSTALLABLEMIOSWADSLIST_H_
#define _GETINSTALLABLEMIOSWADSLIST_H_
#include "../menu/menu.h"
#include "../titles/titles.h"
struct stListItem *getInstallableMiosWadsList(const char *strWadsFolder,struct stTitleInfos *stKnownMiosInfos,unsigned int intKnownMiosCount,struct stTitleInfos **stInstalledMiosInfos,unsigned char chInstalledMiosCount,unsigned int *intWadsCount);
#endif
