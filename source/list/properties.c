DKundefined *dkList_getSource(DKlist *LIST)
{
	safe_start(LIST);
	DKundefined *source = block_getSource(LIST->block);
	safe_endReturn(LIST,source);
};

DKusize dkList_getOffset(DKlist *LIST)
{
	safe_start(LIST);
	DKusize offset = block_getOffset(LIST->block);
	safe_endReturn(LIST,offset);
};

DKusize dkList_setSize(DKlist *LIST,DKusize SIZE)
{
	DKusize size;
	safe_start(LIST);
	block_setSize(DKundefined,LIST->block,SIZE,size);
	safe_endReturn(LIST,size);
};

DKusize dkList_getSize(DKlist *LIST)
{
	safe_start(LIST);
	DKusize size = block_getSize(LIST->block);
	safe_endReturn(LIST,size);
};

DKboolean dkList_isEmpty(DKlist *LIST)
{
	safe_start(LIST);
	DKboolean empty = block_isEmpty(LIST->block);
	safe_endReturn(LIST,empty);
};

DKboolean dkList_isNotEmpty(DKlist *LIST)
{
	safe_start(LIST);
	DKboolean empty = block_isNotEmpty(LIST->block);
	safe_endReturn(LIST,empty);
};

DKusize dkList_getCapacity(DKlist *LIST)
{
	safe_start(LIST);
	DKusize capacity = block_getCapacity(LIST->block);
	safe_endReturn(LIST,capacity);
};

DKboolean dkList_setLock(DKlist *LIST,DKboolean LOCK)
{
	safe_start(LIST);
	mutex_setLock(LIST->mutex,LOCK);
	safe_endReturn(LIST,!LOCK);
};

DKboolean dkList_getLock(DKlist *LIST)
{
	safe_start(LIST);
	DKboolean lock = mutex_getLock(LIST->mutex);
	safe_endReturn(LIST,lock);
};
