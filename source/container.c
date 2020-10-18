Container *Container_create(UnsignedSize SIZE,Boolean FILL)
{
	Container *container;
	if (SIZE == 0) exception_globalThrowReturn("invalid SIZE");
	if ((container = calloc(1,sizeof(Container))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	if (FILL)
	{
		if ((container->pointer = calloc(1,SIZE)) == NULL) exception_globalThrowReturn("MEMORY: calloc");
	}
	else
	{
		if ((container->pointer = malloc(SIZE)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	};
	container->size = SIZE;
	return container;
};

Container *Container_createFromString(String *STRING)
{
	Container *container;
	if (STRING->data.length == 0) exception_globalThrowReturn("invalid STRING");
	if ((container = calloc(1,sizeof(Container))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	if ((container->pointer = malloc(STRING->data.length)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	memcpy(container->pointer,STRING->data.pointer,STRING->data.length);
	container->size = STRING->data.length;
	return container;
};

Container *Container_createFromBlob(Blob *BLOB)
{
	Container *container;
	if (BLOB->data.length == 0) exception_globalThrowReturn("invalid BLOB");
	if ((container = calloc(1,sizeof(Container))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	if ((container->pointer = malloc(BLOB->data.length)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	memcpy(container->pointer,BLOB->data.pointer,BLOB->data.length);
	container->size = BLOB->data.length;
	return container;
};

Container *Container_createFromMemory(Pointer POINTER,UnsignedSize SIZE)
{
	Container *container;
	if (POINTER == NULL) exception_globalThrowReturn("invalid POINTER");
	if (SIZE == 0) exception_globalThrowReturn("invalid SIZE");
	if ((container = calloc(1,sizeof(Container))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	if ((container->pointer = malloc(SIZE)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	memcpy(container->pointer,POINTER,SIZE);
	container->size = SIZE;
	return container;
};

Container *Container_createFromDisk(NullString PATH)
{
	Container *container;
	FILE *file;
	SignedSize size;
	if ((file = fopen(PATH,"rb")) == NULL) exception_globalThrowReturn("FILE: open");
	if (fseek(file,0,SEEK_END) != 0) exception_globalThrowReturn("FILE: seek");
	if ((size = ftell(file)) == -1) exception_globalThrowReturn("FILE: tell");
	if (fseek(file,0,SEEK_SET) != 0) exception_globalThrowReturn("FILE: seek");
	if (size == 0) exception_globalThrowReturn("invalid PATH");
	if ((container = calloc(1,sizeof(Container))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	if ((container->pointer = malloc(size)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	if (fread(container->pointer,1,size,file) != (UnsignedSize) size) exception_globalThrowReturn("FILE: read");
	if (fclose(file) == EOF) exception_globalThrowReturn("FILE: close");
	container->size = size;
	return container;
};

void Container_saveToDisk(Container *CONTAINER,NullString PATH)
{
	FILE *file;
	if ((file = fopen(PATH,"wb")) == NULL) exception_globalThrowExit("FILE: open");
	if (fwrite(CONTAINER->pointer,1,CONTAINER->size,file) != CONTAINER->size) exception_globalThrowExit("FILE: write");
	if (fclose(file) == EOF) exception_globalThrowExit("FILE: close");
};

Container *Container_clone(Container *CONTAINER)
{
	Container *container;
	if ((container = calloc(1,sizeof(Container))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	if ((container->pointer = malloc(CONTAINER->size)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	memcpy(container->pointer,CONTAINER->pointer,CONTAINER->size);
	container->size = CONTAINER->size;
	return container;
};

Container *Container_encapsulate(Pointer POINTER,UnsignedSize SIZE)
{
	Container *container;
	if (POINTER == NULL) exception_globalThrowReturn("invalid POINTER");
	if (SIZE == 0) exception_globalThrowReturn("invalid SIZE");
	if ((container = calloc(1,sizeof(Container))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	container->pointer = POINTER;
	container->size = SIZE;
	container->lock = true;
	return container;
};

Container *Container_destroy(Container *CONTAINER)
{
	if (!CONTAINER->lock) free(CONTAINER->pointer);
	else CONTAINER->lock = false;
	CONTAINER->pointer = NULL;
	CONTAINER->size = 0;
	free(CONTAINER);
	return NULL;
};

Pointer Container_getPointer(Container *CONTAINER)
{
	return CONTAINER->pointer;
};

void Container_setSize(Container *CONTAINER,UnsignedSize SIZE,Boolean FILL)
{
	Pointer pointer;
	if (CONTAINER->lock) exception_globalThrowExit("locked CONTAINER");
	if ((SIZE == 0) || (SIZE == CONTAINER->size)) exception_globalThrowExit("invalid SIZE");
	if ((pointer = realloc(CONTAINER->pointer,SIZE)) == NULL) exception_globalThrowExit("MEMORY: realloc");
	if (FILL && (SIZE > CONTAINER->size)) memset(pointer + CONTAINER->size,0,SIZE - CONTAINER->size);
	CONTAINER->pointer = pointer;
	CONTAINER->size = SIZE;
};

UnsignedSize Container_getSize(Container *CONTAINER)
{
	return CONTAINER->size;
};

void Container_setLock(Container *CONTAINER,Boolean LOCK)
{
	if (LOCK == CONTAINER->lock) exception_globalThrowExit("invalid LOCK");
	CONTAINER->lock = LOCK;
};

Boolean Container_getLock(Container *CONTAINER)
{
	return CONTAINER->lock;
};

void Container_debug(Container *CONTAINER,NullString MESSAGE)
{
	printf("CONTAINER: { pointer: %p, size: %lli, lock: %s } #%s\n",CONTAINER->pointer,CONTAINER->size,CONTAINER->lock? "true" : "false",MESSAGE);
};
