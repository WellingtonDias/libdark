block_define(DKblock_handle,DKhandleUnion);

struct _ordinal
{
	DKblock_handle block;
	DKmutex mutex;
};

void dkOrdinal_debug(DKordinal *ORDINAL,DKnullString LABEL)
{
	safe_start(ORDINAL);
	printf("ORDINAL { size: %lli,capacity: %lli,source: [",(ORDINAL->block).size,(ORDINAL->block).capacity);
	for (DKusize i = 0; i < (ORDINAL->block).size; ++i) printf("%lli ",(ORDINAL->block).start[i].usize);
	printf("] } #%s\n",LABEL);
	safe_end(ORDINAL);
};
