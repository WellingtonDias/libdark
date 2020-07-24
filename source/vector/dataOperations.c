// void dkVector_prepend(DKvector *VECTOR,DKscalar SOURCE)
// {
// 	safe_start(VECTOR);
// 	stream_prepend(VECTOR->block,DKscalar,SOURCE);
// 	safe_end(VECTOR);
// };

// void dkVector_insert(DKvector *VECTOR,DKssize INDEX,DKscalar SOURCE)
// {
// 	safe_start(VECTOR);
// 	stream_insert(VECTOR->block,DKscalar,INDEX,SOURCE);
// 	safe_end(VECTOR);
// };

// void dkVector_append(DKvector *VECTOR,DKscalar SOURCE)
// {
// 	safe_start(VECTOR);
// 	stream_append(VECTOR->block,DKscalar,SOURCE);
// 	safe_end(VECTOR);
// };

// DKscalar dkVector_replace(DKvector *VECTOR,DKssize INDEX,DKscalar SOURCE)
// {
// 	DKscalar source;
// 	safe_start(VECTOR);
// 	stream_replace(VECTOR->block,DKscalar,INDEX,SOURCE,SOURCE);
// 	safe_endCastReturn(VECTOR,SOURCE,DKscalar);
// };

// DKscalar dkVector_set(DKvector *VECTOR,DKssize INDEX,DKscalar SOURCE)
// {
// 	DKscalar source;
// 	safe_start(VECTOR);
// 	stream_set(VECTOR->block,DKscalar,INDEX,SOURCE,SOURCE);
// 	safe_endCastReturn(VECTOR,SOURCE,DKscalar);
// };

// void dkVector_swap(DKvector *VECTOR,DKssize INDEX1,DKssize INDEX2)
// {
// 	safe_start(VECTOR);
// 	stream_swap(VECTOR->block,DKscalar,INDEX1,INDEX2);
// 	safe_end(VECTOR);
// };

// DKscalar dkVector_getFront(DKvector *VECTOR)
// {
// 	DKscalar source;
// 	safe_start(VECTOR);
// 	stream_getFront(VECTOR->block,DKscalar,SOURCE);
// 	safe_endCastReturn(VECTOR,SOURCE,DKscalar);
// };

// DKscalar dkVector_getIndex(DKvector *VECTOR,DKssize INDEX)
// {
// 	DKscalar source;
// 	safe_start(VECTOR);
// 	stream_getIndex(VECTOR->block,DKscalar,INDEX,SOURCE);
// 	safe_endCastReturn(VECTOR,SOURCE,DKscalar);
// };

// DKscalar dkVector_getRear(DKvector *VECTOR)
// {
// 	DKscalar source;
// 	safe_start(VECTOR);
// 	stream_getRear(VECTOR->block,DKscalar,SOURCE);
// 	safe_endCastReturn(VECTOR,SOURCE,DKscalar);
// };

// DKscalar dkVector_dequeue(DKvector *VECTOR)
// {
// 	DKscalar source;
// 	safe_start(VECTOR);
// 	stream_dequeue(VECTOR->block,DKscalar,SOURCE);
// 	safe_endCastReturn(VECTOR,SOURCE,DKscalar);
// };

// DKscalar dkVector_remove(DKvector *VECTOR,DKssize INDEX)
// {
// 	DKscalar source;
// 	safe_start(VECTOR);
// 	stream_remove(VECTOR->block,DKscalar,INDEX,SOURCE);
// 	safe_endCastReturn(VECTOR,SOURCE,DKscalar);
// };

// DKscalar dkVector_pop(DKvector *VECTOR)
// {
// 	DKscalar source;
// 	safe_start(VECTOR);
// 	stream_pop(VECTOR->block,DKscalar,SOURCE);
// 	safe_endCastReturn(VECTOR,SOURCE,DKscalar);
// };
