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
#define DKnstring char*
#define DKpointer void*
typedef struct _string DKstring;
typedef struct _buffer DKbuffer;

// Error
void dkError_start(void);
void dkError_end(void);
DKnstring dkError_catch(void);
void dkError_throw(DKnstring MESSAGE);
void dkError_debug(DKnstring MESSAGE);

//Scalar
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
	DKnstring nstring;
	DKpointer pointer;
	DKstring *string;
	DKbuffer *buffer;
} DKscalar;

// String
#define DARK_STRING_LOWER_CASE     0
#define DARK_STRING_UPPER_CASE     1
#define DARK_STRING_PROPER_CASE    2
#define DARK_STRING_ALTERNATE_CASE 3
#define DARK_STRING_INVERT_CASE    4

#define DARK_STRING_TRIM_START 0
#define DARK_STRING_TRIM_END   1
#define DARK_STRING_TRIM_ALL   2

DKstring *dkString_create(void);
DKstring *dkString_createFromRaw(DKnstring SOURCE,DKusize SIZE,DKssize START,DKssize END);
DKstring *dkString_createFromFile(DKnstring FILE_NAME,DKssize START,DKssize END);
DKstring *dkString_createFromCopy(DKstring *STRING,DKssize START,DKssize END);
DKstring *dkString_destroy(DKstring *STRING);
	void dkString_save(DKstring *STRING,DKssize START,DKssize END,DKnstring FILE_NAME);
	void dkString_merge(DKstring *STRING,DKssize INDEX,DKstring *SOURCE,DKssize START,DKssize END);
	void dkString_clear(DKstring *STRING);
	DKboolean dkString_compare(DKstring *STRING1,DKstring *STRING2);
		void dkString_convert(DKstring *STRING,DKu8 TYPE);
		void dkString_trim(DKstring *STRING,DKu8 TYPE);
			DKcharacter dkString_getCharacter(DKstring *STRING,DKssize INDEX);
			DKnstring dkString_getSource(DKstring *STRING);
			DKusize dkString_getLength(DKstring *STRING);
			DKboolean dkString_isEmpty(DKstring *STRING);
			void dkString_setLock(DKstring *STRING,DKboolean LOCK);
			DKboolean dkString_getLock(DKstring *STRING);
void dkString_debug(DKstring *STRING,DKnstring LABEL);

// Buffer
#define DARK_BUFFER_UNDEFINED_ENDIAN 0
#define DARK_BUFFER_LITTLE_ENDIAN    1
#define DARK_BUFFER_BIG_ENDIAN       2
#define DARK_BUFFER_SYSTEM_ENDIAN    3

#define DARK_BUFFER_BOOLEAN    0
#define DARK_BUFFER_U8         1
#define DARK_BUFFER_S8         2
#define DARK_BUFFER_U16LE      3
#define DARK_BUFFER_U16BE      4
#define DARK_BUFFER_U16        5
#define DARK_BUFFER_S16LE      6
#define DARK_BUFFER_S16BE      7
#define DARK_BUFFER_S16        8
#define DARK_BUFFER_U32LE      9
#define DARK_BUFFER_U32BE     10
#define DARK_BUFFER_U32       11
#define DARK_BUFFER_S32LE     12
#define DARK_BUFFER_S32BE     13
#define DARK_BUFFER_S32       14
#define DARK_BUFFER_U64LE     15
#define DARK_BUFFER_U64BE     16
#define DARK_BUFFER_U64       17
#define DARK_BUFFER_S64LE     18
#define DARK_BUFFER_S64BE     19
#define DARK_BUFFER_S64       20
#define DARK_BUFFER_F32LE     21
#define DARK_BUFFER_F32BE     22
#define DARK_BUFFER_F32       23
#define DARK_BUFFER_F64LE     24
#define DARK_BUFFER_F64BE     25
#define DARK_BUFFER_F64       26
#define DARK_BUFFER_CHARACTER 27
#define DARK_BUFFER_NSTRING   28
#define DARK_BUFFER_RSTRING   29

DKbuffer *dkBuffer_create(DKu8 ENDIAN);
DKbuffer *dkBuffer_createFromRaw(DKu8 *SOURCE,DKusize SIZE,DKssize START,DKssize END,DKu8 ENDIAN);
DKbuffer *dkBuffer_createFromFile(DKnstring FILE_NAME,DKssize START,DKssize END,DKu8 ENDIAN);
DKbuffer *dkBuffer_createFromCopy(DKbuffer *BUFFER,DKssize START,DKssize END);
DKbuffer *dkBuffer_destroy(DKbuffer *BUFFER);
	void dkBuffer_save(DKbuffer *BUFFER,DKssize START,DKssize END,DKnstring FILE_NAME);
	void dkBuffer_merge(DKbuffer *BUFFER,DKssize OFFSET,DKbuffer *SOURCE,DKssize START,DKssize END);
	void dkBuffer_clear(DKbuffer *BUFFER);
	DKboolean dkBuffer_compare(DKbuffer *BUFFER1,DKbuffer *BUFFER2);
		void dkBuffer_insertScalar(DKbuffer *BUFFER,DKscalar SOURCE,DKu8 TYPE);
		void dkBuffer_insertScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKscalar SOURCE,DKu8 TYPE);
		void dkBuffer_insertRaw(DKbuffer *BUFFER,DKu8 *SOURCE,DKusize SIZE);
		void dkBuffer_insertRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE);
		void dkBuffer_writeScalar(DKbuffer *BUFFER,DKscalar SOURCE,DKu8 TYPE);
		void dkBuffer_writeScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKscalar SOURCE,DKu8 TYPE);
		void dkBuffer_writeRaw(DKbuffer *BUFFER,DKu8 *SOURCE,DKusize SIZE);
		void dkBuffer_writeRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE);
		DKscalar dkBuffer_readScalar(DKbuffer *BUFFER,DKu8 TYPE);
		DKscalar dkBuffer_readScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE);
		DKu8 *dkBuffer_readRaw(DKbuffer *BUFFER,DKusize SIZE);
		DKu8 *dkBuffer_readRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE);
		void dkBuffer_eraseScalar(DKbuffer *BUFFER,DKu8 TYPE);
		void dkBuffer_eraseScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE);
		void dkBuffer_eraseRaw(DKbuffer *BUFFER,DKusize SIZE);
		void dkBuffer_eraseRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE);
		void dkBuffer_removeScalar(DKbuffer *BUFFER,DKu8 TYPE);
		void dkBuffer_removeScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE);
		void dkBuffer_removeRaw(DKbuffer *BUFFER,DKusize SIZE);
		void dkBuffer_removeRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE);
			DKu8 dkBuffer_setEndian(DKbuffer *BUFFER,DKu8 ENDIAN);
			DKu8 dkBuffer_getEndian(DKbuffer *BUFFER);
			DKusize dkBuffer_setOffset(DKbuffer *BUFFER,DKusize OFFSET);
			DKusize dkBuffer_resetOffset(DKbuffer *BUFFER);
			DKusize dkBuffer_getOffset(DKbuffer *BUFFER);
			DKu8 *dkBuffer_getSource(DKbuffer *BUFFER);
			DKusize dkBuffer_setSize(DKbuffer *BUFFER,DKusize SIZE);
			DKusize dkBuffer_getSize(DKbuffer *BUFFER);
			DKboolean dkBuffer_isEmpty(DKbuffer *BUFFER);
			void dkBuffer_setLock(DKbuffer *BUFFER,DKboolean LOCK);
			DKboolean dkBuffer_getLock(DKbuffer *BUFFER);
void dkBuffer_debug(DKbuffer *BUFFER,DKnstring LABEL);
