struct _Pointer
{
	RawPointer   source;
	UnsignedSize size;
};

#macro pointer_getSource(POINTER)
{
	POINTER->source
};

#macro pointer_getSize(POINTER)
{
	POINTER->size
};

Pointer *pointer_encapsulate(RawPointer RAW_POINTER,UnsignedSize SIZE)
{
	Pointer *pointer;
	if (!(pointer = malloc(sizeof(Pointer*)))) exception_throwReturn("MEMORY: malloc");
	pointer->source = RAW_POINTER;
	pointer->size = SIZE;
	return pointer;
};

Pointer *pointer_allocate(UnsignedSize SIZE)
{
	Pointer *pointer;
	if (!(pointer = malloc(sizeof(Pointer*)))) exception_throwReturn("MEMORY: malloc");
	if (!(pointer->source = malloc(SIZE))) exception_throwReturn("MEMORY: malloc");
	pointer->size = SIZE;
	return pointer;
};

Pointer *pointer_zeroedAllocate(UnsignedSize SIZE)
{
	Pointer *pointer;
	if (!(pointer = malloc(sizeof(Pointer*)))) exception_throwReturn("MEMORY: malloc");
	if (!(pointer->source = calloc(1,SIZE))) exception_throwReturn("MEMORY: calloc");
	pointer->size = SIZE;
	return pointer;
};

void pointer_reallocate(Pointer *POINTER,UnsignedSize SIZE)
{
	if (!(POINTER->source = realloc(POINTER->source,SIZE))) exception_throwExit("MEMORY: realloc");
	POINTER->size = SIZE;
};

Pointer *pointer_free(Pointer *POINTER)
{
	free(POINTER->source);
	free(POINTER);
	return NULL;
};
