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
#define DARK_RAW_POINTER 21
#define DARK_POINTER     22

#define Boolean      bool
#define Unsigned8    unsigned char
#define Signed8      signed char
#define Unsigned16   unsigned short
#define Signed16     signed short
#define Unsigned32   unsigned int
#define Signed32     signed int
#define Unsigned64   unsigned long long
#define Signed64     signed long long
#define UnsignedSize unsigned long long
#define SignedSize   signed long long
#define Float32      float
#define Float64      double
#define Character    char
#define NullString   char*
#define RawString    char*
#define RawPointer   void*

typedef struct _String  String;
typedef struct _Blob    Blob;
typedef struct _List    List;
typedef struct _Map     Map;
typedef struct _Pointer Pointer;

typedef union
{
	Boolean      boolean;
	Unsigned8    u8;
	Signed8      s8;
	Unsigned16   u16;
	Signed16     s16;
	Unsigned32   u32;
	Signed32     s32;
	Unsigned64   u64;
	Signed64     s64;
	UnsignedSize usize;
	SignedSize   ssize;
	Float32      f32;
	Float64      f64;
	Character    character;
	NullString   nullString;
	RawString    rawString;
	String*      string;
	Blob*        blob;
	List*        list;
	Map*         map;
	RawPointer   rawPointer;
	Pointer*     pointer;
} Undefined;

typedef struct
{
	Unsigned8 type;
	Undefined value;
} Defined;
