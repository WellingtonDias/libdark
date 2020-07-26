#include <stdbool.h>

#define DARK_HANDLE_UNDEFINED    0
#define DARK_HANDLE_BOOLEAN      1
#define DARK_HANDLE_U8           2
#define DARK_HANDLE_S8           3
#define DARK_HANDLE_U16          4
#define DARK_HANDLE_S16          5
#define DARK_HANDLE_U32          6
#define DARK_HANDLE_S32          7
#define DARK_HANDLE_U64          8
#define DARK_HANDLE_S64          9
#define DARK_HANDLE_USIZE       10
#define DARK_HANDLE_SSIZE       11
#define DARK_HANDLE_F32         12
#define DARK_HANDLE_F64         13
#define DARK_HANDLE_CHARACTER   14
#define DARK_HANDLE_NULL_STRING 15
#define DARK_HANDLE_RAW_STRING  16
#define DARK_HANDLE_STRING      17
#define DARK_HANDLE_BLOB        18
#define DARK_HANDLE_ORDINAL     19
#define DARK_HANDLE_NOMINAL     20
#define DARK_HANDLE_POINTER     21

#define DKboolean    bool
#define DKu8         unsigned char
#define DKs8         signed char
#define DKu16        unsigned short
#define DKs16        signed short
#define DKu32        unsigned int
#define DKs32        signed int
#define DKu64        unsigned long long
#define DKs64        signed long long
#define DKusize      unsigned long long
#define DKssize      signed long long
#define DKf32        float
#define DKf64        double
#define DKcharacter  char
#define DKnullString char*
#define DKrawString  char*
#define DKpointer    void*

typedef struct _string  DKstring;
typedef struct _blob    DKblob;
typedef struct _ordinal DKordinal;
typedef struct _nominal DKnominal;

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
	DKrawString rawString;
	DKstring *string;
	DKblob *blob;
	DKordinal *ordinal;
	DKnominal *nominal;
	DKpointer pointer;
} DKvalue;

DKnullString boolean_toString[2];
