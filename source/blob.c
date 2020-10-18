NullString blob_endianToNullString[3] = {"UNDEFINED","LITTLE","BIG"};

#routine blob_adjustCapacity(EXCEPTION,DATA,LENGTH)
{
	data_adjustCapacity(EXCEPTION,DATA,LENGTH,Unsigned8);
};

#routine blob_calculateEndian(EXCEPTION,ENDIAN,RETURN)
{
	switch (ENDIAN)
	{
		case DARK_BLOB_UNDEFINED_ENDIAN:
		case DARK_BLOB_LITTLE_ENDIAN:
		case DARK_BLOB_BIG_ENDIAN: RETURN = ENDIAN; break;
		case DARK_BLOB_SYSTEM_ENDIAN: RETURN = DARK_ENDIAN; break;
		default: exception_routineThrow(EXCEPTION,"invalid ENDIAN");
	};
};

Blob *Blob_create(Unsigned8 ENDIAN)
{
	Blob *blob;
	if ((blob = calloc(1,sizeof(Blob))) == NULL) exception_globalThrowReturn("MEMORY: calloc");
	blob_calculateEndian(ExceptionGlobal,ENDIAN,blob->endian);
	if ((blob->data.pointer = malloc(1)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	blob->data.length = 0;
	blob->data.capacity = 1;
	return blob;
};

Blob *Blob_createFromContainer(Container *CONTAINER,Unsigned8 ENDIAN)
{
	Blob *blob;
	if ((blob = calloc(1,sizeof(Blob))) == NULL) exception_globalThrowReturn("MEMORY: calloc");
	blob_calculateEndian(ExceptionGlobal,ENDIAN,blob->endian);
	if ((blob->data.pointer = malloc(CONTAINER->size)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	memcpy(blob->data.pointer,CONTAINER->pointer,CONTAINER->size);
	blob->data.length = CONTAINER->size;
	blob->data.capacity = CONTAINER->size;
	return blob;
};

Blob *Blob_clone(Blob *BLOB)
{
	Blob *blob;
	if ((blob = calloc(1,sizeof(Blob))) == NULL) exception_globalThrowReturn("MEMORY: calloc");
	blob_calculateEndian(BLOB->exception,BLOB->endian,blob->endian);
	if ((blob->data.pointer = malloc(BLOB->data.length)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	memcpy(blob->data.pointer,BLOB->data.pointer,BLOB->data.length);
	blob->data.length = BLOB->data.length;
	blob->data.capacity = BLOB->data.length;
	return blob;
};

Blob *Blob_destroy(Blob *BLOB)
{
	mutex_lock(BLOB);
	BLOB->endian = 0;
	BLOB->offset = 0;
	free(BLOB->data.pointer);
	BLOB->data.pointer = NULL;
	BLOB->data.length = 0;
	BLOB->data.capacity = 0;
	mutex_destroy(BLOB);
	exception_destroy(BLOB);
	free(BLOB);
	return NULL;
};

Boolean Blob_compare(Blob *BLOB1,Blob *BLOB2)
{
	Boolean comparison;
	mutex_lock(BLOB1);
	mutex_lock(BLOB2);
	data_compare(BLOB1->data,BLOB2->data,pointer,Unsigned8,comparison);
	mutex_unlock(BLOB2);
	mutex_unlock(BLOB1);
	return comparison;
};

void Blob_merge(Blob *TARGET,SignedSize INDEX,Blob *SOURCE)
{
	mutex_lock(TARGET);
	mutex_lock(SOURCE);
	data_merge(TARGET->exception,TARGET->data,INDEX,SOURCE->data,blob_adjustCapacity,pointer,Unsigned8);
	mutex_unlock(SOURCE);
	mutex_unlock(TARGET);
};

void Blob_clear(Blob *BLOB)
{
	mutex_lock(BLOB);
	data_clear(BLOB->exception,BLOB->data,Unsigned8);
	mutex_unlock(BLOB);
};

void Blob_setEndian(Blob *BLOB,Unsigned8 ENDIAN)
{
	mutex_lock(BLOB);
	blob_calculateEndian(BLOB->exception,ENDIAN,BLOB->endian);
	mutex_unlock(BLOB);
};

Unsigned8 Blob_getEndian(Blob *BLOB)
{
	mutex_lock(BLOB);
	Unsigned8 endian = BLOB->endian;
	mutex_unlock(BLOB);
	return endian;
};

void Blob_setOffset(Blob *BLOB,UnsignedSize OFFSET)
{
	mutex_lock(BLOB);
	BLOB->offset = OFFSET;
	mutex_unlock(BLOB);
};

void Blob_resetOffset(Blob *BLOB)
{
	mutex_lock(BLOB);
	BLOB->offset = 0;
	mutex_unlock(BLOB);
};

UnsignedSize Blob_getOffset(Blob *BLOB)
{
	mutex_lock(BLOB);
	UnsignedSize offset = BLOB->offset;
	mutex_unlock(BLOB);
	return offset;
};

void Blob_setLength(Blob *BLOB,UnsignedSize LENGTH)
{
	mutex_lock(BLOB);
	data_setLength(BLOB->exception,BLOB->data,LENGTH,blob_adjustCapacity,pointer,Unsigned8,0);
	mutex_unlock(BLOB);
};

UnsignedSize Blob_getLength(Blob *BLOB)
{
	mutex_lock(BLOB);
	UnsignedSize length = BLOB->data.length;
	mutex_unlock(BLOB);
	return length;
};

Boolean Blob_isEmpty(Blob *BLOB)
{
	mutex_lock(BLOB);
	Boolean empty = BLOB->data.length == 0;
	mutex_unlock(BLOB);
	return empty;
};

Boolean Blob_isNotEmpty(Blob *BLOB)
{
	mutex_lock(BLOB);
	Boolean empty = BLOB->data.length != 0;
	mutex_unlock(BLOB);
	return empty;
};

void Blob_setMutex(Blob *BLOB,Boolean LOCK)
{
	mutex_lock(BLOB);
	mutex_setLock(BLOB,LOCK);
	mutex_unlock(BLOB);
};

Boolean Blob_getMutex(Blob *BLOB)
{
	Boolean lock;
	mutex_lock(BLOB);
	mutex_getLock(BLOB,lock);
	mutex_unlock(BLOB);
	return lock;
};

NullString Blob_getException(Blob *BLOB)
{
	NullString message;
	mutex_lock(BLOB);
	exception_getMessage(BLOB,message);
	mutex_unlock(BLOB);
	return message;
};

void Blob_debug(Blob *BLOB,NullString MESSAGE)
{
	mutex_lock(BLOB);
	printf("BLOB: { endian: %s, offset: %lli, length: %lli, capacity: %lli, < ",blob_endianToNullString[BLOB->endian],BLOB->offset,BLOB->data.length,BLOB->data.capacity);
	for (UnsignedSize index = 0; index < BLOB->data.length; ++index) printf("%lli ",(UnsignedSize) BLOB->data.pointer[index]);
	printf("> } #%s\n",MESSAGE);
	mutex_unlock(BLOB);
};
