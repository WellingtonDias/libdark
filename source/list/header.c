block_define(DKblock_undefined,DKundefined);

struct _list
{
	DKblock_undefined block;
	DKmutex           mutex;
};

void dkList_debug(DKlist *LIST,DKnullString LABEL)
{
	safe_start(LIST);
	printf("LIST { offset: %lli, size: %lli, capacity: %lli, source: [ ",block_getOffset(LIST->block),block_getSize(LIST->block),block_getCapacity(LIST->block));
	for (DKusize index = 0; index < block_getSize(LIST->block); ++index) printf("%lli ",block_getStart(LIST->block)[index].usize);
	printf("] } #%s\n",LABEL);
	safe_endExit(LIST);
};
