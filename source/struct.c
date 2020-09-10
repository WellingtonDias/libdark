#routine struct_allocate(#TYPE,RETURN)
{
	if (!(RETURN = calloc(1,sizeof(TYPE)))) exception_globalThrowBreak("MEMORY: calloc");
};

#routine struct_create(#STRUCT_TYPE,#BLOCK_TYPE,RETURN)
{
	struct_allocate(STRUCT_TYPE,RETURN);
	exception_globalBypassBreak();
	block_create(BLOCK_TYPE,RETURN->block);
};

#routine struct_createFromContainer(#STRUCT_TYPE,#BLOCK_TYPE,CONTAINER,RETURN)
{
	struct_allocate(STRUCT_TYPE,RETURN);
	exception_globalBypassBreak();
	block_createFromContainer(BLOCK_TYPE,RETURN->block,CONTAINER);
};

#routine struct_createFromMemory(#STRUCT_TYPE,#BLOCK_TYPE,CONTAINER,START,END,RETURN)
{
	struct_allocate(STRUCT_TYPE,RETURN);
	exception_globalBypassBreak();
	block_createFromMemory(BLOCK_TYPE,RETURN->block,CONTAINER,START,END);
};

#routine struct_createFromCopy(#STRUCT_TYPE,#BLOCK_TYPE,STRUCT,START,END,RETURN)
{
	struct_allocate(STRUCT_TYPE,RETURN);
	exception_globalBypassBreak();
	block_createFromCopy(BLOCK_TYPE,RETURN->block,STRUCT->block,START,END);
};

#routine struct_destroy(STRUCT,DEALLOCATE)
{
	block_destroy(STRUCT->block,DEALLOCATE);
	mutex_destroy(STRUCT->mutex);
	exception_destroy(STRUCT->exception);
	free(STRUCT);
};
