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

#routine struct_destroy(STRUCT)
{
	block_destroy(STRUCT->block);
	mutex_destroy(STRUCT->mutex);
	exception_destroy(STRUCT->exception);
	free(STRUCT);
};
