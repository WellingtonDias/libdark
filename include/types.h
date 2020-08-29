#include <stdbool.h>

#define DARK_UNDEFINED    0
#define DARK_BOOLEAN      1
#define DARK_U8           2
#define DARK_S8           3
#define DARK_U16          4
#define DARK_S16          5
#define DARK_U32          6
#define DARK_S32          7
#define DARK_U64          8
#define DARK_S64          9
#define DARK_USIZE       10
#define DARK_SSIZE       11
#define DARK_F32         12
#define DARK_F64         13
#define DARK_CHARACTER   14
#define DARK_NULL_STRING 15
#define DARK_RAW_STRING  16
#define DARK_STRING      17
#define DARK_BLOB        18
#define DARK_LIST        19
#define DARK_MAP         20
#define DARK_POINTER     21

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

typedef struct _string DKstring;
typedef struct _blob   DKblob;
typedef struct _list   DKlist;
typedef struct _map    DKmap;

typedef union
{
	DKboolean    boolean;
	DKu8         u8;
	DKs8         s8;
	DKu16        u16;
	DKs16        s16;
	DKu32        u32;
	DKs32        s32;
	DKu64        u64;
	DKs64        s64;
	DKusize      usize;
	DKssize      ssize;
	DKf32        f32;
	DKf64        f64;
	DKcharacter  character;
	DKnullString nullString;
	DKrawString  rawString;
	DKstring     *string;
	DKblob       *blob;
	DKlist       *list;
	DKmap        *map;
	DKpointer    pointer;
} DKundefined;

typedef struct
{
	DKu8        type;
	DKundefined value;
} DKdefined;
