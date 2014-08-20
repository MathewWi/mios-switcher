#ifndef _GUI_H_
#define _GUI_H_
#include "../video/video.h"
#include "../menu/menu.h"
#define AUTOSIZE 255
enum CELL_CORNERS {
    TOP_LEFT_CORNER=0,
    TOP_RIGHT_CORNER=3,
    BOTTOM_LEFT_CORNER=12,
    BOTTOM_RIGHT_CORNER=15
};
enum BORDER_SYMBOLS {
    HORIZONTAL_SINGLE_BORDER=196,
    MIDDLE_TOP_SINGLE_JUNCTION=194,
    LEFT_MIDDLE_SINGLE_JUNCTION=195,
    CROSS_SINGLE_JUNCTION=197,
    LEFT_TOP_SINGLE_CORNER=218,
    RIGHT_MIDDLE_SINGLE_JUNCTION=180,
    RIGHT_TOP_SINGLE_CORNER=191,
    MIDDLE_BOTTOM_SINGLE_JUNCTION=193,
    LEFT_BOTTOM_SINGLE_CORNER=192,
    RIGHT_BOTTOM_SINGLE_CORNER=217,
    VERTICAL_SINGLE_BORDER=179
};
enum BORDER_ALTERNATIVE_SYMBOLS {
    HORIZONTAL_DOUBLE_BORDER=205,
    MIDDLE_TOP_DOUBLE_JUNCTION=203,
    LEFT_MIDDLE_DOUBLE_JUNCTION=204,
    CROSS_DOUBLE_JUNCTION=206,
    LEFT_TOP_DOUBLE_CORNER=201,
    RIGHT_MIDDLE_DOUBLE_JUNCTION=185,
    RIGHT_TOP_DOUBLE_CORNER=187,
    MIDDLE_BOTTOM_DOUBLE_JUNCTION=202,
    LEFT_BOTTOM_DOUBLE_CORNER=200,
    RIGHT_BOTTOM_DOUBLE_CORNER=188,
    VERTICAL_DOUBLE_BORDER=186
};
enum BORDERS {
    NO_BORDER=0,
    LEFT_BORDER=1,
    TOP_BORDER=2,
    RIGHT_BORDER=4,
    BOTTOM_BORDER=8,
    ALL_BORDERS=LEFT_BORDER|TOP_BORDER|RIGHT_BORDER|BOTTOM_BORDER
};
enum BORDER_STYLES {
    SINGLE_BORDER=0,
    DOUBLE_BORDER=1,
    STAR_BORDER=42
};
enum FRAME_JUNCTIONS {
    NO_JUNCTION=0,
    HORIZONTAL_JUNCTION=1,
    VERTICAL_JUNCTION=2,
    ALL_JUNCTIONS=HORIZONTAL_JUNCTION|VERTICAL_JUNCTION
};
struct stLabel {
    unsigned char chLabelSize;
    struct stConsoleCursorLocation stLabelLocation;
};
struct stCommandsBar {
    struct stConsoleCursorLocation stStatusBarLocation;
    struct stConsoleCursorLocation stCommandsBarLocation;
    unsigned char chCommandsCount;
    unsigned char chCommandItemsCount;
};
struct stGuiList {
    unsigned char chRow;
    unsigned char chColumn;
    unsigned char chItemsInterlines;
    struct stListItem *stListItems;
    struct stLabel *stLabelsSettings;
    unsigned int intListItemsCount;
    size_t intListItemsHiddenPrefixSize;
    unsigned char chVisibleListItemsCount;
    unsigned char chFieldSize;
    const char *strPrependItemString;
    const char *strAppendItemString;
    signed char chMarkerOffset;
    unsigned int intSelectedListItemIndex;
    enum CONSOLE_FONT_COLORS LIST_FONT_COLOR;
    enum CONSOLE_FONT_COLORS ACTIVE_ITEM_COLOR;
};
struct stFrame {
    unsigned char chRow;
    unsigned char chColumn;
    unsigned char chRowsCount;
    unsigned char chColumnsCount;
    enum CONSOLE_FONT_COLORS BORDER_COLOR;
    enum CONSOLE_FONT_COLORS FRAME_COLOR;
    unsigned char chLeftBorderSymbol;
    unsigned char chRightBorderSymbol;
    unsigned char chTopBorderSymbol;
    unsigned char chBottomBorderSymbol;
    unsigned char chTopLeftJunctionSymbol;
    unsigned char chTopRightJunctionSymbol;
    unsigned char chBottomLeftJunctionSymbol;
    unsigned char chBottomRightJunctionSymbol;
};
struct stLogMonitor {
    unsigned char chRow;
    unsigned char chColumn;
    unsigned char chRowsCount;
    unsigned char chColumnsCount;
    struct stConsoleCursorLocation stCurrentCursorPositions;
};
enum {
    LABEL_STRUCTURE_SIZE=sizeof(struct stLabel)
};
#endif
