// Blob
#define DARK_BLOB_UNDEFINED_ENDIAN 0
#define DARK_BLOB_LITTLE_ENDIAN    1
#define DARK_BLOB_BIG_ENDIAN       2
#define DARK_BLOB_SYSTEM_ENDIAN    3

#define DARK_BLOB_BOOLEAN      0
#define DARK_BLOB_U8           1
#define DARK_BLOB_S8           2
#define DARK_BLOB_U16LE        3
#define DARK_BLOB_U16BE        4
#define DARK_BLOB_U16          5
#define DARK_BLOB_S16LE        6
#define DARK_BLOB_S16BE        7
#define DARK_BLOB_S16          8
#define DARK_BLOB_U32LE        9
#define DARK_BLOB_U32BE       10
#define DARK_BLOB_U32         11
#define DARK_BLOB_S32LE       12
#define DARK_BLOB_S32BE       13
#define DARK_BLOB_S32         14
#define DARK_BLOB_U64LE       15
#define DARK_BLOB_U64BE       16
#define DARK_BLOB_U64         17
#define DARK_BLOB_S64LE       18
#define DARK_BLOB_S64BE       19
#define DARK_BLOB_S64         20
#define DARK_BLOB_F32LE       21
#define DARK_BLOB_F32BE       22
#define DARK_BLOB_F32         23
#define DARK_BLOB_F64LE       24
#define DARK_BLOB_F64BE       25
#define DARK_BLOB_F64         26
#define DARK_BLOB_CHARACTER   27
#define DARK_BLOB_NULL_STRING 28
#define DARK_BLOB_RAW_STRING  29

DKblob *dkBlob_create(DKu8 ENDIAN);
DKblob *dkBlob_createFromMemory(DKu8 *SOURCE,DKusize LENGTH,DKssize START,DKssize END,DKu8 ENDIAN);
DKblob *dkBlob_createFromFile(DKnullString FILE_NAME,DKssize START,DKssize END,DKu8 ENDIAN);
DKblob *dkBlob_createFromCopy(DKblob *BLOB,DKssize START,DKssize END);
DKblob *dkBlob_destroy(DKblob *BLOB);
	void dkBlob_saveToFile(DKblob *BLOB,DKssize START,DKssize END,DKnullString FILE_NAME);
	void dkBlob_merge(DKblob *BLOB,DKssize OFFSET,DKblob *SOURCE,DKssize START,DKssize END);
	void dkBlob_clear(DKblob *BLOB);
	DKboolean dkBlob_compare(DKblob *BLOB1,DKblob *BLOB2);
		void dkBlob_insert(DKblob *BLOB,DKu8 *SOURCE,DKusize LENGTH);
		void dkBlob_insertAt(DKblob *BLOB,DKssize OFFSET,DKu8 *SOURCE,DKusize LENGTH);
		void dkBlob_insertHandle(DKblob *BLOB,DKvalue SOURCE,DKu8 TYPE);
		void dkBlob_insertHandleAt(DKblob *BLOB,DKssize OFFSET,DKvalue SOURCE,DKu8 TYPE);
		void dkBlob_write(DKblob *BLOB,DKu8 *SOURCE,DKusize LENGTH);
		void dkBlob_writeAt(DKblob *BLOB,DKssize OFFSET,DKu8 *SOURCE,DKusize LENGTH);
		void dkBlob_writeHandle(DKblob *BLOB,DKvalue SOURCE,DKu8 TYPE);
		void dkBlob_writeHandleAt(DKblob *BLOB,DKssize OFFSET,DKvalue SOURCE,DKu8 TYPE);
		DKu8 *dkBlob_read(DKblob *BLOB,DKusize LENGTH);
		DKu8 *dkBlob_readAt(DKblob *BLOB,DKssize OFFSET,DKusize LENGTH);
		DKvalue dkBlob_readHandle(DKblob *BLOB,DKu8 TYPE);
		DKvalue dkBlob_readHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE);
		void dkBlob_erase(DKblob *BLOB,DKusize LENGTH);
		void dkBlob_eraseAt(DKblob *BLOB,DKssize OFFSET,DKusize LENGTH);
		void dkBlob_eraseHandle(DKblob *BLOB,DKu8 TYPE);
		void dkBlob_eraseHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE);
		void dkBlob_remove(DKblob *BLOB,DKusize LENGTH);
		void dkBlob_removeAt(DKblob *BLOB,DKssize OFFSET,DKusize LENGTH);
		void dkBlob_removeHandle(DKblob *BLOB,DKu8 TYPE);
		void dkBlob_removeHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE);
			DKu8 dkBlob_setEndian(DKblob *BLOB,DKu8 ENDIAN);
			DKu8 dkBlob_getEndian(DKblob *BLOB);
			DKusize dkBlob_setOffset(DKblob *BLOB,DKusize OFFSET);
			DKusize dkBlob_resetOffset(DKblob *BLOB);
			DKusize dkBlob_getOffset(DKblob *BLOB);
			DKu8 *dkBlob_getSource(DKblob *BLOB);
			DKusize dkBlob_setLength(DKblob *BLOB,DKusize LENGTH);
			DKusize dkBlob_getLength(DKblob *BLOB);
			DKboolean dkBlob_isEmpty(DKblob *BLOB);
			DKboolean dkBlob_isNotEmpty(DKblob *BLOB);
			DKboolean dkBlob_setLock(DKblob *BLOB,DKboolean LOCK);
			DKboolean dkBlob_getLock(DKblob *BLOB);
				void dkBlob_debug(DKblob *BLOB,DKnullString LABEL);
