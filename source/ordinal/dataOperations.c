// void dkOrdinal_prepend(DKordinal *ORDINAL,DKhandleUnion SOURCE)
// {
// 	safe_start(ORDINAL);
// 	stream_prepend(ORDINAL->block,DKhandleUnion,SOURCE);
// 	safe_end(ORDINAL);
// };

// void dkOrdinal_insert(DKordinal *ORDINAL,DKssize INDEX,DKhandleUnion SOURCE)
// {
// 	safe_start(ORDINAL);
// 	stream_insert(ORDINAL->block,DKhandleUnion,INDEX,SOURCE);
// 	safe_end(ORDINAL);
// };

// void dkOrdinal_append(DKordinal *ORDINAL,DKhandleUnion SOURCE)
// {
// 	safe_start(ORDINAL);
// 	stream_append(ORDINAL->block,DKhandleUnion,SOURCE);
// 	safe_end(ORDINAL);
// };

// DKhandleUnion dkOrdinal_replace(DKordinal *ORDINAL,DKssize INDEX,DKhandleUnion SOURCE)
// {
// 	DKhandleUnion source;
// 	safe_start(ORDINAL);
// 	stream_replace(ORDINAL->block,DKhandleUnion,INDEX,SOURCE,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandleUnion);
// };

// DKhandleUnion dkOrdinal_set(DKordinal *ORDINAL,DKssize INDEX,DKhandleUnion SOURCE)
// {
// 	DKhandleUnion source;
// 	safe_start(ORDINAL);
// 	stream_set(ORDINAL->block,DKhandleUnion,INDEX,SOURCE,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandleUnion);
// };

// void dkOrdinal_swap(DKordinal *ORDINAL,DKssize INDEX1,DKssize INDEX2)
// {
// 	safe_start(ORDINAL);
// 	stream_swap(ORDINAL->block,DKhandleUnion,INDEX1,INDEX2);
// 	safe_end(ORDINAL);
// };

// DKhandleUnion dkOrdinal_getFront(DKordinal *ORDINAL)
// {
// 	DKhandleUnion source;
// 	safe_start(ORDINAL);
// 	stream_getFront(ORDINAL->block,DKhandleUnion,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandleUnion);
// };

// DKhandleUnion dkOrdinal_getIndex(DKordinal *ORDINAL,DKssize INDEX)
// {
// 	DKhandleUnion source;
// 	safe_start(ORDINAL);
// 	stream_getIndex(ORDINAL->block,DKhandleUnion,INDEX,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandleUnion);
// };

// DKhandleUnion dkOrdinal_getRear(DKordinal *ORDINAL)
// {
// 	DKhandleUnion source;
// 	safe_start(ORDINAL);
// 	stream_getRear(ORDINAL->block,DKhandleUnion,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandleUnion);
// };

// DKhandleUnion dkOrdinal_dequeue(DKordinal *ORDINAL)
// {
// 	DKhandleUnion source;
// 	safe_start(ORDINAL);
// 	stream_dequeue(ORDINAL->block,DKhandleUnion,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandleUnion);
// };

// DKhandleUnion dkOrdinal_remove(DKordinal *ORDINAL,DKssize INDEX)
// {
// 	DKhandleUnion source;
// 	safe_start(ORDINAL);
// 	stream_remove(ORDINAL->block,DKhandleUnion,INDEX,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandleUnion);
// };

// DKhandleUnion dkOrdinal_pop(DKordinal *ORDINAL)
// {
// 	DKhandleUnion source;
// 	safe_start(ORDINAL);
// 	stream_pop(ORDINAL->block,DKhandleUnion,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandleUnion);
// };
