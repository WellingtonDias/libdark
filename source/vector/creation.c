DKvector *dkVector_create(void)
{
	DKvector *vector;
	unsafe_start();
	struct_createFromNothing(DKvector,DKscalar,vector);
	return vector;
};

DKvector *dkVector_createFromCopy(DKvector *VECTOR,DKssize START,DKssize END)
{
	DKvector *vector;
	safe_start(VECTOR);
	struct_createFromMemory(DKvector,DKscalar,(VECTOR->block).start,(VECTOR->block).size,START,END,vector);
	safe_endReturn(VECTOR,vector);
};

DKvector *dkVector_destroy(DKvector *VECTOR)
{
	safe_start(VECTOR);
	struct_destroy(VECTOR);
	return NULL;
};
