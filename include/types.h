// Headers
#include <stdbool.h>

// Types
#define DKboolean bool
#define DKu8 unsigned char
#define DKs8 signed char
#define DKu16 unsigned short
#define DKs16 signed short
#define DKu32 unsigned int
#define DKs32 signed int
#define DKu64 unsigned long long
#define DKs64 signed long long
#define DKusize unsigned long long
#define DKssize signed long long
#define DKf32 float
#define DKf64 double
#define DKcharacter char
#define DKnullString char*
#define DKpointer void*
typedef struct _string DKstring;
typedef struct _blob DKblob;
typedef struct _ordinal DKordinal;
typedef struct _nominal DKnominal;

// Handle
typedef union
{
	DKboolean boolean;
	DKu8 u8;
	DKs8 s8;
	DKu16 u16;
	DKs16 s16;
	DKu32 u32;
	DKs32 s32;
	DKu64 u64;
	DKs64 s64;
	DKusize usize;
	DKssize ssize;
	DKf32 f32;
	DKf64 f64;
	DKcharacter character;
	DKnullString nullString;
	DKstring *string;
	DKblob *blob;
	DKordinal *ordinal;
	DKnominal *nominal;
	DKpointer pointer;
} DKhandle;
