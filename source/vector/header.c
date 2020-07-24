block_define(DKblock_scalar,DKscalar);

struct _vector
{
	DKblock_scalar block;
	DKmutex mutex;
};

void dkVector_debug(DKvector *VECTOR,DKnstring LABEL)
{
	safe_start(VECTOR);
	printf("VECTOR { size: %lli, capacity: %lli, source: [ ",(VECTOR->block).size,(VECTOR->block).capacity);
	for (DKusize i = 0; i < (VECTOR->block).size; ++i) printf("%lli ",(VECTOR->block).start[i].usize);
	printf("] } #%s\n",LABEL);
	safe_end(VECTOR);
};
