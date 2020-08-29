#routine struct_allocate(#TYPE,STRUCT)
{
	if (!(STRUCT = calloc(1,sizeof(TYPE)))) error_throwBreak("MEMORY: calloc");
};

#routine struct_create(#STRUCT_TYPE,#BLOCK_TYPE,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	block_create(BLOCK_TYPE,STRUCT->block);
};

#routine struct_createFromPointer(#STRUCT_TYPE,#BLOCK_TYPE,ADDRESS,SIZE,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	block_createFromPointer(BLOCK_TYPE,STRUCT->block,ADDRESS,SIZE);
};

#routine struct_createFromMemory(#STRUCT_TYPE,#BLOCK_TYPE,ADDRESS,SIZE,START,END,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	block_createFromMemory(BLOCK_TYPE,STRUCT->block,ADDRESS,SIZE,START,END);
};

#routine struct_createFromCopy(#STRUCT_TYPE,#BLOCK_TYPE,SOURCE,START,END,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	block_createFromMemory(BLOCK_TYPE,STRUCT->block,block_getStart(SOURCE->block),block_getSize(SOURCE->block),START,END);
};

#routine struct_destroy(STRUCT,SOURCE)
{
	if (SOURCE) block_destroy(STRUCT->block);
	mutex_destroy(STRUCT->mutex);
	free(STRUCT);
};
