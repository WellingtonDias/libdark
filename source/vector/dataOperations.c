void dkVector_prepend(DKvector *VECTOR,DKscalar VALUE)
{
	safe_start(VECTOR);
	stream_prepend(VECTOR->block,DKscalar,VALUE);
	safe_end(VECTOR);
};

void dkVector_insert(DKvector *VECTOR,DKssize INDEX,DKscalar VALUE)
{
	safe_start(VECTOR);
	stream_insert(VECTOR->block,DKscalar,INDEX,VALUE);
	safe_end(VECTOR);
};

void dkVector_append(DKvector *VECTOR,DKscalar VALUE)
{
	safe_start(VECTOR);
	stream_append(VECTOR->block,DKscalar,VALUE);
	safe_end(VECTOR);
};

DKscalar dkVector_replace(DKvector *VECTOR,DKssize INDEX,DKscalar VALUE)
{
	DKscalar value;
	safe_start(VECTOR);
	stream_replace(VECTOR->block,DKscalar,INDEX,VALUE,value);
	safe_endCastReturn(VECTOR,value,DKscalar);
};

DKscalar dkVector_set(DKvector *VECTOR,DKssize INDEX,DKscalar VALUE)
{
	DKscalar value;
	safe_start(VECTOR);
	stream_set(VECTOR->block,DKscalar,INDEX,VALUE,value);
	safe_endCastReturn(VECTOR,value,DKscalar);
};

void dkVector_swap(DKvector *VECTOR,DKssize INDEX1,DKssize INDEX2)
{
	safe_start(VECTOR);
	stream_swap(VECTOR->block,DKscalar,INDEX1,INDEX2);
	safe_end(VECTOR);
};

DKscalar dkVector_getFront(DKvector *VECTOR)
{
	DKscalar value;
	safe_start(VECTOR);
	stream_getFront(VECTOR->block,DKscalar,value);
	safe_endCastReturn(VECTOR,value,DKscalar);
};

DKscalar dkVector_getIndex(DKvector *VECTOR,DKssize INDEX)
{
	DKscalar value;
	safe_start(VECTOR);
	stream_getIndex(VECTOR->block,DKscalar,INDEX,value);
	safe_endCastReturn(VECTOR,value,DKscalar);
};

DKscalar dkVector_getRear(DKvector *VECTOR)
{
	DKscalar value;
	safe_start(VECTOR);
	stream_getRear(VECTOR->block,DKscalar,value);
	safe_endCastReturn(VECTOR,value,DKscalar);
};

DKscalar dkVector_dequeue(DKvector *VECTOR)
{
	DKscalar value;
	safe_start(VECTOR);
	stream_dequeue(VECTOR->block,DKscalar,value);
	safe_endCastReturn(VECTOR,value,DKscalar);
};

DKscalar dkVector_remove(DKvector *VECTOR,DKssize INDEX)
{
	DKscalar value;
	safe_start(VECTOR);
	stream_remove(VECTOR->block,DKscalar,INDEX,value);
	safe_endCastReturn(VECTOR,value,DKscalar);
};

DKscalar dkVector_pop(DKvector *VECTOR)
{
	DKscalar value;
	safe_start(VECTOR);
	stream_pop(VECTOR->block,DKscalar,value);
	safe_endCastReturn(VECTOR,value,DKscalar);
};
