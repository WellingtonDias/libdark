#routine struct_allocate(#TYPE,STRUCT)
{
	if (!(STRUCT = calloc(1,sizeof(TYPE)))) exception_throwBreak("MEMORY: calloc");
};

#routine struct_create(#STRUCT_TYPE,#BLOCK_TYPE,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	block_create(BLOCK_TYPE,STRUCT->block);
};

#routine struct_createFromPointer(#STRUCT_TYPE,#BLOCK_TYPE,POINTER,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	block_createFromPointer(BLOCK_TYPE,STRUCT->block,POINTER);
};

#routine struct_createFromMemoryAtInterval(#STRUCT_TYPE,#BLOCK_TYPE,POINTER,INDEX,SIZE,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	block_createFromMemoryAtInterval(BLOCK_TYPE,STRUCT->block,POINTER,INDEX,SIZE);
};

#routine struct_createFromMemoryAtRange(#STRUCT_TYPE,#BLOCK_TYPE,POINTER,START,END,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	block_createFromMemoryAtRange(BLOCK_TYPE,STRUCT->block,POINTER,START,END);
};

#routine struct_createFromCopyAtInterval(#STRUCT_TYPE,#BLOCK_TYPE,SOURCE,INDEX,SIZE,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	block_createFromCopyAtInterval(BLOCK_TYPE,STRUCT->block,SOURCE->block,INDEX,SIZE);
};

#routine struct_createFromCopyAtRange(#STRUCT_TYPE,#BLOCK_TYPE,SOURCE,START,END,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	block_createFromCopyAtRange(BLOCK_TYPE,STRUCT->block,SOURCE->block,START,END);
};

#routine struct_destroy(STRUCT,SOURCE)
{
	if (SOURCE) block_destroy(STRUCT->block);
	mutex_destroy(STRUCT->mutex);
	free(STRUCT);
};
