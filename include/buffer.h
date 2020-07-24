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
DKbuffer *dkBuffer_createFromMemory(DKu8 *SOURCE,DKusize SIZE,DKssize START,DKssize END,DKu8 ENDIAN);
DKbuffer *dkBuffer_createFromFile(DKnstring FILE_NAME,DKssize START,DKssize END,DKu8 ENDIAN);
DKbuffer *dkBuffer_createFromCopy(DKbuffer *BUFFER,DKssize START,DKssize END);
DKbuffer *dkBuffer_destroy(DKbuffer *BUFFER);
	void dkBuffer_saveToFile(DKbuffer *BUFFER,DKssize START,DKssize END,DKnstring FILE_NAME);
	void dkBuffer_merge(DKbuffer *BUFFER,DKssize OFFSET,DKbuffer *SOURCE,DKssize START,DKssize END);
	void dkBuffer_clear(DKbuffer *BUFFER);
	DKboolean dkBuffer_compare(DKbuffer *BUFFER1,DKbuffer *BUFFER2);
		// void dkBuffer_insertHandle(DKbuffer *BUFFER,DKhandle SOURCE,DKu8 TYPE);
		// void dkBuffer_insertHandleAt(DKbuffer *BUFFER,DKssize OFFSET,DKhandle SOURCE,DKu8 TYPE);
		// void dkBuffer_insertRaw(DKbuffer *BUFFER,DKu8 *SOURCE,DKusize SIZE);
		// void dkBuffer_insertRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE);
		// void dkBuffer_writeHandle(DKbuffer *BUFFER,DKhandle SOURCE,DKu8 TYPE);
		// void dkBuffer_writeHandleAt(DKbuffer *BUFFER,DKssize OFFSET,DKhandle SOURCE,DKu8 TYPE);
		// void dkBuffer_writeRaw(DKbuffer *BUFFER,DKu8 *SOURCE,DKusize SIZE);
		// void dkBuffer_writeRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE);
		// DKhandle dkBuffer_readHandle(DKbuffer *BUFFER,DKu8 TYPE);
		// DKhandle dkBuffer_readHandleAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE);
		// DKu8 *dkBuffer_readRaw(DKbuffer *BUFFER,DKusize SIZE);
		// DKu8 *dkBuffer_readRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE);
		// void dkBuffer_eraseHandle(DKbuffer *BUFFER,DKu8 TYPE);
		// void dkBuffer_eraseHandleAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE);
		// void dkBuffer_eraseRaw(DKbuffer *BUFFER,DKusize SIZE);
		// void dkBuffer_eraseRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE);
		// void dkBuffer_removeHandle(DKbuffer *BUFFER,DKu8 TYPE);
		// void dkBuffer_removeHandleAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE);
		// void dkBuffer_removeRaw(DKbuffer *BUFFER,DKusize SIZE);
		// void dkBuffer_removeRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE);
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
