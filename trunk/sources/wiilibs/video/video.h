#ifndef _VIDEO_H_
#define _VIDEO_H_
#include <ogc/color.h>
#include "../images/images.h"
#define FGCOLOR_PATTERN_SIZE 10
#define BGCOLOR_PATTERN_SIZE 8
#define FGCOLOR_PATTERN_PREFIX "\x1b[3"
#define BGCOLOR_PATTERN_PREFIX "\x1b[4"
enum CONSOLE_FONT_COLORS {
	CONSOLE_FONT_BLACK=0,
	CONSOLE_FONT_RED=1,
	CONSOLE_FONT_GREEN=2,
	CONSOLE_FONT_YELLOW=3,
	CONSOLE_FONT_BLUE=4,
	CONSOLE_FONT_MAGENTA=5,
	CONSOLE_FONT_CYAN=6,
	CONSOLE_FONT_WHITE=7,
	CONSOLE_FONT_CURRENT_COLOR=8
};
enum CONSOLE_COLORS {
    CONSOLE_BLACK=COLOR_BLACK,
    CONSOLE_MAROON=COLOR_MAROON,
    CONSOLE_GREEN=COLOR_GREEN,
    CONSOLE_OLIVE=COLOR_OLIVE,
    CONSOLE_NAVY=COLOR_NAVY,
    CONSOLE_PURPLE=COLOR_PURPLE,
    CONSOLE_TEAL=COLOR_TEAL,
    CONSOLE_GRAY=COLOR_GRAY,
    CONSOLE_SILVER=COLOR_SILVER,
    CONSOLE_RED=COLOR_RED,
    CONSOLE_LIME=COLOR_LIME,
    CONSOLE_YELLOW=COLOR_YELLOW,
    CONSOLE_BLUE=COLOR_BLUE,
    CONSOLE_FUCHSIA=COLOR_FUCHSIA,
    CONSOLE_AQUA=COLOR_AQUA,
    CONSOLE_WHITE=COLOR_WHITE,
    CONSOLE_MONEYGREEN=COLOR_MONEYGREEN,
    CONSOLE_SKYBLUE=COLOR_SKYBLUE,
    CONSOLE_CREAM=COLOR_CREAM,
    CONSOLE_MEDGRAY=COLOR_MEDGRAY,
};
enum CONSOLE_FONT_WEIGHTS {
    CONSOLE_FONT_NORMAL=0,
    CONSOLE_FONT_BOLD=1,
    CONSOLE_FONT_CURRENT_WEIGHT=2
};
struct stConsoleCursorLocation {
    int intColumn;
    int intRow;
};
struct stFrameBuffer {
    void *frameBuffer;
    struct stTextureSettings stTexturesSettings[10];
};
struct stVideoSettings {
    const void *imgBgData;
    double dbConsoleLeft;
    double dbConsoleTop;
    double dbConsoleWidth;
    double dbConsoleHeight;
    double dbBgImgXScaleFactor;
    double dbBgImgYScaleFactor;
    short int intBgLeft;
    short int intBgTop;
    unsigned short int intBgWidth;
    unsigned short int intBgHeight;
    struct stFrameBuffer stFrameBuffers[3];
};
enum VIDEO_MODES {
    AUTO_VIDEO_MODE=0,
    PAL50_VIDEO_MODE=1,
    PAL60_VIDEO_MODE=2,
    NTSC480I_VIDEO_MODE=3,
    NTSC480P_VIDEO_MODE=4,
    PAL480P_VIDEO_MODE=5,
    PATCHED_NTSC480P_VIDEO_MODE=6,
    PATCHED_PAL480P_VIDEO_MODE=7
};
#endif
