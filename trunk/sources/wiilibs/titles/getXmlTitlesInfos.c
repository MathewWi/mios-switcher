#include <stdlib.h>
#include <mxml.h>
#include "../../clibs/libmemory/getDynamicMemory.h"
#include "../../clibs/libmemory/freeRecursiveVector.h"
#include "../../clibs/libstring/getSplitStrings.h"
#include "freeTitlesInfos.h"
#include "getXmlTitlesInfos.h"
//version finale
struct stTitleInfos *getXmlTitlesInfos(const char *strXmlTitlesInfos,unsigned int *intTitlesCount) {
struct stTitleInfos *varout=NULL;
unsigned int intXmlTitlesCount,intHashBytesCount;
mxml_node_t *pXml=NULL,*pXmlTitles=NULL,*pXmlTitle=NULL;
char **strHashBytesValues=NULL,*chUnexpectedChar;
    *intTitlesCount=0;
    if ((pXml=mxmlLoadString(NULL,strXmlTitlesInfos,MXML_NO_CALLBACK))) {
        if ((pXmlTitles=mxmlFindElement(pXml,pXml,"titles",NULL,NULL,MXML_DESCEND_FIRST))) {
            intXmlTitlesCount=atoi(mxmlElementGetAttr(pXmlTitles,"count"));
            if ((varout=getDynamicMemory(intXmlTitlesCount*TITLE_INFOS_STRUCTURE_SIZE))==NULL) {
                //TODO
            }
            else {
                for (pXmlTitle=mxmlFindElement(pXmlTitles,pXmlTitles,"title",NULL,NULL,MXML_DESCEND_FIRST);pXmlTitle!=NULL;pXmlTitle=mxmlFindElement(pXmlTitle,pXmlTitles,"title",NULL,NULL,MXML_NO_DESCEND)) {
                    if (*intTitlesCount<intXmlTitlesCount) {
                        intHashBytesCount=21;
                        if ((strHashBytesValues=getSplitStrings(mxmlElementGetAttr(pXmlTitle,"hash"),",",&intHashBytesCount))==NULL) {
                            //TODO
                        }
                        else {
                            if (intHashBytesCount==20) {
                                for (varout[*intTitlesCount].stIdentificationModule.intModuleIndex=0;varout[*intTitlesCount].stIdentificationModule.intModuleIndex<20;varout[*intTitlesCount].stIdentificationModule.intModuleIndex++) {
                                    varout[*intTitlesCount].stIdentificationModule.chModuleHash[varout[*intTitlesCount].stIdentificationModule.intModuleIndex]=strtoul(strHashBytesValues[varout[*intTitlesCount].stIdentificationModule.intModuleIndex],&chUnexpectedChar,16);
                                }
                                varout[*intTitlesCount].strTitleLabel=strdup(mxmlElementGetAttr(pXmlTitle,"name"));
                                varout[*intTitlesCount].intTitleId=strtoul(mxmlElementGetAttr(pXmlTitle,"titleid"),&chUnexpectedChar,16);
                                varout[*intTitlesCount].stIdentificationModule.intModuleIndex=atoi(mxmlElementGetAttr(pXmlTitle,"mid"));
                                varout[*intTitlesCount].strTitleInfos=strdup(mxmlElementGetAttr(pXmlTitle,"infos"));
                            }
                            else {
                                //TODO
                                freeRecursiveVector((void ***) &strHashBytesValues,intHashBytesCount);
                                goto FREEANDEXIT;
                            }
                            freeRecursiveVector((void ***) &strHashBytesValues,intHashBytesCount);
                        }
                        *intTitlesCount=*intTitlesCount+1;
                    }
                    else {
                        //TODO
                        goto FREEANDEXIT;
                    }
                }
            }
        }
    }
    EXITFUNCTION:
    return varout;
    FREEANDEXIT:
    freeTitlesInfos(&varout,*intTitlesCount);
    goto EXITFUNCTION;
}
