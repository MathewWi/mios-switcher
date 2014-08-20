#ifndef _INSTALLWADTMDCONTENTS_H_
#define _INSTALLWADTMDCONTENTS_H_
#include <stdio.h>
#include <gctypes.h>
#include <ogc/es.h>
#include "wad.h"
s32 installWadTmdContents(FILE *fpwad,struct stWadMap *stWadFileMap,const signed_blob *sTmd,u32 intTmdSize,const signed_blob *sCerts,u32 intCertsSize,const signed_blob *sCrl,u32 intCrlsize);
#endif
