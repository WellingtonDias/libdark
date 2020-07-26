void dkOrdinal_prepend(DKordinal *ORDINAL,DKvalue VALUE)
{
	safe_start(ORDINAL);
	stream_prepend(ORDINAL->block,DKvalue,VALUE);
	safe_endExit(ORDINAL);
};

void dkOrdinal_insert(DKordinal *ORDINAL,DKssize INDEX,DKvalue VALUE)
{
	safe_start(ORDINAL);
	stream_insert(ORDINAL->block,DKvalue,INDEX,VALUE);
	safe_endExit(ORDINAL);
};

void dkOrdinal_append(DKordinal *ORDINAL,DKvalue VALUE)
{
	safe_start(ORDINAL);
	stream_append(ORDINAL->block,DKvalue,VALUE);
	safe_endExit(ORDINAL);
};

DKvalue dkOrdinal_replace(DKordinal *ORDINAL,DKssize INDEX,DKvalue VALUE)
{
	DKvalue value;
	safe_start(ORDINAL);
	stream_replace(ORDINAL->block,DKvalue,INDEX,VALUE,value);
	safe_endReturnValue(ORDINAL,value);
};

DKvalue dkOrdinal_set(DKordinal *ORDINAL,DKssize INDEX,DKvalue VALUE)
{
	DKvalue value;
	safe_start(ORDINAL);
	stream_set(ORDINAL->block,DKvalue,INDEX,VALUE,value);
	safe_endReturnValue(ORDINAL,value);
};

void dkOrdinal_swap(DKordinal *ORDINAL,DKssize INDEX1,DKssize INDEX2)
{
	safe_start(ORDINAL);
	stream_swap(ORDINAL->block,DKvalue,INDEX1,INDEX2);
	safe_endExit(ORDINAL);
};

DKvalue dkOrdinal_getFront(DKordinal *ORDINAL)
{
	DKvalue value;
	safe_start(ORDINAL);
	stream_getFront(ORDINAL->block,DKvalue,value);
	safe_endReturnValue(ORDINAL,value);
};

DKvalue dkOrdinal_getIndex(DKordinal *ORDINAL,DKssize INDEX)
{
	DKvalue value;
	safe_start(ORDINAL);
	stream_getIndex(ORDINAL->block,DKvalue,INDEX,value);
	safe_endReturnValue(ORDINAL,value);
};

DKvalue dkOrdinal_getRear(DKordinal *ORDINAL)
{
	DKvalue value;
	safe_start(ORDINAL);
	stream_getRear(ORDINAL->block,DKvalue,value);
	safe_endReturnValue(ORDINAL,value);
};

DKvalue dkOrdinal_dequeue(DKordinal *ORDINAL)
{
	DKvalue value;
	safe_start(ORDINAL);
	stream_dequeue(ORDINAL->block,DKvalue,value);
	safe_endReturnValue(ORDINAL,value);
};

DKvalue dkOrdinal_remove(DKordinal *ORDINAL,DKssize INDEX)
{
	DKvalue value;
	safe_start(ORDINAL);
	stream_remove(ORDINAL->block,DKvalue,INDEX,value);
	safe_endReturnValue(ORDINAL,value);
};

DKvalue dkOrdinal_pop(DKordinal *ORDINAL)
{
	DKvalue value;
	safe_start(ORDINAL);
	stream_pop(ORDINAL->block,DKvalue,value);
	safe_endReturnValue(ORDINAL,value);
};
