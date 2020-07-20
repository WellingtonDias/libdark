DKusize dkVector_setSize(DKvector *VECTOR,DKusize SIZE)
{
	DKusize size;
	safe_start(VECTOR);
	block_setSize(VECTOR->block,DKscalar,SIZE,size);
	safe_endReturn(VECTOR,size);
};

DKusize dkVector_getSize(DKvector *VECTOR)
{
	safe_start(VECTOR);
	DKusize size = block_getSize(VECTOR->block);
	safe_endReturn(VECTOR,size);
};

DKboolean dkVector_isEmpty(DKvector *VECTOR)
{
	safe_start(VECTOR);
	DKboolean empty = block_isEmpty(VECTOR->block);
	safe_endReturn(VECTOR,empty);
};

void dkVector_setLock(DKvector *VECTOR,DKboolean LOCK)
{
	safe_start(VECTOR);
	mutex_setLock(VECTOR->mutex,LOCK);
	safe_end(VECTOR);
};

DKboolean dkVector_getLock(DKvector *VECTOR)
{
	safe_start(VECTOR);
	DKboolean lock = mutex_getLock(VECTOR->mutex);
	safe_endReturn(VECTOR,lock);
};
