void dkVector_merge(DKvector *VECTOR,DKssize INDEX,DKvector *SOURCE,DKssize START,DKssize END)
{
	safe_start(VECTOR);
	mutex_lock(SOURCE->mutex);
	block_merge(VECTOR->block,DKscalar,INDEX,SOURCE->block,START,END);
	mutex_unlock(SOURCE->mutex);
	safe_end(VECTOR);
};

void dkVector_clear(DKvector *VECTOR)
{
	safe_start(VECTOR);
	block_clear(VECTOR->block,DKscalar);
	safe_end(VECTOR);
};

DKboolean dkVector_compare(DKvector *VECTOR1,DKvector *VECTOR2)
{
	safe_start(VECTOR1);
	mutex_lock(VECTOR2->mutex);
	DKboolean comparison = block_compare(VECTOR1->block,VECTOR2->block,DKscalar);
	mutex_unlock(VECTOR2->mutex);
	safe_endReturn(VECTOR1,comparison);
};
