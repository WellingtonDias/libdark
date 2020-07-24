// void dkOrdinal_prepend(DKordinal *ORDINAL,DKhandle SOURCE)
// {
// 	safe_start(ORDINAL);
// 	stream_prepend(ORDINAL->block,DKhandle,SOURCE);
// 	safe_end(ORDINAL);
// };

// void dkOrdinal_insert(DKordinal *ORDINAL,DKssize INDEX,DKhandle SOURCE)
// {
// 	safe_start(ORDINAL);
// 	stream_insert(ORDINAL->block,DKhandle,INDEX,SOURCE);
// 	safe_end(ORDINAL);
// };

// void dkOrdinal_append(DKordinal *ORDINAL,DKhandle SOURCE)
// {
// 	safe_start(ORDINAL);
// 	stream_append(ORDINAL->block,DKhandle,SOURCE);
// 	safe_end(ORDINAL);
// };

// DKhandle dkOrdinal_replace(DKordinal *ORDINAL,DKssize INDEX,DKhandle SOURCE)
// {
// 	DKhandle source;
// 	safe_start(ORDINAL);
// 	stream_replace(ORDINAL->block,DKhandle,INDEX,SOURCE,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandle);
// };

// DKhandle dkOrdinal_set(DKordinal *ORDINAL,DKssize INDEX,DKhandle SOURCE)
// {
// 	DKhandle source;
// 	safe_start(ORDINAL);
// 	stream_set(ORDINAL->block,DKhandle,INDEX,SOURCE,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandle);
// };

// void dkOrdinal_swap(DKordinal *ORDINAL,DKssize INDEX1,DKssize INDEX2)
// {
// 	safe_start(ORDINAL);
// 	stream_swap(ORDINAL->block,DKhandle,INDEX1,INDEX2);
// 	safe_end(ORDINAL);
// };

// DKhandle dkOrdinal_getFront(DKordinal *ORDINAL)
// {
// 	DKhandle source;
// 	safe_start(ORDINAL);
// 	stream_getFront(ORDINAL->block,DKhandle,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandle);
// };

// DKhandle dkOrdinal_getIndex(DKordinal *ORDINAL,DKssize INDEX)
// {
// 	DKhandle source;
// 	safe_start(ORDINAL);
// 	stream_getIndex(ORDINAL->block,DKhandle,INDEX,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandle);
// };

// DKhandle dkOrdinal_getRear(DKordinal *ORDINAL)
// {
// 	DKhandle source;
// 	safe_start(ORDINAL);
// 	stream_getRear(ORDINAL->block,DKhandle,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandle);
// };

// DKhandle dkOrdinal_dequeue(DKordinal *ORDINAL)
// {
// 	DKhandle source;
// 	safe_start(ORDINAL);
// 	stream_dequeue(ORDINAL->block,DKhandle,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandle);
// };

// DKhandle dkOrdinal_remove(DKordinal *ORDINAL,DKssize INDEX)
// {
// 	DKhandle source;
// 	safe_start(ORDINAL);
// 	stream_remove(ORDINAL->block,DKhandle,INDEX,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandle);
// };

// DKhandle dkOrdinal_pop(DKordinal *ORDINAL)
// {
// 	DKhandle source;
// 	safe_start(ORDINAL);
// 	stream_pop(ORDINAL->block,DKhandle,SOURCE);
// 	safe_endCastReturn(ORDINAL,SOURCE,DKhandle);
// };
