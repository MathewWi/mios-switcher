#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gctypes.h>
#include <ogc/color.h>
#include <ogc/pad.h>
#include <ogc/system.h>
#include <ogc/gx_struct.h>
#include <ogc/video.h>
#include <ogc/video_types.h>
#include <ogc/ios.h>
#include <ogc/wiilaunch.h>
#include <wiiuse/wpad.h>
#include "clibs/macros.h"
#include "clibs/clibs.h"
#include "clibs/libarray/getArrayMemoryItemIndex.h"
#include "clibs/libgeometry/libgeometry.h"
#include "clibs/libtools/printBreakLines.h"
#include "clibs/libtools/getFormattedString.h"
#include "clibs/libtools/getAppArguments.h"
#include "clibs/libtools/libtools.h"
#include "clibs/libstring/truncateString.h"
#include "clibs/libfile/dirname.h"
#include "clibs/libfile/getFileContent.h"
#include "clibs/libfile/writeBinaryFile.h"
#include "clibs/libfile/getFolderContent.h"
#include "clibs/libfile/getFilenameExtension.h"
#include "clibs/libfile/isValidFilePath.h"
#include "clibs/libfile/basename.h"
#include "clibs/libmemory/freeVector.h"
#include "clibs/libmemory/getClonedBuffer.h"
#include "clibs/libmemory/reallocBuffer.h"
#include "clibs/libmemory/dynamicMemory.h"
#include "wiilibs/images/images.h"
#include "wiilibs/video/video.h"
#include "wiilibs/video/clearConsole.h"
#include "wiilibs/video/getConsoleColumnsCount.h"
#include "wiilibs/video/initConsole.h"
#include "wiilibs/video/setFrameBuffer.h"
#include "wiilibs/video/drawFramebuffer.h"
#include "wiilibs/video/getFgColorPattern.h"
#include "wiilibs/gui/gui.h"
#include "wiilibs/gui/printStyledText.h"
#include "wiilibs/gui/drawCommandsBar.h"
#include "wiilibs/gui/addCommandsBarItem.h"
#include "wiilibs/gui/setStatusBar.h"
#include "wiilibs/gui/drawLabel.h"
#include "wiilibs/gui/drawList.h"
#include "wiilibs/gui/destroyList.h"
#include "wiilibs/gui/initMenuItems.h"
#include "wiilibs/gui/printListItem.h"
#include "wiilibs/gui/selectListItem.h"
#include "wiilibs/gui/markListItem.h"
#include "wiilibs/gui/markAllListItems.h"
#include "wiilibs/gui/initLogMonitor.h"
#include "wiilibs/gui/updateLogMonitor.h"
#include "wiilibs/titles/titles.h"
#include "wiilibs/titles/getXmlTitlesInfos.h"
#include "wiilibs/titles/freeTitlesInfos.h"
#include "wiilibs/titles/getNextFreeTitleId.h"
#include "wiilibs/nand/haveNandAccess.h"
#include "wiilibs/filesystems/filesystems.h"
#include "wiilibs/filesystems/mountNandFs.h"
#include "wiilibs/filesystems/mountFatDevice.h"
#include "wiilibs/filesystems/unmountFatDevice.h"
#include "wiilibs/filesystems/unmountNandFs.h"
#include "wiilibs/filesystems/getDeviceLabel.h"
#include "wiilibs/filesystems/getWiiFileDevice.h"
#include "wiilibs/system/onResetButtonDown.h"
#include "wiilibs/system/setCacheDataSegment.h"
#include "wiilibs/system/system.h"
#include "wiilibs/controllers/waitPadsKeyPressed.h"
#include "wiilibs/controllers/getPadsKeyPressed.h"
#include "wiilibs/mios/getInstalledMiosInfos.h"
#include "wiilibs/mios/getInstalledCompatibleMios.h"
#include "wiilibs/mios/mios.h"
#include "wiilibs/mios/activateMios.h"
#include "wiilibs/mios/cleanMiosSlots.h"
#include "wiilibs/mios/getInstalledMiosList.h"
#include "wiilibs/mios/uninstallAlternativeMios.h"
#include "wiilibs/mios/getInstallableMiosWadsList.h"
#include "wiilibs/mios/moveMiosNandItems.h"
#include "wiilibs/mios/setMiosHomebrewMode.h"
#include "wiilibs/menu/getListItemId.h"
#include "wiilibs/menu/getBooleanListItemId.h"
#include "wiilibs/menu/freeListItems.h"
#include "wiilibs/menu/menu.h"
#include "wiilibs/ios/loadCios.h"
#include "wiilibs/dvd/resetDvdDrive.h"
#include "wiilibs/dvd/dvd.h"
#include "wiilibs/games/getGcGamesList.h"
#include "wiilibs/games/getGamesIniSettings.h"
#include "wiilibs/games/getGamesSettings.h"
#include "wiilibs/games/setGameVideoSettings.h"
#include "wiilibs/games/getGameVideoMode.h"
#include "wiilibs/games/setGameSystemSettings.h"
#include "wiilibs/games/games.h"
#include "wiilibs/wad/installWadFile.h"
#include "wiilibs/wad/wad.h"
#include "wiilibs/dol/dol.h"
#include "wiilibs/dol/getDolsList.h"
#include "MIOSINFOS_xml.h"
#include "miosswbg_png.h"
#include "leds_png.h"
#include "miosload_bin.h"
#include "swiss_bin.h"
#include "main.h"
#ifdef DEBUG_FILE
#include "clibs/libdebug/writeLogFile.h"
#include "clibs/libdebug/libdebug.h"
#endif
#define AUTOBOOT_LAUNCHER "LAUNCHER"
#define AUTOBOOT_SWITCHER "SWITCHER"
#define AUTOBOOT_INSTALLER "INSTALLER"
#define AUTOBOOT_UNINSTALLER "UNINSTALLER"
const char *strGcLanguages[7]={"English","German","French","Spanish","Italian","Dutch","Console"},*strGcVideoModes[8]={"Auto","PAL50","PAL60","NTSC480i","NTSC480p","PAL480p","NTSC480p (patched)","PAL480p (patched)"},*strGcForceVideos[3]={"Auto","Force","None"},*strBooleanOptions[2]={"Off","On"};
unsigned char initMiosConfigurationMenu(struct stTitleInfos *stMiosInfos,struct stGameConfig *stGameSettings,struct stLabel *stLabelsSettings) {
    if (strncmp(strstr(stMiosInfos->strTitleInfos,MIOS_INFOS_FAMILY_ID_LABEL)+strlen(MIOS_INFOS_FAMILY_ID_LABEL)+1,DIOS_MIOS_FAMILY_ID,2)) {
        initMenuItems(stLabelsSettings,11);
        return 0;
    }
    else {
        printListItem(stLabelsSettings[0].stLabelLocation.intRow,stLabelsSettings[0].stLabelLocation.intColumn,"",stGameSettings->GAME_LANGUAGE,STATIC_ARRAY_SIZE(strGcLanguages),CONSOLE_FONT_BLACK,"","",stLabelsSettings[0].chLabelSize,strGcLanguages[stGameSettings->GAME_LANGUAGE],"");
        printListItem(stLabelsSettings[1].stLabelLocation.intRow,stLabelsSettings[1].stLabelLocation.intColumn,"",stGameSettings->VIDEO_MODE,STATIC_ARRAY_SIZE(strGcVideoModes),CONSOLE_FONT_BLACK,"","",stLabelsSettings[1].chLabelSize,strGcVideoModes[stGameSettings->VIDEO_MODE],"");
        stGameSettings->stDiosMiosConfig.intMagicbytes=stGameSettings->stDiosMiosConfig.intVideoMode>>16;
        printListItem(stLabelsSettings[2].stLabelLocation.intRow,stLabelsSettings[2].stLabelLocation.intColumn,"",stGameSettings->stDiosMiosConfig.intMagicbytes,STATIC_ARRAY_SIZE(strGcForceVideos),CONSOLE_FONT_BLACK,"","",stLabelsSettings[2].chLabelSize,strGcForceVideos[stGameSettings->stDiosMiosConfig.intMagicbytes],"");
        stGameSettings->stDiosMiosConfig.intMagicbytes=(stGameSettings->stDiosMiosConfig.intOptions & DIOS_MIOS_NODISC)/DIOS_MIOS_NODISC;
        printListItem(stLabelsSettings[3].stLabelLocation.intRow,stLabelsSettings[3].stLabelLocation.intColumn,"",stGameSettings->stDiosMiosConfig.intMagicbytes,2,CONSOLE_FONT_BLACK,"","",stLabelsSettings[3].chLabelSize,strBooleanOptions[stGameSettings->stDiosMiosConfig.intMagicbytes],"");
        stGameSettings->stDiosMiosConfig.intMagicbytes=(stGameSettings->stDiosMiosConfig.intOptions & DIOS_MIOS_WIDESCREEN)/DIOS_MIOS_WIDESCREEN;
        printListItem(stLabelsSettings[4].stLabelLocation.intRow,stLabelsSettings[4].stLabelLocation.intColumn,"",stGameSettings->stDiosMiosConfig.intMagicbytes,2,CONSOLE_FONT_BLACK,"","",stLabelsSettings[4].chLabelSize,strBooleanOptions[stGameSettings->stDiosMiosConfig.intMagicbytes],"");
        stGameSettings->stDiosMiosConfig.intMagicbytes=(unsigned int) (stGameSettings->blnDriveReset);
        printListItem(stLabelsSettings[5].stLabelLocation.intRow,stLabelsSettings[5].stLabelLocation.intColumn,"",stGameSettings->stDiosMiosConfig.intMagicbytes,2,CONSOLE_FONT_BLACK,"","",stLabelsSettings[5].chLabelSize,strBooleanOptions[stGameSettings->stDiosMiosConfig.intMagicbytes],"");
        stGameSettings->stDiosMiosConfig.intMagicbytes=(unsigned int) (stGameSettings->blnNtscjPatch);
        printListItem(stLabelsSettings[6].stLabelLocation.intRow,stLabelsSettings[6].stLabelLocation.intColumn,"",stGameSettings->stDiosMiosConfig.intMagicbytes,2,CONSOLE_FONT_BLACK,"","",stLabelsSettings[6].chLabelSize,strBooleanOptions[stGameSettings->stDiosMiosConfig.intMagicbytes],"");
        stGameSettings->stDiosMiosConfig.intMagicbytes=(stGameSettings->stDiosMiosConfig.intOptions & DIOS_MIOS_LED)/DIOS_MIOS_LED;
        printListItem(stLabelsSettings[7].stLabelLocation.intRow,stLabelsSettings[7].stLabelLocation.intColumn,"",stGameSettings->stDiosMiosConfig.intMagicbytes,2,CONSOLE_FONT_BLACK,"","",stLabelsSettings[7].chLabelSize,strBooleanOptions[stGameSettings->stDiosMiosConfig.intMagicbytes],"");
        stGameSettings->stDiosMiosConfig.intMagicbytes=(stGameSettings->stDiosMiosConfig.intOptions & DIOS_MIOS_PADHOOK)/DIOS_MIOS_PADHOOK;
        printListItem(stLabelsSettings[8].stLabelLocation.intRow,stLabelsSettings[8].stLabelLocation.intColumn,"",stGameSettings->stDiosMiosConfig.intMagicbytes,2,CONSOLE_FONT_BLACK,"","",stLabelsSettings[8].chLabelSize,strBooleanOptions[stGameSettings->stDiosMiosConfig.intMagicbytes],"");
        stGameSettings->stDiosMiosConfig.intMagicbytes=(stGameSettings->stDiosMiosConfig.intOptions & DIOS_MIOS_CHEATS)/DIOS_MIOS_CHEATS;
        printListItem(stLabelsSettings[9].stLabelLocation.intRow,stLabelsSettings[9].stLabelLocation.intColumn,"",stGameSettings->stDiosMiosConfig.intMagicbytes,2,CONSOLE_FONT_BLACK,"","",stLabelsSettings[9].chLabelSize,strBooleanOptions[stGameSettings->stDiosMiosConfig.intMagicbytes],"");
        stGameSettings->stDiosMiosConfig.intMagicbytes=(stGameSettings->stDiosMiosConfig.intOptions & DIOS_MIOS_NMM)/DIOS_MIOS_NMM;
        printListItem(stLabelsSettings[10].stLabelLocation.intRow,stLabelsSettings[10].stLabelLocation.intColumn,"",stGameSettings->stDiosMiosConfig.intMagicbytes,2,CONSOLE_FONT_BLACK,"","",stLabelsSettings[10].chLabelSize,strBooleanOptions[stGameSettings->stDiosMiosConfig.intMagicbytes],"");
        return 11;
    }
}
unsigned char initGameConfigurationMenu(struct stGameConfig *stGameSettings,enum STORAGE_DEVICES STORAGE_DEVICE,struct stTitleInfos **stInstalledMiosInfos,unsigned char chInstalledMiosCount,struct stTitleInfos ****stInstalledCompatibleMiosInfos,unsigned char *chInstalledCompatibleMiosCount,struct stLabel *stLabelsSettings,struct stConsoleCursorLocation *stLabelsLocation) {
    if ((*stInstalledCompatibleMiosInfos=getInstalledCompatibleMios(stGameSettings->strDiscID,STORAGE_DEVICE,stInstalledMiosInfos,chInstalledMiosCount,chInstalledCompatibleMiosCount))==NULL) {
        printListItem(stLabelsSettings[1].stLabelLocation.intRow,stLabelsSettings[1].stLabelLocation.intColumn,"",0,1,CONSOLE_FONT_BLACK,"","",stLabelsSettings[1].chLabelSize,"No compatible MIOS detected","");
        initMenuItems(&stLabelsSettings[2],12);
        return 1;
    }
    else {
        stGameSettings->stDiosMiosConfig.intCfgVersion=*chInstalledCompatibleMiosCount-1;
        while ((stGameSettings->stDiosMiosConfig.intCfgVersion) && (memcmp((*(*stInstalledCompatibleMiosInfos)[stGameSettings->stDiosMiosConfig.intCfgVersion])->stIdentificationModule.chModuleHash,stGameSettings->stIosIdentificationModule.chModuleHash,20))) {
            stGameSettings->stDiosMiosConfig.intCfgVersion=stGameSettings->stDiosMiosConfig.intCfgVersion-1;
        }
        memcpy(&stGameSettings->stIosIdentificationModule,&(*(*stInstalledCompatibleMiosInfos)[stGameSettings->stDiosMiosConfig.intCfgVersion])->stIdentificationModule,TITLE_IDENTIFICATION_MODULE_STRUCTURE_SIZE);
        printListItem(stLabelsSettings[1].stLabelLocation.intRow,stLabelsSettings[1].stLabelLocation.intColumn,"",stGameSettings->stDiosMiosConfig.intCfgVersion,*chInstalledCompatibleMiosCount,CONSOLE_FONT_BLACK,"","",stLabelsSettings[1].chLabelSize,(*(*stInstalledCompatibleMiosInfos)[stGameSettings->stDiosMiosConfig.intCfgVersion])->strTitleLabel,"...");
        return 2+initMiosConfigurationMenu((*(*stInstalledCompatibleMiosInfos)[stGameSettings->stDiosMiosConfig.intCfgVersion]),stGameSettings,&stLabelsSettings[2]);
    }
}
int main(int intArgumentsCount,char **strArguments) {
s32 intExpectedPadsKeys[]={PAD_BUTTON_UP,PAD_BUTTON_DOWN,PAD_BUTTON_LEFT,PAD_BUTTON_RIGHT,PAD_BUTTON_A,PAD_BUTTON_START,PAD_TRIGGER_L,PAD_TRIGGER_R,PAD_BUTTON_B},pressed=0;
int intConsoleColumnsCount=236;
struct stConsoleCursorLocation stLabelsLocation[13];
bool blnTryAhbProt=true;
char strFormattedMessage[1024];
struct stCommandsBar stCommandsBarSettings;
struct stTitleInfos **stInstalledMiosInfos=NULL,*stKnownMiosInfos=NULL,***stInstalledCompatibleMiosInfos;
unsigned char chInstalledMiosCount,chInstalledCompatibleMiosCount;
struct stVideoSettings stVideoParameters={(const void *) miosswbg_png,124,104,506,306,1,1,ALIGN_CENTER,ALIGN_MIDDLE,0,0,{{NULL,{{{leds_png,0,0,28,28},{2,144}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}}}},{NULL,{{{leds_png,0,28,28,28},{2,184}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}}}},{NULL,{{{leds_png,0,56,28,28},{2,224}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}},{{NULL,0,0,0,0},{0,0}}}}}};
struct stLabel stLabelsSettings[13]={{0,{stVideoParameters.intBgLeft,stVideoParameters.intBgTop}},{0,{0,0}},{0,{0,0}},{0,{0,0}},{0,{0,0}},{0,{0,0}},{0,{0,0}},{0,{0,0}},{0,{0,0}},{0,{0,0}},{0,{0,0}},{0,{0,0}},{0,{0,0}}};
struct stTextureSettings stSettingsScreenTextures[1]={{{leds_png,0,84,28,28},{2,264}}};
struct stAppArgument stAppArguments[5]={{"--ios=",NULL},{"--resolution=",NULL},{"--autoboot=",NULL},{"--wadsfolder=",NULL},{"--dolsfolder=",NULL}};
struct stDvdDiscInfos *stGcGamesInfos=NULL;
struct stGameConfig *stGamesIniSettings=NULL,**stGamesSettings=NULL,stDefaultGameConfig={{0,0,0,0,0,0,0},{DIOS_MIOS_MAGICWORD,0,DIOS_MIOS_VIDEO_AUTO,0,"",""},{0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},AUTO_VIDEO_MODE,SRAM_GC_CONSOLE_LANGUAGE,false,false};
unsigned int intGamesSettingsCount=0;
enum STORAGE_DEVICES FAT_DEVICE;
struct stLogMonitor stLogMonitorSettings;
struct stGuiList stListSettings={0,0,0,NULL,NULL,0,0,0,0,NULL,NULL,0,0,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_FGCOLOR};
GXRModeObj *objRenderSettings;
    if (getAppArguments(&strArguments[1],intArgumentsCount-1,stAppArguments,STATIC_ARRAY_SIZE(stAppArguments))) {
        if (stAppArguments[0].strArgumentValue!=NULL) {
            intConsoleColumnsCount=atoi(stAppArguments[0].strArgumentValue);
            blnTryAhbProt=false;
        }
        if (stAppArguments[1].strArgumentValue!=NULL) {
            if (strlen(stAppArguments[1].strArgumentValue)==7) {
                stAppArguments[1].strArgumentValue[3]=0;
                stVideoParameters.dbBgImgXScaleFactor=(double) atoi(stAppArguments[1].strArgumentValue)/(double) PNG_WIDTH(stVideoParameters.imgBgData);
                stVideoParameters.dbBgImgYScaleFactor=(double) atoi(stAppArguments[1].strArgumentValue+4)/(double) PNG_HEIGHT(stVideoParameters.imgBgData);
                stVideoParameters.dbBgImgXScaleFactor=MAX(stVideoParameters.dbBgImgXScaleFactor,1);
                stVideoParameters.dbBgImgYScaleFactor=MAX(stVideoParameters.dbBgImgYScaleFactor,1);
            }
        }
        if (stAppArguments[3].strArgumentValue!=NULL) {
            if ((*stAppArguments[3].strArgumentValue!='/') || (!isValidFilePath(stAppArguments[3].strArgumentValue))) {
                stAppArguments[3].strArgumentValue=NULL;
            }
            else {
                stCommandsBarSettings.chCommandsCount=strlen(stAppArguments[3].strArgumentValue)-1;
                if (stAppArguments[3].strArgumentValue[stCommandsBarSettings.chCommandsCount]=='/') {
                    stAppArguments[3].strArgumentValue[stCommandsBarSettings.chCommandsCount]=0;
                }
            }
        }
        if (stAppArguments[4].strArgumentValue!=NULL) {
            if ((*stAppArguments[4].strArgumentValue!='/') || (!isValidFilePath(stAppArguments[4].strArgumentValue))) {
                stAppArguments[4].strArgumentValue=NULL;
            }
            else {
                stCommandsBarSettings.chCommandsCount=strlen(stAppArguments[4].strArgumentValue)-1;
                if (stAppArguments[4].strArgumentValue[stCommandsBarSettings.chCommandsCount]=='/') {
                    stAppArguments[4].strArgumentValue[stCommandsBarSettings.chCommandsCount]=0;
                }
            }
        }
    }
    objRenderSettings=initConsole(GUI_BACKGROUND_COLOR,"Loading, please wait...",&stVideoParameters);
    loadCios(blnTryAhbProt,intConsoleColumnsCount);
    if (mountNandFs()) {
        if (haveNandAccess()) {
            intConsoleColumnsCount=getConsoleColumnsCount()-1;
            if (stAppArguments[2].strArgumentValue==NULL) {
                clearConsole();
                printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"[*] ABOUT MIOS SWITCHER\n");
                printf("Description: Multi MIOS manager\n");
                printf("Source: http://code.google.com/p/mios-switcher/\n");
                printf("Website: http://www.wii-addict.fr\n\n");
                printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"[*] DISCLAIMER\n");
                printBreakLines(' ',intConsoleColumnsCount,"THIS PACKAGE COMES WITH ABSOLUTELY NO WARRANTY, NEITHER STATED NOR IMPLIED. NO ONE BUT YOURSELF IS TO BE HELD RESPONSIBLE FOR ANY DAMAGE THIS MAY CAUSE TO YOUR NINTENDO WII CONSOLE! USE ON YOUR OWN RISK!");
                printf("\n\n");
                drawCommandsBar(0,true,&stCommandsBarSettings);
                setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Current IOS: %d v%d",IOS_GetVersion(),IOS_GetRevision()));
                VIDEO_WaitVSync();
            }
            else {
                if (!strcmp(stAppArguments[2].strArgumentValue,AUTOBOOT_LAUNCHER)) {
                    pressed=PAD_BUTTON_B;
                }
                else if (!strcmp(stAppArguments[2].strArgumentValue,AUTOBOOT_SWITCHER)) {
                    pressed=PAD_BUTTON_A;
                }
                else if (!strcmp(stAppArguments[2].strArgumentValue,AUTOBOOT_INSTALLER)) {
                    pressed=PAD_TRIGGER_R;
                }
                else if (!strcmp(stAppArguments[2].strArgumentValue,AUTOBOOT_UNINSTALLER)) {
                    pressed=PAD_TRIGGER_L;
                }
                else {
                    stAppArguments[2].strArgumentValue=NULL;
                    pressed=PAD_BUTTON_LEFT;
                }
                pressed=-1*pressed;
            }
            SYS_SetResetCallback(onResetButtonDown);
            PAD_Init();
            WPAD_Init();
            switch(getWiiFileDevice(strArguments[0])) {
                case SD_STORAGE_DEVICE:
                    FAT_DEVICE=mountFatDevice(4,SD_STORAGE_DEVICE,USB_STORAGE_DEVICE,SDGECKOA_STORAGE_DEVICE,SDGECKOB_STORAGE_DEVICE);
                    blnTryAhbProt=(FAT_DEVICE==SD_STORAGE_DEVICE);
                    break;
                case SDGECKOA_STORAGE_DEVICE:
                    FAT_DEVICE=mountFatDevice(4,SDGECKOA_STORAGE_DEVICE,SD_STORAGE_DEVICE,USB_STORAGE_DEVICE,SDGECKOB_STORAGE_DEVICE);
                    blnTryAhbProt=(FAT_DEVICE==SDGECKOA_STORAGE_DEVICE);
                    break;
                case SDGECKOB_STORAGE_DEVICE:
                    FAT_DEVICE=mountFatDevice(4,SDGECKOB_STORAGE_DEVICE,SD_STORAGE_DEVICE,USB_STORAGE_DEVICE,SDGECKOA_STORAGE_DEVICE);
                    blnTryAhbProt=(FAT_DEVICE==SDGECKOB_STORAGE_DEVICE);
                    break;
                case USB_STORAGE_DEVICE:
                    FAT_DEVICE=mountFatDevice(4,USB_STORAGE_DEVICE,SD_STORAGE_DEVICE,SDGECKOA_STORAGE_DEVICE,SDGECKOB_STORAGE_DEVICE);
                    blnTryAhbProt=(FAT_DEVICE==USB_STORAGE_DEVICE);
                    break;
                default:
                    FAT_DEVICE=mountFatDevice(4,SD_STORAGE_DEVICE,USB_STORAGE_DEVICE,SDGECKOA_STORAGE_DEVICE,SDGECKOB_STORAGE_DEVICE);
                    blnTryAhbProt=false;
            }
            stAppArguments[0].strArgumentValue=(char *) MIOSINFOS_xml;
            if (FAT_DEVICE) {
                if (stAppArguments[3].strArgumentValue==NULL) {
                    stAppArguments[3].strArgumentValue=strdup(getFormattedString(strFormattedMessage,"%s:%s",getDeviceLabel(FAT_DEVICE),WADS_FOLDER_PATH));
                }
                else {
                    stAppArguments[3].strArgumentValue=getFormattedString(strFormattedMessage,"%s:%s",getDeviceLabel(FAT_DEVICE),stAppArguments[3].strArgumentValue);
                    dynamicMemory((void **) &stAppArguments[3].strArgumentValue,strlen(stAppArguments[3].strArgumentValue)+1,0);
                }
                if (stAppArguments[4].strArgumentValue==NULL) {
                    stAppArguments[4].strArgumentValue=strdup(getFormattedString(strFormattedMessage,"%s:/",getDeviceLabel(FAT_DEVICE)));
                }
                else {
                    stAppArguments[4].strArgumentValue=getFormattedString(strFormattedMessage,"%s:%s",getDeviceLabel(FAT_DEVICE),stAppArguments[4].strArgumentValue);
                    dynamicMemory((void **) &stAppArguments[4].strArgumentValue,strlen(stAppArguments[4].strArgumentValue)+1,0);
                }
                if (blnTryAhbProt) {
                    stAppArguments[0].strArgumentValue=NULL;
                    if ((stAppArguments[0].strArgumentValue=getFileContent(getFormattedString(strFormattedMessage,"%s/MIOSINFOS.xml",dirname(strArguments[0])),(size_t *) &intArgumentsCount,0))==NULL) {
                        stAppArguments[0].strArgumentValue=(char *) MIOSINFOS_xml;
                    }
                    stGamesIniSettings=getGamesIniSettings(getFormattedString(strFormattedMessage,"%s/mios-switcher.ini",strArguments[0]),&intGamesSettingsCount);
                }
            }
            if ((stKnownMiosInfos=getXmlTitlesInfos(stAppArguments[0].strArgumentValue,(unsigned int *) &intArgumentsCount))!=NULL) {
                if (((pressed<0)?true:waitPadsKeyPressed("Press any button to continue...\n",60000))) {
                    setFrameBuffer(objRenderSettings,stVideoParameters.stFrameBuffers[1].frameBuffer);
                    stVideoParameters.intBgLeft=stLabelsSettings[0].stLabelLocation.intColumn;
                    stVideoParameters.intBgTop=stLabelsSettings[0].stLabelLocation.intRow;
                    drawFramebuffer(stVideoParameters.imgBgData,stSettingsScreenTextures,STATIC_ARRAY_SIZE(stSettingsScreenTextures),GUI_BACKGROUND_COLOR,&stVideoParameters.intBgLeft,&stVideoParameters.intBgTop,&stVideoParameters.dbBgImgXScaleFactor,&stVideoParameters.dbBgImgYScaleFactor,objRenderSettings,stVideoParameters.stFrameBuffers[0].frameBuffer);
                    while (pressed!=PAD_BUTTON_START) {
                        stInstalledMiosInfos=getInstalledMiosInfos(&chInstalledMiosCount,stKnownMiosInfos,intArgumentsCount);
                        if (stAppArguments[2].strArgumentValue==NULL) {
                            clearConsole();
                            setFrameBuffer(objRenderSettings,stVideoParameters.stFrameBuffers[1].frameBuffer);
                            printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"[*] MIOS TASKS\n");
                            printf("MIOS switcher: activate an alternative MIOS.\n");
                            printf("MIOS uninstaller: uninstall the 'alternative MIOS'.\n");
                            printf("MIOS installer: install multiple MIOS.\n");
                            printf("MIOS launcher: launch GC games.\n");
                            printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"\n\n[*] NOTES\n");
                            printf("Active MIOS: %s\n",chInstalledMiosCount?stInstalledMiosInfos[0]->strTitleLabel:"");
                            printf("Alternative MIOS: %u\n",chInstalledMiosCount?chInstalledMiosCount-1:0);
                            drawCommandsBar(5,true,&stCommandsBarSettings);
                            addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[4],1,": MIOS switcher");
                            addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[7],1,": MIOS installer");
                            addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[8],1,": MIOS launcher");
                            addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[6],1,": MIOS uninstaller");
                            addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[5],1,": Exit");
                            setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Current IOS: %d v%d",IOS_GetVersion(),IOS_GetRevision()));
                            VIDEO_WaitVSync();
                            pressed=0;
                        }
                        while ((pressed!=PAD_BUTTON_A) && (pressed!=PAD_BUTTON_B) && (pressed!=PAD_TRIGGER_R) && (pressed!=PAD_TRIGGER_L) && (pressed!=PAD_BUTTON_START)) {
                            if ((pressed=(pressed<0)?-1*pressed:getPadsKeyPressed(&intExpectedPadsKeys[4],5,true,0,0))) {
                                stAppArguments[2].strArgumentValue=NULL;
                                switch (pressed) {
                                    case PAD_BUTTON_A:
                                        clearConsole();
                                        setFrameBuffer(objRenderSettings,stVideoParameters.stFrameBuffers[2].frameBuffer);
                                        printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"[*] MIOS SWITCHER\n");
                                        drawLabel(-1,-1,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,"Select MIOS ",intConsoleColumnsCount-13,&stLabelsSettings[0],&stLabelsLocation[0]);
                                        printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"\n\n[*] NOTES\n");
                                        printf("DIOS MIOS: GC games from an USB device or retail discs.\n");
                                        printf("DIOS MIOS Lite: GC games from a SD card or retail discs.\n");
                                        printf("MIOS: GC games from retail discs.\n");
                                        printf("Waninkoko cMIOS: GC games from DVD-R or retail discs.\n");
                                        printBreakLines(' ',intConsoleColumnsCount,"Wiigator cMIOS: GC games from DVD-R or retail discs and homebrew support.\n");
                                        printBreakLines(' ',intConsoleColumnsCount,"Quadforce: triforce arcade games Mario Kart GP, Mario Kart GP 2 and F-Zero AX from an USB device or a SD card.");
                                        printf("\n");
                                        drawCommandsBar(3,true,&stCommandsBarSettings);
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[4],1,": Activate MIOS");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[5],1,": Exit");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[2],2,": MIOS selection");
                                        setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Current IOS: %d v%d",IOS_GetVersion(),IOS_GetRevision()));
                                        VIDEO_WaitVSync();
                                        if (chInstalledMiosCount>1) {
                                            chInstalledMiosCount--;
                                            pressed=0;
                                            stSettingsScreenTextures[0].stTileTextureSettings.intTileTop=0;
                                            while ((pressed!=PAD_BUTTON_START) && (pressed!=PAD_BUTTON_A)) {
                                                printListItem(stLabelsSettings[0].stLabelLocation.intRow,stLabelsSettings[0].stLabelLocation.intColumn,"",stSettingsScreenTextures[0].stTileTextureSettings.intTileTop,chInstalledMiosCount,CONSOLE_FONT_BLACK,"","",stLabelsSettings[0].chLabelSize,stInstalledMiosInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop+1]->strTitleLabel,"...");
                                                if ((pressed=getPadsKeyPressed(&intExpectedPadsKeys[2],4,true,0,0))) {
                                                    switch(pressed) {
                                                        case PAD_BUTTON_RIGHT:
                                                            stSettingsScreenTextures[0].stTileTextureSettings.intTileTop=getListItemId(stSettingsScreenTextures[0].stTileTextureSettings.intTileTop,1,chInstalledMiosCount);
                                                            break;
                                                        case PAD_BUTTON_LEFT:
                                                            stSettingsScreenTextures[0].stTileTextureSettings.intTileTop=getListItemId(stSettingsScreenTextures[0].stTileTextureSettings.intTileTop,-1,chInstalledMiosCount);
                                                            break;
                                                        case PAD_BUTTON_A:
                                                            clearConsole();
                                                            setFrameBuffer(objRenderSettings,stVideoParameters.stFrameBuffers[0].frameBuffer);
                                                            printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"[*] MIOS SWITCHER DETAILS\n");
                                                            drawCommandsBar(0,true,&stCommandsBarSettings);
                                                            setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Current IOS: %d v%d",IOS_GetVersion(),IOS_GetRevision()));
                                                            stSettingsScreenTextures[0].stTileTextureSettings.intTileTop++;
                                                            stCommandsBarSettings.chCommandsCount=intConsoleColumnsCount-7;
                                                            initLogMonitor(1,0,stCommandsBarSettings.stStatusBarLocation.intRow-2,intConsoleColumnsCount,false,&stLogMonitorSettings);
                                                            updateLogMonitor(getFormattedString(strFormattedMessage,"%*s [NOTE]",stCommandsBarSettings.chCommandsCount-updateLogMonitor(getFormattedString(strFormattedMessage,"> %s <-> %s",stInstalledMiosInfos[0]->strTitleLabel,stInstalledMiosInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop]->strTitleLabel),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                            updateLogMonitor(getFormattedString(strFormattedMessage,"%*s ",stCommandsBarSettings.chCommandsCount-updateLogMonitor(getFormattedString(strFormattedMessage,"> /title/00000001/00000101 <-> /title/00000001/%08x",MIOS_MINOR_TID+stSettingsScreenTextures[0].stTileTextureSettings.intTileTop),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                            VIDEO_WaitVSync();
                                                            if (activateMios(stSettingsScreenTextures[0].stTileTextureSettings.intTileTop)) {
                                                                updateLogMonitor("[",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                updateLogMonitor("DONE",CONSOLE_FONT_GREEN,CONSOLE_FONT_BOLD,0,&stLogMonitorSettings);
                                                                updateLogMonitor("]",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_GREEN,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,3,getFormattedString(strFormattedMessage,"%s activation completed",stInstalledMiosInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop]->strTitleLabel));
                                                            }
                                                            else {
                                                                updateLogMonitor("[",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                updateLogMonitor("FAIL",CONSOLE_FONT_RED,CONSOLE_FONT_BOLD,0,&stLogMonitorSettings);
                                                                updateLogMonitor("]",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_RED,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,getFormattedString(strFormattedMessage,"%s activation failed",stInstalledMiosInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop]->strTitleLabel));
                                                            }
                                                            break;
                                                        default:
                                                            break;
                                                    }
                                                }
                                                else {
                                                    pressed=PAD_BUTTON_START;
                                                }
                                            }
                                        }
                                        else {
                                            setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_MAGENTA,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"No alternative MIOS detected");
                                        }
                                        break;
                                    case PAD_TRIGGER_L:
                                        clearConsole();
                                        setFrameBuffer(objRenderSettings,stVideoParameters.stFrameBuffers[2].frameBuffer);
                                        printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"[*] MIOS UNINSTALLER\n");
                                        drawCommandsBar(0,true,&stCommandsBarSettings);
                                        setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Current IOS: %d v%d",IOS_GetVersion(),IOS_GetRevision()));
                                        drawCommandsBar(8,true,&stCommandsBarSettings);
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[0],2,": Navigation");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[8],1,": (Un)select MIOS");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[6],1,": Previous page");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[2],1,": Unselect all MIOS");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[7],1,": Next page");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[3],1,": Select all MIOS");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[5],1,": Exit");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[4],1,": Uninstall MIOS");
                                        setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Current IOS: %d v%d",IOS_GetVersion(),IOS_GetRevision()));
                                        VIDEO_WaitVSync();
                                        if ((stListSettings.stListItems=getInstalledMiosList(stInstalledMiosInfos,chInstalledMiosCount))!=NULL) {
                                            drawList(1,0,intConsoleColumnsCount,DEFAULT_FONT_FGCOLOR,CONSOLE_FONT_CYAN,stListSettings.stListItems,chInstalledMiosCount,stCommandsBarSettings.stCommandsBarLocation.intRow-2,0,1,0,"[ ] ","",-3,&stListSettings);
                                            stLabelsSettings[0].stLabelLocation.intColumn=LIST_TOTAL_PAGES_COUNT(stListSettings.chVisibleListItemsCount,stListSettings.intListItemsCount);
                                            setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Page 1 of %u",stLabelsSettings[0].stLabelLocation.intColumn));
                                            pressed=0;
                                            stLabelsSettings[0].stLabelLocation.intRow=0;
                                            while ((pressed!=PAD_BUTTON_START) && (pressed!=PAD_BUTTON_A)) {
                                                if ((pressed=getPadsKeyPressed(&intExpectedPadsKeys[0],9,true,0,0))) {
                                                    switch(pressed) {
                                                        case PAD_BUTTON_UP:
                                                            selectListItem(&stListSettings,stListSettings.intSelectedListItemIndex-1);
                                                            break;
                                                        case PAD_BUTTON_DOWN:
                                                            selectListItem(&stListSettings,stListSettings.intSelectedListItemIndex+1);
                                                            break;
                                                        case PAD_BUTTON_LEFT:
                                                            markAllListItems(&stListSettings,' ',DEFAULT_FONT_FGCOLOR);
                                                            stLabelsSettings[0].stLabelLocation.intRow=0;
                                                            break;
                                                        case PAD_BUTTON_RIGHT:
                                                            markAllListItems(&stListSettings,254,DEFAULT_FONT_FGCOLOR);
                                                            stLabelsSettings[0].stLabelLocation.intRow=stListSettings.intListItemsCount;
                                                            break;
                                                        case PAD_BUTTON_A:
                                                            clearConsole();
                                                            setFrameBuffer(objRenderSettings,stVideoParameters.stFrameBuffers[0].frameBuffer);
                                                            printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"[*] MIOS UNINSTALLER DETAILS\n");
                                                            drawCommandsBar(0,true,&stCommandsBarSettings);
                                                            setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Current IOS: %d v%d",IOS_GetVersion(),IOS_GetRevision()));
                                                            VIDEO_WaitVSync();
                                                            if (stLabelsSettings[0].stLabelLocation.intRow) {
                                                                stLabelsSettings[0].stLabelLocation.intColumn=0;
                                                                stCommandsBarSettings.chCommandItemsCount=intConsoleColumnsCount-9;
                                                                initLogMonitor(1,0,stCommandsBarSettings.stStatusBarLocation.intRow-2,intConsoleColumnsCount,false,&stLogMonitorSettings);
                                                                stCommandsBarSettings.chCommandsCount=stListSettings.intListItemsCount;
                                                                while (stCommandsBarSettings.chCommandsCount) {
                                                                    setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Uninstalling MIOS (%d|%d)...",stLabelsSettings[0].stLabelLocation.intColumn+1,stLabelsSettings[0].stLabelLocation.intRow));
                                                                    stCommandsBarSettings.chCommandsCount--;
                                                                    if (stListSettings.stListItems[stCommandsBarSettings.chCommandsCount].blnMarked) {
                                                                        updateLogMonitor(getFormattedString(strFormattedMessage,"> %-*s ",stCommandsBarSettings.chCommandItemsCount,stListSettings.stListItems[stCommandsBarSettings.chCommandsCount].strLabel),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings);
                                                                        if (uninstallAlternativeMios(stCommandsBarSettings.chCommandsCount,stInstalledMiosInfos,&chInstalledMiosCount)) {
                                                                            updateLogMonitor("[",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                            updateLogMonitor("DONE",CONSOLE_FONT_GREEN,CONSOLE_FONT_BOLD,0,&stLogMonitorSettings);
                                                                            updateLogMonitor("]",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                        }
                                                                        else {
                                                                            updateLogMonitor("[",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                            updateLogMonitor("FAIL",CONSOLE_FONT_RED,CONSOLE_FONT_BOLD,0,&stLogMonitorSettings);
                                                                            updateLogMonitor("]",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                            setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_RED,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"MIOS uninstallation error");
                                                                            break;
                                                                        }
                                                                        stLabelsSettings[0].stLabelLocation.intColumn=stLabelsSettings[0].stLabelLocation.intColumn+1;
                                                                    }
                                                                }
                                                                if (stLabelsSettings[0].stLabelLocation.intColumn==stLabelsSettings[0].stLabelLocation.intRow) {
                                                                    setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_GREEN,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,3,"Uninstallation completed");
                                                                }
                                                                else {
                                                                    cleanMiosSlots();
                                                                }
                                                            }
                                                            else {
                                                                setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_MAGENTA,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"No MIOS selected");
                                                            }
                                                            break;
                                                        case PAD_TRIGGER_L:
                                                            selectListItem(&stListSettings,LIST_PAGE_START_ITEM_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)-stListSettings.chVisibleListItemsCount);
                                                            setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Page %u of %u",LIST_PAGE_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)+1,stLabelsSettings[0].stLabelLocation.intColumn));
                                                            break;
                                                        case PAD_TRIGGER_R:
                                                            selectListItem(&stListSettings,LIST_PAGE_START_ITEM_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)+stListSettings.chVisibleListItemsCount);
                                                            setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Page %u of %u",LIST_PAGE_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)+1,stLabelsSettings[0].stLabelLocation.intColumn));
                                                            break;
                                                        case PAD_BUTTON_B:
                                                            if (stListSettings.stListItems[stListSettings.intSelectedListItemIndex].blnMarked) {
                                                                stLabelsSettings[0].stLabelLocation.intRow=stLabelsSettings[0].stLabelLocation.intRow-1;
                                                                *strFormattedMessage=' ';
                                                            }
                                                            else {
                                                                stLabelsSettings[0].stLabelLocation.intRow=stLabelsSettings[0].stLabelLocation.intRow+1;
                                                                *strFormattedMessage=254;
                                                            }
                                                            markListItem(&stListSettings,stListSettings.intSelectedListItemIndex,*strFormattedMessage,DEFAULT_FONT_FGCOLOR);
                                                            break;
                                                    }
                                                }
                                                else {
                                                    pressed=PAD_BUTTON_START;
                                                }
                                            }
                                            freeVector((void **) &stListSettings.stListItems);
                                            destroyList(&stListSettings,false);
                                        }
                                        else {
                                            setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_MAGENTA,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"No MIOS installed");
                                        }
                                        break;
                                    case PAD_TRIGGER_R:
                                        clearConsole();
                                        setFrameBuffer(objRenderSettings,stVideoParameters.stFrameBuffers[2].frameBuffer);
                                        printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"[*] MIOS INSTALLER\n");
                                        drawCommandsBar(8,true,&stCommandsBarSettings);
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[0],2,": Navigation");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[8],1,": (Un)select WAD");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[6],1,": Previous page");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[2],1,": Unselect all WADs");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[7],1,": Next page");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[3],1,": Select all WADs");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[5],1,": Exit");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[4],1,": Install WAD(s)");
                                        setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Current IOS: %d v%d",IOS_GetVersion(),IOS_GetRevision()));
                                        VIDEO_WaitVSync();
                                        if (FAT_DEVICE) {
                                            if ((stListSettings.stListItems=getInstallableMiosWadsList(stAppArguments[3].strArgumentValue,stKnownMiosInfos,intArgumentsCount,stInstalledMiosInfos,chInstalledMiosCount,&stListSettings.intListItemsCount))==NULL) {
                                                setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_MAGENTA,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,getFormattedString(strFormattedMessage,"No new MIOS WADs found in %s folder",stAppArguments[3].strArgumentValue));
                                            }
                                            else {
                                                drawList(1,0,intConsoleColumnsCount,DEFAULT_FONT_FGCOLOR,CONSOLE_FONT_CYAN,stListSettings.stListItems,stListSettings.intListItemsCount,stCommandsBarSettings.stCommandsBarLocation.intRow-2,strlen(stAppArguments[3].strArgumentValue)+1,1,0,"[ ] ","",-3,&stListSettings);
                                                stLabelsSettings[0].stLabelLocation.intColumn=LIST_TOTAL_PAGES_COUNT(stListSettings.chVisibleListItemsCount,stListSettings.intListItemsCount);
                                                setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Page 1 of %u",stLabelsSettings[0].stLabelLocation.intColumn));
                                                pressed=0;
                                                stLabelsSettings[0].stLabelLocation.intRow=0;
                                                while ((pressed!=PAD_BUTTON_START) && (pressed!=PAD_BUTTON_A)) {
                                                    if ((pressed=getPadsKeyPressed(&intExpectedPadsKeys[0],9,true,0,0))) {
                                                        switch(pressed) {
                                                            case PAD_BUTTON_UP:
                                                                selectListItem(&stListSettings,stListSettings.intSelectedListItemIndex-1);
                                                                break;
                                                            case PAD_BUTTON_DOWN:
                                                                selectListItem(&stListSettings,stListSettings.intSelectedListItemIndex+1);
                                                                break;
                                                            case PAD_BUTTON_LEFT:
                                                                markAllListItems(&stListSettings,' ',DEFAULT_FONT_FGCOLOR);
                                                                stLabelsSettings[0].stLabelLocation.intRow=0;
                                                                break;
                                                            case PAD_BUTTON_RIGHT:
                                                                markAllListItems(&stListSettings,254,DEFAULT_FONT_FGCOLOR);
                                                                stLabelsSettings[0].stLabelLocation.intRow=stListSettings.intListItemsCount;
                                                                break;
                                                            case PAD_BUTTON_A:
                                                                clearConsole();
                                                                setFrameBuffer(objRenderSettings,stVideoParameters.stFrameBuffers[0].frameBuffer);
                                                                printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"[*] MIOS INSTALLER DETAILS\n");
                                                                drawCommandsBar(0,true,&stCommandsBarSettings);
                                                                setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Current IOS: %d v%d",IOS_GetVersion(),IOS_GetRevision()));
                                                                VIDEO_WaitVSync();
                                                                if (stLabelsSettings[0].stLabelLocation.intRow) {
                                                                    stLabelsSettings[0].stLabelLocation.intColumn=0;
                                                                    stCommandsBarSettings.chCommandItemsCount=intConsoleColumnsCount-9;
                                                                    initLogMonitor(1,0,stCommandsBarSettings.stStatusBarLocation.intRow-2,intConsoleColumnsCount,false,&stLogMonitorSettings);
                                                                    for (stCommandsBarSettings.chCommandsCount=0;stCommandsBarSettings.chCommandsCount<stListSettings.intListItemsCount;stCommandsBarSettings.chCommandsCount++) {
                                                                        setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Installing selected MIOS WADs (%d|%d)...",stLabelsSettings[0].stLabelLocation.intColumn+1,stLabelsSettings[0].stLabelLocation.intRow));
                                                                        if (stListSettings.stListItems[stCommandsBarSettings.chCommandsCount].blnMarked) {
                                                                            updateLogMonitor("> ",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings);
                                                                            updateLogMonitor(getFormattedString(strFormattedMessage,"%*s ",stCommandsBarSettings.chCommandItemsCount-updateLogMonitor(truncateString("...",stCommandsBarSettings.chCommandItemsCount,strcpy(strFormattedMessage,basename(stListSettings.stListItems[stCommandsBarSettings.chCommandsCount].strLabel))),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                            if (moveMiosNandItems(getNextFreeTitleId(MIOS_TID)-MIOS_TID)) {
                                                                                if (installWadFile(stListSettings.stListItems[stCommandsBarSettings.chCommandsCount].strLabel)<0) {
                                                                                    updateLogMonitor("[",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                    updateLogMonitor("FAIL",CONSOLE_FONT_RED,CONSOLE_FONT_BOLD,0,&stLogMonitorSettings);
                                                                                    updateLogMonitor("]",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                    setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_RED,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"WAD installation error");
                                                                                    break;
                                                                                }
                                                                                else {
                                                                                    updateLogMonitor("[",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                    updateLogMonitor("DONE",CONSOLE_FONT_GREEN,CONSOLE_FONT_BOLD,0,&stLogMonitorSettings);
                                                                                    updateLogMonitor("]",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                }
                                                                            }
                                                                            else {
                                                                                updateLogMonitor("[",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                updateLogMonitor("SKIP",CONSOLE_FONT_RED,CONSOLE_FONT_BOLD,0,&stLogMonitorSettings);
                                                                                updateLogMonitor("]",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_RED,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"Official MIOS slot realeasing error");
                                                                                break;
                                                                            }
                                                                            stLabelsSettings[0].stLabelLocation.intColumn=stLabelsSettings[0].stLabelLocation.intColumn+1;
                                                                        }
                                                                    }
                                                                    if (stLabelsSettings[0].stLabelLocation.intColumn==stLabelsSettings[0].stLabelLocation.intRow) {
                                                                        setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_GREEN,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,3,"Installation completed");
                                                                    }
                                                                    else {
                                                                        cleanMiosSlots();
                                                                    }
                                                                }
                                                                else {
                                                                    setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_MAGENTA,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"No MIOS WADs selected");
                                                                }
                                                                break;
                                                            case PAD_TRIGGER_L:
                                                                selectListItem(&stListSettings,LIST_PAGE_START_ITEM_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)-stListSettings.chVisibleListItemsCount);
                                                                setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Page %u of %u",LIST_PAGE_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)+1,stLabelsSettings[0].stLabelLocation.intColumn));
                                                                break;
                                                            case PAD_TRIGGER_R:
                                                                selectListItem(&stListSettings,LIST_PAGE_START_ITEM_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)+stListSettings.chVisibleListItemsCount);
                                                                setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Page %u of %u",LIST_PAGE_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)+1,stLabelsSettings[0].stLabelLocation.intColumn));
                                                                break;
                                                            case PAD_BUTTON_B:
                                                                if (stListSettings.stListItems[stListSettings.intSelectedListItemIndex].blnMarked) {
                                                                    stLabelsSettings[0].stLabelLocation.intRow=stLabelsSettings[0].stLabelLocation.intRow-1;
                                                                    *strFormattedMessage=' ';
                                                                }
                                                                else {
                                                                    stLabelsSettings[0].stLabelLocation.intRow=stLabelsSettings[0].stLabelLocation.intRow+1;
                                                                    *strFormattedMessage=254;
                                                                }
                                                                markListItem(&stListSettings,stListSettings.intSelectedListItemIndex,*strFormattedMessage,DEFAULT_FONT_FGCOLOR);
                                                                break;
                                                        }
                                                    }
                                                    else {
                                                        pressed=PAD_BUTTON_START;
                                                    }
                                                }
                                                freeListItems(&stListSettings.stListItems,stListSettings.intListItemsCount);
                                                destroyList(&stListSettings,false);
                                            }
                                        }
                                        else {
                                            setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_RED,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"SD card not mounted");
                                        }
                                        break;
                                    case PAD_BUTTON_B:
                                        clearConsole();
                                        setFrameBuffer(objRenderSettings,stVideoParameters.stFrameBuffers[2].frameBuffer);
                                        printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"[*] MIOS LAUNCHER\n");
                                        drawLabel(-1,-1,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,">Select game ",intConsoleColumnsCount-14,&stLabelsSettings[0],&stLabelsLocation[0]);
                                        printf("\n");
                                        drawLabel(-1,-1,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," MIOS ",intConsoleColumnsCount-7,&stLabelsSettings[1],&stLabelsLocation[1]);
                                        printf("\n");
                                        drawLabel(-1,-1,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," Language ",intConsoleColumnsCount-11,&stLabelsSettings[2],&stLabelsLocation[2]);
                                        printf("\n");
                                        drawLabel(-1,-1,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," Video mode ",intConsoleColumnsCount-13,&stLabelsSettings[3],&stLabelsLocation[3]);
                                        printf("\n");
                                        drawLabel(-1,-1,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," Force video ",intConsoleColumnsCount-14,&stLabelsSettings[4],&stLabelsLocation[4]);
                                        printf("\n");
                                        drawLabel(-1,-1,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," No disc ",intConsoleColumnsCount/2-10,&stLabelsSettings[5],&stLabelsLocation[5]);
                                        drawLabel(-1,intConsoleColumnsCount/2,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," Widescreen ",intConsoleColumnsCount/2-13,&stLabelsSettings[6],&stLabelsLocation[6]);
                                        printf("\n");
                                        drawLabel(-1,-1,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," Drive reset ",intConsoleColumnsCount/2-14,&stLabelsSettings[7],&stLabelsLocation[7]);
                                        drawLabel(-1,intConsoleColumnsCount/2,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," NTSC-J patch ",intConsoleColumnsCount/2-15,&stLabelsSettings[8],&stLabelsLocation[8]);
                                        printf("\n");
                                        drawLabel(-1,-1,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," LED ",intConsoleColumnsCount/2-6,&stLabelsSettings[9],&stLabelsLocation[9]);
                                        drawLabel(-1,intConsoleColumnsCount/2,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," PAD Hook ",intConsoleColumnsCount/2-11,&stLabelsSettings[10],&stLabelsLocation[10]);
                                        printf("\n");
                                        drawLabel(-1,-1,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," Cheats ",intConsoleColumnsCount/2-9,&stLabelsSettings[11],&stLabelsLocation[11]);
                                        drawLabel(-1,intConsoleColumnsCount/2,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT," No More Memory ",intConsoleColumnsCount/2-17,&stLabelsSettings[12],&stLabelsLocation[12]);
                                        printf("\n");
                                        drawCommandsBar(4,true,&stCommandsBarSettings);
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[0],2,": Navigation");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[2],2,": Change values");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[4],1,": Launch game");
                                        addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[5],1,": Exit");
                                        setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Current IOS: %d v%d",IOS_GetVersion(),IOS_GetRevision()));
                                        VIDEO_WaitVSync();
                                        if (chInstalledMiosCount) {
                                            unmountFatDevice();
                                            printListItem(stLabelsSettings[0].stLabelLocation.intRow,stLabelsSettings[0].stLabelLocation.intColumn,"",0,1,CONSOLE_FONT_BLACK,"","",stLabelsSettings[0].chLabelSize,"Getting GC Games list...","");
                                            stGcGamesInfos=getGcGamesList(&stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth,5,DVD_STORAGE_DEVICE,USB_STORAGE_DEVICE,SD_STORAGE_DEVICE,SDGECKOA_STORAGE_DEVICE,SDGECKOB_STORAGE_DEVICE);
                                            FAT_DEVICE=mountFatDevice(1,FAT_DEVICE);
                                            if (reallocBuffer((void **) &stGcGamesInfos,(stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth+1)*DVD_DISC_INFOS_STRUCTURE_SIZE,0)==NULL) {
                                                freeVector((void **) &stGcGamesInfos);
                                                setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_MAGENTA,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"No GC Games detected");
                                            }
                                            else {
                                                if ((stGamesSettings=getGamesSettings(stGcGamesInfos,stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth,&stGamesIniSettings,&intGamesSettingsCount,&stDefaultGameConfig))==NULL) {
                                                    setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_RED,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"Loading games settings failed");
                                                }
                                                else {
                                                    if (reallocBuffer((void **) &stGamesSettings,(stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth+1)*POINTER_TYPE_SIZE,0)==NULL) {
                                                        freeVector((void **) &stGamesSettings);
                                                        setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_RED,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"Adding homebrew support failed");
                                                    }
                                                    else {
                                                        strcpy(stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth].strGameTitle,"MIOS homebrew mode");
                                                        stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth].STORAGE_DEVICE=SDGECKOA_STORAGE_DEVICE;
                                                        strncpy(stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth].strDiscID,strcpy(stDefaultGameConfig.strDiscID,"DOLAPP"),6);
                                                        stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth]=&stDefaultGameConfig;
                                                        stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth=stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth+1;
                                                        pressed=0;
                                                        stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft=0;
                                                        stSettingsScreenTextures[0].stTileTextureSettings.intTileTop=0;
                                                        stSettingsScreenTextures[0].stTileTextureSettings.intTileHeight=STATIC_ARRAY_SIZE(strGcLanguages);
                                                        stCommandsBarSettings.stCommandsBarLocation.intColumn=STATIC_ARRAY_SIZE(strGcForceVideos);
                                                        stVideoParameters.intBgTop=STATIC_ARRAY_SIZE(strGcVideoModes);
                                                        printListItem(stLabelsSettings[0].stLabelLocation.intRow,stLabelsSettings[0].stLabelLocation.intColumn,"",stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft,stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth,CONSOLE_FONT_BLACK,"","",stLabelsSettings[0].chLabelSize,stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].strGameTitle,"...");
                                                        stCommandsBarSettings.chCommandsCount=initGameConfigurationMenu(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft],stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].STORAGE_DEVICE,stInstalledMiosInfos,chInstalledMiosCount,&stInstalledCompatibleMiosInfos,&chInstalledCompatibleMiosCount,stLabelsSettings,stLabelsLocation);
                                                        while ((pressed!=PAD_BUTTON_START) && (pressed!=PAD_BUTTON_A)) {
                                                            if ((pressed=getPadsKeyPressed(&intExpectedPadsKeys[0],6,true,0,0))) {
                                                                switch(pressed) {
                                                                    case PAD_BUTTON_A:
                                                                        if (chInstalledCompatibleMiosCount) {
                                                                            if ((stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].STORAGE_DEVICE==SDGECKOA_STORAGE_DEVICE) || (stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].STORAGE_DEVICE==SDGECKOB_STORAGE_DEVICE)) {
                                                                                stAppArguments[1].strArgumentValue=NULL;
                                                                                if (strcmp(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->strDiscID,"DOLAPP")) {
                                                                                    if ((FAT_DEVICE) && (blnTryAhbProt)) {
                                                                                        stAppArguments[1].strArgumentValue=getFileContent(getFormattedString(strFormattedMessage,"%s/swiss.dol",strArguments[0]),(size_t *) &stLabelsLocation[1].intRow,0);
                                                                                    }
                                                                                    stLabelsLocation[10].intRow=sprintf(strFormattedMessage,"%s:/",getDeviceLabel(stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].STORAGE_DEVICE));
                                                                                }
                                                                                else {
                                                                                    stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].STORAGE_DEVICE=FAT_DEVICE;
                                                                                    if (stAppArguments[4].strArgumentValue==NULL) {
                                                                                        stLabelsLocation[10].intRow=sprintf(strFormattedMessage,"%s:/",getDeviceLabel(FAT_DEVICE));
                                                                                    }
                                                                                    else {
                                                                                        stLabelsLocation[10].intRow=sprintf(strFormattedMessage,"%s/",stAppArguments[4].strArgumentValue);
                                                                                    }
                                                                                }
                                                                                if (stAppArguments[1].strArgumentValue==NULL) {
                                                                                    unmountFatDevice();
                                                                                    if (mountFatDevice(1,stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].STORAGE_DEVICE)!=UNKNOWN_STORAGE_DEVICE) {
                                                                                        if ((stListSettings.stListItems=getDolsList(strFormattedMessage,false,GC_DOL_IMAGE_MAXSIZE,&stListSettings.intListItemsCount))!=NULL) {
                                                                                            clearConsole();
                                                                                            printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],"[*] MIOS HOMEBREW MODE SETTINGS\n");
                                                                                            drawCommandsBar(5,true,&stCommandsBarSettings);
                                                                                            addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[0],2,": Navigation");
                                                                                            addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[4],1,": Launch DOL");
                                                                                            addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[6],1,": Previous page");
                                                                                            addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[5],1,": Exit");
                                                                                            addCommandsBarItem(&stCommandsBarSettings,&intExpectedPadsKeys[7],1,": Next page");
                                                                                            strcpy(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.strCheatsPath,getFormattedString(strFormattedMessage,"%s:/%s",getDeviceLabel(stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].STORAGE_DEVICE),basename(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.strCheatsPath)));
                                                                                            drawList(1,0,intConsoleColumnsCount,DEFAULT_FONT_FGCOLOR,CONSOLE_FONT_CYAN,stListSettings.stListItems,stListSettings.intListItemsCount,stCommandsBarSettings.stCommandsBarLocation.intRow-2,stLabelsLocation[10].intRow,1,getArrayMemoryItemIndex((void *) &stListSettings.stListItems[0].strLabel,stListSettings.intListItemsCount,stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.strCheatsPath,-1*(strlen(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.strCheatsPath)+1),LIST_ITEM_STRUCTURE_SIZE,false),"[ ] ","",-3,&stListSettings);
                                                                                            markListItem(&stListSettings,stListSettings.intSelectedListItemIndex,254,DEFAULT_FONT_FGCOLOR);
                                                                                            stLabelsSettings[0].stLabelLocation.intColumn=LIST_TOTAL_PAGES_COUNT(stListSettings.chVisibleListItemsCount,stListSettings.intListItemsCount);
                                                                                            setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Page 1 of %u",stLabelsSettings[0].stLabelLocation.intColumn));
                                                                                            VIDEO_WaitVSync();
                                                                                            pressed=0;
                                                                                            while ((pressed!=PAD_BUTTON_START) && (pressed!=PAD_BUTTON_A)) {
                                                                                                if ((pressed=getPadsKeyPressed(&intExpectedPadsKeys[0],8,true,0,0))) {
                                                                                                    switch(pressed) {
                                                                                                        case PAD_BUTTON_UP:
                                                                                                            markListItem(&stListSettings,stListSettings.intSelectedListItemIndex,' ',DEFAULT_FONT_FGCOLOR);
                                                                                                            selectListItem(&stListSettings,stListSettings.intSelectedListItemIndex-1);
                                                                                                            markListItem(&stListSettings,stListSettings.intSelectedListItemIndex,254,DEFAULT_FONT_FGCOLOR);
                                                                                                            break;
                                                                                                        case PAD_BUTTON_DOWN:
                                                                                                            markListItem(&stListSettings,stListSettings.intSelectedListItemIndex,' ',DEFAULT_FONT_FGCOLOR);
                                                                                                            selectListItem(&stListSettings,stListSettings.intSelectedListItemIndex+1);
                                                                                                            markListItem(&stListSettings,stListSettings.intSelectedListItemIndex,254,DEFAULT_FONT_FGCOLOR);
                                                                                                            break;
                                                                                                        case PAD_TRIGGER_L:
                                                                                                            selectListItem(&stListSettings,LIST_PAGE_START_ITEM_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)-stListSettings.chVisibleListItemsCount);
                                                                                                            setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Page %u of %u",LIST_PAGE_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)+1,stLabelsSettings[0].stLabelLocation.intColumn));
                                                                                                            break;
                                                                                                        case PAD_TRIGGER_R:
                                                                                                            selectListItem(&stListSettings,LIST_PAGE_START_ITEM_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)+stListSettings.chVisibleListItemsCount);
                                                                                                            setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Page %u of %u",LIST_PAGE_INDEX(stListSettings.intSelectedListItemIndex,stListSettings.chVisibleListItemsCount)+1,stLabelsSettings[0].stLabelLocation.intColumn));
                                                                                                            break;
                                                                                                    }
                                                                                                }
                                                                                                else {
                                                                                                    pressed=PAD_BUTTON_START;
                                                                                                }
                                                                                            }
                                                                                            strcpy(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.strCheatsPath,stListSettings.stListItems[stListSettings.intSelectedListItemIndex].strLabel);
                                                                                            stAppArguments[1].strArgumentValue=getFileContent(stListSettings.stListItems[stListSettings.intSelectedListItemIndex].strLabel,(size_t *) &stLabelsLocation[1].intRow,0);
                                                                                            freeListItems(&stListSettings.stListItems,stListSettings.intListItemsCount);
                                                                                            destroyList(&stListSettings,false);
                                                                                        }
                                                                                        unmountFatDevice();
                                                                                    }
                                                                                    FAT_DEVICE=mountFatDevice(1,FAT_DEVICE);
                                                                                    if (stAppArguments[1].strArgumentValue==NULL) {
                                                                                        stAppArguments[1].strArgumentValue=(char *) swiss_bin;
                                                                                        stLabelsLocation[1].intRow=swiss_bin_size;
                                                                                    }
                                                                                }
                                                                                setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,"Loading DOL into memory...");
                                                                                setMiosHomebrewMode(miosload_bin,miosload_bin_size,(const u8 *) stAppArguments[1].strArgumentValue,stLabelsLocation[1].intRow);
                                                                                if (stAppArguments[1].strArgumentValue!=(char *) swiss_bin) {
                                                                                    freeVector((void **) &stAppArguments[1].strArgumentValue);
                                                                                }
                                                                            }
                                                                            if (pressed==PAD_BUTTON_A) {
                                                                                clearConsole();
                                                                                setFrameBuffer(objRenderSettings,stVideoParameters.stFrameBuffers[0].frameBuffer);
                                                                                printStyledText(-1,-1,DEFAULT_FONT_BGCOLOR,CONSOLE_FONT_YELLOW,CONSOLE_FONT_BOLD,&stLabelsLocation[0],getFormattedString(strFormattedMessage,"[*] MIOS LAUNCHER DETAILS (%s)\n",stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->strDiscID));
                                                                                drawCommandsBar(0,true,&stCommandsBarSettings);
                                                                                setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,getFormattedString(strFormattedMessage,"Current IOS: %d v%d",IOS_GetVersion(),IOS_GetRevision()));
                                                                                stCommandsBarSettings.chCommandsCount=intConsoleColumnsCount-7;
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion=((void *) stInstalledCompatibleMiosInfos[stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion]-(void *) &stInstalledMiosInfos[0])/POINTER_TYPE_SIZE;
                                                                                initLogMonitor(1,0,stCommandsBarSettings.stStatusBarLocation.intRow-2,intConsoleColumnsCount,false,&stLogMonitorSettings);
                                                                                updateLogMonitor("[MIOS ACTIVATION]",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings);
                                                                                updateLogMonitor(getFormattedString(strFormattedMessage,"%*s [NOTE]",stCommandsBarSettings.chCommandsCount-updateLogMonitor(getFormattedString(strFormattedMessage,"> %s <-> %s",stInstalledMiosInfos[0]->strTitleLabel,stInstalledMiosInfos[stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion]->strTitleLabel),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                updateLogMonitor(getFormattedString(strFormattedMessage,"%*s ",stCommandsBarSettings.chCommandsCount-updateLogMonitor(getFormattedString(strFormattedMessage,"> /title/00000001/00000101 <-> /title/00000001/%08x",MIOS_MINOR_TID+stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                if (activateMios(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion)) {
                                                                                    updateLogMonitor("[",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                    updateLogMonitor("DONE",CONSOLE_FONT_GREEN,CONSOLE_FONT_BOLD,0,&stLogMonitorSettings);
                                                                                    updateLogMonitor("]",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                    updateLogMonitor("[GAME LAUNCHING]",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings);
                                                                                    if (strncmp(strstr(stInstalledMiosInfos[stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion]->strTitleInfos,MIOS_INFOS_FAMILY_ID_LABEL)+strlen(MIOS_INFOS_FAMILY_ID_LABEL)+1,DIOS_MIOS_FAMILY_ID,2)) {
                                                                                        stDefaultGameConfig.stDiosMiosConfig.intCfgVersion=1;
                                                                                        updateLogMonitor(getFormattedString(strFormattedMessage,"%*s [NOTE]",stCommandsBarSettings.chCommandsCount-updateLogMonitor("> Using basic MIOS mode...",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                    }
                                                                                    else {
                                                                                        memcpy(&stDefaultGameConfig,stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft],GAME_CONFIG_STRUCTURE_SIZE);
                                                                                        stDefaultGameConfig.stDiosMiosConfig.intMagicbytes=DIOS_MIOS_MAGICWORD;
                                                                                        stDefaultGameConfig.stDiosMiosConfig.intCfgVersion=0x2;
                                                                                        if (stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].STORAGE_DEVICE==DVD_STORAGE_DEVICE) {
                                                                                            updateLogMonitor(getFormattedString(strFormattedMessage,"%*s [NOTE]",stCommandsBarSettings.chCommandsCount-updateLogMonitor("> Using DM(L) DISC mode...",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                            stDefaultGameConfig.stDiosMiosConfig.intOptions=stDefaultGameConfig.stDiosMiosConfig.intOptions | DIOS_MIOS_BOOT_DISC;
                                                                                        }
                                                                                        else {
                                                                                            if (stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].DVD_GAME_FORMAT==FST_GAME_FORMAT) {
                                                                                                strcat(dirname(stDefaultGameConfig.stDiosMiosConfig.strGamePath),"/");
                                                                                                updateLogMonitor(getFormattedString(strFormattedMessage,"%*s [NOTE]",stCommandsBarSettings.chCommandsCount-updateLogMonitor("> Using DM(L) FST mode...",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                            }
                                                                                            else {
                                                                                                updateLogMonitor(getFormattedString(strFormattedMessage,"%*s [NOTE]",stCommandsBarSettings.chCommandsCount-updateLogMonitor("> Using DM(L) ISO mode...",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                            }
                                                                                            stDefaultGameConfig.stDiosMiosConfig.intOptions=stDefaultGameConfig.stDiosMiosConfig.intOptions | DIOS_MIOS_GAME_PATH;
                                                                                        }
                                                                                        if (stDefaultGameConfig.blnDriveReset) {
                                                                                            updateLogMonitor(getFormattedString(strFormattedMessage,"%*s [NOTE]",stCommandsBarSettings.chCommandsCount-updateLogMonitor("> Reset drive...",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                            resetDvdDrive();
                                                                                        }
                                                                                        updateLogMonitor(getFormattedString(strFormattedMessage,"%*s [NOTE]",stCommandsBarSettings.chCommandsCount-updateLogMonitor("> Fixing game DM(L) settings...",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                        setCacheDataSegment(THERMAL_INTERRUPT,DIOS_MIOS_SETTINGS_STRUCTURE_SIZE,&stDefaultGameConfig.stDiosMiosConfig);
                                                                                        setCacheDataSegment(APPLOADER_LOADING_ADDRESS,DIOS_MIOS_SETTINGS_STRUCTURE_SIZE,&stDefaultGameConfig.stDiosMiosConfig);
                                                                                        if (stDefaultGameConfig.blnNtscjPatch) {
                                                                                            updateLogMonitor(getFormattedString(strFormattedMessage,"%*s [NOTE]",stCommandsBarSettings.chCommandsCount-updateLogMonitor("> Applying NTSC-J patch...",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                            *HW_PPCSPEED=0x0002A9E0;
                                                                                        }
                                                                                        objRenderSettings=getGameVideoMode(stDefaultGameConfig.strDiscID,&stDefaultGameConfig.VIDEO_MODE);
                                                                                    }
                                                                                    updateLogMonitor(getFormattedString(strFormattedMessage,"%*s [NOTE]",stCommandsBarSettings.chCommandsCount-updateLogMonitor("> Launching game...",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,100,&stLogMonitorSettings),""),DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                }
                                                                                else {
                                                                                    updateLogMonitor("[",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                    updateLogMonitor("FAIL",CONSOLE_FONT_RED,CONSOLE_FONT_BOLD,0,&stLogMonitorSettings);
                                                                                    updateLogMonitor("]",DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,0,&stLogMonitorSettings);
                                                                                    setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_RED,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,getFormattedString(strFormattedMessage,"%s activation failed",stInstalledMiosInfos[stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion]->strTitleLabel));
                                                                                }
                                                                            }
                                                                            pressed=PAD_BUTTON_START;
                                                                        }
                                                                        else {
                                                                            pressed=PAD_BUTTON_UP;
                                                                        }
                                                                        break;
                                                                    case PAD_BUTTON_UP:
                                                                        stVideoParameters.intBgLeft=-1;
                                                                        DRAWCURSOR:
                                                                        printStyledText(stLabelsLocation[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop].intRow,stLabelsLocation[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop].intColumn,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,&stLabelsLocation[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop]," ");
                                                                        stSettingsScreenTextures[0].stTileTextureSettings.intTileTop=getListItemId(stSettingsScreenTextures[0].stTileTextureSettings.intTileTop,stVideoParameters.intBgLeft,stCommandsBarSettings.chCommandsCount);
                                                                        printStyledText(stLabelsLocation[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop].intRow,stLabelsLocation[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop].intColumn,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,&stLabelsLocation[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop],">");
                                                                        break;
                                                                    case PAD_BUTTON_DOWN:
                                                                        stVideoParameters.intBgLeft=1;
                                                                        goto DRAWCURSOR;
                                                                    case PAD_BUTTON_LEFT:
                                                                        stVideoParameters.intBgLeft=-1;
                                                                        DRAWMENUOPTIONS:
                                                                        switch (stSettingsScreenTextures[0].stTileTextureSettings.intTileTop) {
                                                                            case 0:
                                                                                if (stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft!=getListItemId(stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft,stVideoParameters.intBgLeft,stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth)) {
                                                                                    stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft=stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft+stVideoParameters.intBgLeft;
                                                                                    printListItem(stLabelsSettings[0].stLabelLocation.intRow,stLabelsSettings[0].stLabelLocation.intColumn,"",stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft,stSettingsScreenTextures[0].stTileTextureSettings.intTileWidth,CONSOLE_FONT_BLACK,"","",stLabelsSettings[0].chLabelSize,stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].strGameTitle,"...");
                                                                                    stCommandsBarSettings.chCommandsCount=initGameConfigurationMenu(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft],stGcGamesInfos[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft].STORAGE_DEVICE,stInstalledMiosInfos,chInstalledMiosCount,&stInstalledCompatibleMiosInfos,&chInstalledCompatibleMiosCount,stLabelsSettings,stLabelsLocation);
                                                                                }
                                                                                break;
                                                                            case 1:
                                                                                if (stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion!=getListItemId(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion,stVideoParameters.intBgLeft,chInstalledCompatibleMiosCount)) {
                                                                                    stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion=stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion+stVideoParameters.intBgLeft;
                                                                                    printListItem(stLabelsSettings[1].stLabelLocation.intRow,stLabelsSettings[1].stLabelLocation.intColumn,"",stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion,chInstalledCompatibleMiosCount,CONSOLE_FONT_BLACK,"","",stLabelsSettings[1].chLabelSize,(*stInstalledCompatibleMiosInfos[stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion])->strTitleLabel,"...");
                                                                                    stCommandsBarSettings.chCommandsCount=2+initMiosConfigurationMenu(*stInstalledCompatibleMiosInfos[stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion],stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft],&stLabelsSettings[2]);
                                                                                    memcpy(&stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stIosIdentificationModule,&(*stInstalledCompatibleMiosInfos[stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intCfgVersion])->stIdentificationModule,TITLE_IDENTIFICATION_MODULE_STRUCTURE_SIZE);
                                                                                }
                                                                                break;
                                                                            case 2:
                                                                                if (stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->GAME_LANGUAGE!=getListItemId(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->GAME_LANGUAGE,stVideoParameters.intBgLeft,stSettingsScreenTextures[0].stTileTextureSettings.intTileHeight)) {
                                                                                    stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->GAME_LANGUAGE=stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->GAME_LANGUAGE+stVideoParameters.intBgLeft;
                                                                                    printListItem(stLabelsSettings[2].stLabelLocation.intRow,stLabelsSettings[2].stLabelLocation.intColumn,"",stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->GAME_LANGUAGE,stSettingsScreenTextures[0].stTileTextureSettings.intTileHeight,CONSOLE_FONT_BLACK,"","",stLabelsSettings[2].chLabelSize,strGcLanguages[stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->GAME_LANGUAGE],"");
                                                                                }
                                                                                break;
                                                                            case 3:
                                                                                if (stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->VIDEO_MODE!=getListItemId(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->VIDEO_MODE,stVideoParameters.intBgLeft,stVideoParameters.intBgTop)) {
                                                                                    stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->VIDEO_MODE=stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->VIDEO_MODE+stVideoParameters.intBgLeft;
                                                                                    setGameVideoSettings(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft],stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->VIDEO_MODE);
                                                                                    printListItem(stLabelsSettings[3].stLabelLocation.intRow,stLabelsSettings[3].stLabelLocation.intColumn,"",stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->VIDEO_MODE,stVideoParameters.intBgTop,CONSOLE_FONT_BLACK,"","",stLabelsSettings[3].chLabelSize,strGcVideoModes[stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->VIDEO_MODE],"");
                                                                                }
                                                                                break;
                                                                            case 4:
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes=stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intVideoMode>>16;
                                                                                if (stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes!=getListItemId(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes,stVideoParameters.intBgLeft,stCommandsBarSettings.stCommandsBarLocation.intColumn)) {
                                                                                    stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes=stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes+stVideoParameters.intBgLeft;
                                                                                    stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intVideoMode=stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intVideoMode+((1<<16)*stVideoParameters.intBgLeft);
                                                                                    printListItem(stLabelsSettings[4].stLabelLocation.intRow,stLabelsSettings[4].stLabelLocation.intColumn,"",stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes,stCommandsBarSettings.stCommandsBarLocation.intColumn,CONSOLE_FONT_BLACK,"","",stLabelsSettings[4].chLabelSize,strGcForceVideos[stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes],"");
                                                                                }
                                                                                break;
                                                                            case 5:
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes=getBooleanListItemId(&stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intOptions,DIOS_MIOS_NODISC,stVideoParameters.intBgLeft);
                                                                                DRAWMENUBOOLEANOPTIONS:
                                                                                printListItem(stLabelsSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop].stLabelLocation.intRow,stLabelsSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop].stLabelLocation.intColumn,"",stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes,2,CONSOLE_FONT_BLACK,"","",stLabelsSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileTop].chLabelSize,strBooleanOptions[stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes],"");
                                                                                break;
                                                                            case 6:
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes=getBooleanListItemId(&stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intOptions,DIOS_MIOS_WIDESCREEN,stVideoParameters.intBgLeft);
                                                                                goto DRAWMENUBOOLEANOPTIONS;
                                                                            case 7:
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes=getListItemId((unsigned int) stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->blnDriveReset,stVideoParameters.intBgLeft,2);
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->blnDriveReset=(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes==1);
                                                                                goto DRAWMENUBOOLEANOPTIONS;
                                                                            case 8:
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes=getListItemId((unsigned int) stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->blnNtscjPatch,stVideoParameters.intBgLeft,2);
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->blnNtscjPatch=(stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes==1);
                                                                                goto DRAWMENUBOOLEANOPTIONS;
                                                                            case 9:
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes=getBooleanListItemId(&stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intOptions,DIOS_MIOS_LED,stVideoParameters.intBgLeft);
                                                                                goto DRAWMENUBOOLEANOPTIONS;
                                                                            case 10:
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes=getBooleanListItemId(&stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intOptions,DIOS_MIOS_PADHOOK,stVideoParameters.intBgLeft);
                                                                                goto DRAWMENUBOOLEANOPTIONS;
                                                                            case 11:
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes=getBooleanListItemId(&stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intOptions,DIOS_MIOS_CHEATS,stVideoParameters.intBgLeft);
                                                                                goto DRAWMENUBOOLEANOPTIONS;
                                                                            case 12:
                                                                                stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intMagicbytes=getBooleanListItemId(&stGamesSettings[stSettingsScreenTextures[0].stTileTextureSettings.intTileLeft]->stDiosMiosConfig.intOptions,DIOS_MIOS_NMM,stVideoParameters.intBgLeft);
                                                                                goto DRAWMENUBOOLEANOPTIONS;
                                                                        }
                                                                        break;
                                                                   case PAD_BUTTON_RIGHT:
                                                                        stVideoParameters.intBgLeft=1;
                                                                        goto DRAWMENUOPTIONS;
                                                                }
                                                            }
                                                            else {
                                                                pressed=PAD_BUTTON_START;
                                                            }
                                                        }
                                                        freeVector((void **) &stGamesSettings);
                                                        if ((FAT_DEVICE) && (blnTryAhbProt)) {
                                                            writeBinaryFile(getFormattedString(strFormattedMessage,"%s/mios-switcher.ini",strArguments[0]),stGamesIniSettings,intGamesSettingsCount*GAME_CONFIG_STRUCTURE_SIZE);
                                                        }
                                                    }
                                                }
                                                freeVector((void **) &stGcGamesInfos);
                                            }
                                        }
                                        else {
                                            setStatusBar(&stCommandsBarSettings,CONSOLE_FONT_MAGENTA,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,5,"No MIOS detected");
                                        }
                                        break;
                                }
                            }
                            else {
                                pressed=PAD_BUTTON_START;
                            }
                        }
                        freeVector((void **) &stInstalledMiosInfos);
                    }
                    setStatusBar(&stCommandsBarSettings,DEFAULT_FONT_BGCOLOR,DEFAULT_FONT_FGCOLOR,DEFAULT_FONT_WEIGHT,2,(stDefaultGameConfig.stDiosMiosConfig.intCfgVersion)?"Launching BC...":"Exiting...");
                }
                freeTitlesInfos(&stKnownMiosInfos,intArgumentsCount);
            }
            if (stAppArguments[0].strArgumentValue!=(char *) MIOSINFOS_xml) {
                freeVector((void *) &stAppArguments[0].strArgumentValue);
            }
            freeVector((void **) &stGamesIniSettings);
            if (FAT_DEVICE) {
                freeVector((void **) &stAppArguments[3].strArgumentValue);
                freeVector((void **) &stAppArguments[4].strArgumentValue);

#ifdef DEBUG_FILE
                writeLogFile(getFormattedString(strFormattedMessage,"%s:/%s",getDeviceLabel(FAT_DEVICE),DEBUG_FILE),DEBUG_LOG_MESSAGE);
#endif
            }
            unmountFatDevice();
            WPAD_Shutdown();
        }
        else {
            return 2;
        }
        unmountNandFs();
    }
    else {
        return 1;
    }
    switch (stDefaultGameConfig.stDiosMiosConfig.intCfgVersion) {
        case 1:
            switch (VIDEO_GetCurrentTvMode()) {
                case VI_PAL:
                    objRenderSettings=&TVPal528IntDf;
                    stDefaultGameConfig.VIDEO_MODE=PAL50_VIDEO_MODE;
                    break;
                case VI_MPAL:
                    objRenderSettings=&TVMpal480IntDf;
                    stDefaultGameConfig.VIDEO_MODE=NTSC480I_VIDEO_MODE;
                    break;
                case VI_EURGB60:
                    objRenderSettings=&TVEurgb60Hz480IntDf;
                    stDefaultGameConfig.VIDEO_MODE=PAL60_VIDEO_MODE;
                    break;
                case VI_NTSC:
                default:
                    objRenderSettings=&TVNtsc480IntDf;
                    stDefaultGameConfig.VIDEO_MODE=NTSC480I_VIDEO_MODE;
                    break;
            }
        case 2:
            VIDEO_Configure(objRenderSettings);
            VIDEO_SetBlack(TRUE);
            VIDEO_Flush();
            VIDEO_WaitVSync();
            if (objRenderSettings->viTVMode & VI_NON_INTERLACE) {
                VIDEO_WaitVSync();
            }
            setGameSystemSettings(&stDefaultGameConfig);
            *SOFT_RESET |= 7;
            WII_Initialize();
            return WII_LaunchTitle(BC_TID);
            break;
        default:
            break;
    }
    return 0;
}
