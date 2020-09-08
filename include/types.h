#include <stdbool.h>

#define DARK_UNDEFINED      0
#define DARK_BOOLEAN        1
#define DARK_UNSIGNED_8     2
#define DARK_SIGNED_8       3
#define DARK_UNSIGNED_16    4
#define DARK_SIGNED_16      5
#define DARK_UNSIGNED_32    6
#define DARK_SIGNED_32      7
#define DARK_UNSIGNED_64    8
#define DARK_SIGNED_64      9
#define DARK_UNSIGNED_SIZE 10
#define DARK_SIGNED_SIZE   11
#define DARK_FLOAT_32      12
#define DARK_FLOAT_64      13
#define DARK_CHARACTER     14
#define DARK_NULL_STRING   15
#define DARK_RAW_STRING    16
#define DARK_STRING        17
#define DARK_BLOB          18
#define DARK_LIST          19
#define DARK_MAP           20
#define DARK_RAW_POINTER   21
#define DARK_POINTER       22

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
	Unsigned8    unsigned8;
	Signed8      signed8;
	Unsigned16   unsigned16;
	Signed16     signed16;
	Unsigned32   unsigned32;
	Signed32     signed32;
	Unsigned64   unsigned64;
	Signed64     signed64;
	UnsignedSize unsignedSize;
	SignedSize   signedSize;
	Float32      float32;
	Float64      float64;
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
