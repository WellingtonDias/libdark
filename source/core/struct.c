#macro struct_create(#TYPE,STRUCT)
{
	if (!(STRUCT = malloc(sizeof(TYPE)))) error_throwReturn("MEMORY: malloc");
	mutex_update(STRUCT->mutex,NULL);
};

#macro struct_createFromNothing(#STRUCT_TYPE,#BLOCK_TYPE,STRUCT)
{
	struct_create(STRUCT_TYPE,STRUCT);
	block_createFromNothing(STRUCT->block,BLOCK_TYPE);
};

#macro struct_createFromMemory(#STRUCT_TYPE,#BLOCK_TYPE,SOURCE,SIZE,START,END,STRUCT)
{
	struct_create(STRUCT_TYPE,STRUCT);
	block_createFromMemory(STRUCT->block,BLOCK_TYPE,SOURCE,SIZE,START,END);
};

#macro struct_destroy(STRUCT)
{
	block_destroy(STRUCT->block);
	mutex_destroy(STRUCT->mutex);
	free(STRUCT);
};
