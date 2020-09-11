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
