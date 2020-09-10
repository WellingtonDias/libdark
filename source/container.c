struct _Container
{
	Pointer      pointer;
	UnsignedSize size;
};

#macro container_getPointer(CONTAINER)
{
	CONTAINER->pointer
};

#macro container_getSize(CONTAINER)
{
	CONTAINER->size
};

Container *Container_create(UnsignedSize SIZE,Boolean FILL)
{
	Container *container;
	if (SIZE == 0) exception_globalThrowReturn("invalid SIZE");
	if (!(container = malloc(sizeof(Container)))) exception_globalThrowReturn("MEMORY: malloc");
	if (FILL)
	{
		if (!(container->pointer = calloc(1,SIZE))) exception_globalThrowReturn("MEMORY: calloc");
	}
	else
	{
		if (!(container->pointer = malloc(SIZE))) exception_globalThrowReturn("MEMORY: malloc");
	};
	container->size = SIZE;
	return container;
};

Container *Container_createFromMemory(Pointer POINTER,UnsignedSize SIZE)
{
	Container *container;
	if (POINTER == NULL) exception_globalThrowReturn("invalid POINTER");
	if (SIZE == 0) exception_globalThrowReturn("invalid SIZE");
	if (!(container = malloc(sizeof(Container)))) exception_globalThrowReturn("MEMORY: malloc");
	container->pointer = POINTER;
	container->size = SIZE;
	return container;
};

container *Container_createFromDisk(NullString PATH);
{
	Container *container;
	FILE *file;
	SignedSize size;
	if (!(file = fopen(PATH,"rb"))) exception_globalThrowReturn("FILE: open");
	if (fseek(file,0,SEEK_END) != 0) exception_globalThrowReturn("FILE: seek");
	if ((size = ftell(file)) == -1) exception_globalThrowReturn("FILE: tell");
	if (size == 0) exception_globalThrowReturn("invalid PATH");
	if (!(container = malloc(sizeof(Container)))) exception_globalThrowReturn("MEMORY: malloc");
	if (!(container->pointer = malloc(size))) exception_globalThrowReturn("MEMORY: malloc");
	if (fseek(file,0,SEEK_SET) != 0) exception_globalThrowReturn("FILE: seek");
	if (fread(container->pointer,1,size,file) != size) exception_globalThrowReturn("FILE: read");
	container->size = size;
	if (fclose(file) != 0) exception_globalThrowReturn("FILE: close");
	return container;
};

void Container_saveToDisk(Container *CONTAINER,NullString PATH)
{
	FILE *file;
	if (CONTAINER->pointer == NULL) exception_globalThrowExit("invalid CONTAINER");
	if (!(file = fopen(PATH,"wb"))) exception_globalThrowExit("FILE: open");
	if (fwrite(CONTAINER->pointer,1,CONTAINER->size,file) != CONTAINER->size) exception_globalThrowExit("FILE: write");
	if (fclose(file) != 0) exception_globalThrowExit("FILE: close");
};

Container *Container_destroy(Container *CONTAINER)
{
	if (CONTAINER->pointer == NULL) exception_globalThrowReturn("invalid CONTAINER");
	free(CONTAINER->pointer);
	CONTAINER->pointer = NULL;
	CONTAINER->size = 0;
	free(CONTAINER);
	return NULL;
};

Pointer Container_getPointer(Container *CONTAINER)
{
	if (CONTAINER->pointer == NULL) exception_globalThrowReturn("invalid CONTAINER");
	return CONTAINER->pointer;
};

UnsignedSize Container_setSize(Container *CONTAINER,UnsignedSize SIZE)
{
	Pointer pointer;
	if (CONTAINER->pointer == NULL) exception_globalThrowReturn("invalid CONTAINER");
	if (SIZE == 0) exception_globalThrowReturn("invalid SIZE");
	if (!(pointer = realloc(CONTAINER->pointer,SIZE))) exception_globalThrowReturn("MEMORY: realloc");
	CONTAINER->pointer = pointer;
	UnsignedSize size = CONTAINER->size;
	CONTAINER->size = SIZE;
	return size;
};

UnsignedSize Container_getSize(Container *CONTAINER)
{
	if (CONTAINER->pointer == NULL) exception_globalThrowReturn("invalid CONTAINER");
	return CONTAINER->size;
};
