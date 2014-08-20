#ifndef _MACROS_H_
#define _MACROS_H_
#include <limits.h>
#include <math.h>
#define LOG(a,b) (log((a))/log((b)))
#define ROUND(a) (floor((a)+0.5))
#define CEIL(a,b) (((a)+(b)-1) & (~((b)-1)))
#define ALIGN(a,b) ((((a)+(b)-1)/(b))*(b))
#define ROUND_UP(x,n) (-(-(x) & -(n)))
#define SWAP(x,y) (*(x))=(*(x))+(*(y));(*(y))=(*(x))-(*(y));(*(x))=(*(x))-(*(y))
#ifndef MIN
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif
#ifndef MAX
#define MAX(x,y) ((x)>(y)?(x):(y))
#endif
#define DELTA_SIGN(x,y) ((x)==(y)?0:(x)<(y)?-1:1)
#define SIGN(x) (DELTA_SIGN((x),0))
#define DELTA(x,y) (DELTA_SIGN((x),(y))*(MAX((x),(y))-MIN((x),(y))))
#define MAJOR_NUMBER(x,t) ((x) >> (CHAR_BIT*sizeof(t)))
#define MINOR_NUMBER(x,t) ((x) & ((t) (-1)))
#define MAJOR_MINOR_NUMBER(x,y,t) ((((unsigned long long) (x)) << (CHAR_BIT*sizeof(t))) | (unsigned long long) (y))
#define ISPAIR(x) ((x)%2==0)
#define STATIC_ARRAY_SIZE(a) (sizeof((a))/sizeof((a[0])))
#define PNG_WIDTH(d) (*((unsigned int *) ((d)+16)))
#define PNG_HEIGHT(d) (*((unsigned int *) ((d)+20)))
#endif
