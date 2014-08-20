#ifndef _SETWADFILEMAPFOOTER_H_
#define _SETWADFILEMAPFOOTER_H_
#if defined(_WIN64) || defined(_WIN32)
#include "../../clibs/libwii/libwii.h"
#else
#include <ogc/es.h>
#endif
#include <stdbool.h>
#include "wad.h"
bool setWadFileMapFooter(signed_blob *sTmd,struct stWadHeader *stWadTitleHeader,struct stWadMap *stWadFileMap);
#endif
