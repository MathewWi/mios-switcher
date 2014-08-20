#include <stdlib.h>
#include "../../clibs/libmemory/getDynamicMemory.h"
#include "../../clibs/libmemory/freeVector.h"
//version finale
void *resizeTexture(void **imgRGBAData,unsigned int intWidth,unsigned int intHeight,unsigned int intNewWidth,unsigned int intNewHeight) {
double dbXScaleFactor,dbYScaleFactor,dbWeightingXFactor,dbWeightingYFactor,dbWeightingXFactor2,dbWeightingYFactor2;
void *varout=NULL;
unsigned char *pchRGBA[2],*pchComputedRGBA;
unsigned int intTempVar;
    if ((intNewWidth!=intWidth) || (intNewHeight!=intHeight)) {
        intTempVar=4*intNewWidth*intNewHeight;
        if ((varout=getDynamicMemory(intTempVar))!=NULL) {
            dbXScaleFactor=((double) (intWidth-1))/((double) intNewWidth);
            dbYScaleFactor=((double) (intHeight-1))/((double) intNewHeight);
            pchComputedRGBA=(unsigned char *) varout+intTempVar;
            intTempVar=intNewWidth;
            while (intNewHeight) {
                intNewHeight--;
                intNewWidth=intTempVar;
                while (intNewWidth) {
                    intNewWidth--;
                    dbWeightingXFactor=(unsigned int)(dbXScaleFactor*(double) intNewWidth);
                    dbWeightingYFactor=(unsigned int)(dbYScaleFactor*(double) intNewHeight);
                    pchRGBA[0]=(unsigned char *) *imgRGBAData+(unsigned int) ((dbWeightingYFactor*intWidth+dbWeightingXFactor)*4);
                    dbWeightingXFactor=(dbXScaleFactor*(double) intNewWidth)-dbWeightingXFactor;
                    dbWeightingYFactor=(dbYScaleFactor*(double) intNewHeight)-dbWeightingYFactor;
                    dbWeightingXFactor2=1-dbWeightingXFactor;
                    dbWeightingYFactor2=1-dbWeightingYFactor;
                    pchRGBA[1]=pchRGBA[0]+intWidth*4;
                    pchComputedRGBA=pchComputedRGBA-4;
                    pchComputedRGBA[0]=(unsigned char) (((double) pchRGBA[0][0])*dbWeightingXFactor2*dbWeightingYFactor2+((double) pchRGBA[0][4])*dbWeightingXFactor*dbWeightingYFactor2+((double) pchRGBA[1][0])*dbWeightingYFactor*dbWeightingXFactor2+((double) pchRGBA[1][4])*dbWeightingXFactor*dbWeightingYFactor);
                    pchComputedRGBA[1]=(unsigned char) (((double) pchRGBA[0][1])*dbWeightingXFactor2*dbWeightingYFactor2+((double) pchRGBA[0][5])*dbWeightingXFactor*dbWeightingYFactor2+((double) pchRGBA[1][1])*dbWeightingYFactor*dbWeightingXFactor2+((double) pchRGBA[1][5])*dbWeightingXFactor*dbWeightingYFactor);
                    pchComputedRGBA[2]=(unsigned char) (((double) pchRGBA[0][2])*dbWeightingXFactor2*dbWeightingYFactor2+((double) pchRGBA[0][6])*dbWeightingXFactor*dbWeightingYFactor2+((double) pchRGBA[1][2])*dbWeightingYFactor*dbWeightingXFactor2+((double) pchRGBA[1][6])*dbWeightingXFactor*dbWeightingYFactor);
                    //pchComputedRGBA[3]=(unsigned char) (((double) pchRGBA[0][3])*dbWeightingXFactor2*dbWeightingYFactor2+((double) pchRGBA[0][7])*dbWeightingXFactor*dbWeightingYFactor2+((double) pchRGBA[1][3])*dbWeightingYFactor*dbWeightingXFactor2+((double) pchRGBA[1][7])*dbWeightingXFactor*dbWeightingYFactor);
                    pchComputedRGBA[3]=255;
                }
            }
        }
        freeVector(imgRGBAData);
	}
	else {
        varout=*imgRGBAData;
	}
    return varout;
}
