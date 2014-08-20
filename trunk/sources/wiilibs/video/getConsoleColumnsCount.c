#include <ogc/consol.h>
//version finale
int getConsoleColumnsCount() {
int intConsoleColumnsCount,intConsoleRowsCount;
    CON_GetMetrics(&intConsoleColumnsCount,&intConsoleRowsCount);
    return intConsoleColumnsCount;
}
