block_define(DKblock_value,DKvalue);

struct _ordinal
{
	DKblock_value block;
	DKmutex mutex;
};

void dkOrdinal_debug(DKordinal *ORDINAL,DKnullString LABEL)
{
	safe_start(ORDINAL);
	printf("ORDINAL { length: %lli, source: [ ",block_getLength(ORDINAL->block));
	for (DKusize i = 0; i < block_getLength(ORDINAL->block); ++i) printf("%lli ",block_getSource(ORDINAL->block)[i].usize);
	printf("] } #%s\n",LABEL);
	safe_endExit(ORDINAL);
};
