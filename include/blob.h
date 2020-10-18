// Blob
#define DARK_BLOB_UNDEFINED_ENDIAN 0
#define DARK_BLOB_LITTLE_ENDIAN    1
#define DARK_BLOB_BIG_ENDIAN       2
#define DARK_BLOB_SYSTEM_ENDIAN    3

Blob *Blob_create(Unsigned8 ENDIAN);
Blob *Blob_createFromContainer(Container *CONTAINER,Unsigned8 ENDIAN);
Blob *Blob_clone(Blob *BLOB);
Blob *Blob_destroy(Blob *BLOB);

Boolean Blob_compare(Blob *BLOB1,Blob *BLOB2);
void Blob_merge(Blob *BLOB,SignedSize OFFSET,Blob *SOURCE);
void Blob_clear(Blob *BLOB);

void Blob_setEndian(Blob *BLOB,Unsigned8 ENDIAN);
Unsigned8 Blob_getEndian(Blob *BLOB);
void Blob_setOffset(Blob *BLOB,UnsignedSize OFFSET);
void Blob_resetOffset(Blob *BLOB);
UnsignedSize Blob_getOffset(Blob *BLOB);
void Blob_setLength(Blob *BLOB,UnsignedSize LENGTH);
UnsignedSize Blob_getLength(Blob *BLOB);
Boolean Blob_isEmpty(Blob *BLOB);
Boolean Blob_isNotEmpty(Blob *BLOB);
void Blob_setMutex(Blob *BLOB,Boolean LOCK);
Boolean Blob_getMutex(Blob *BLOB);
NullString Blob_getException(Blob *BLOB);

void Blob_debug(Blob *BLOB,NullString MESSAGE);
