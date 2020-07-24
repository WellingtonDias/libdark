DKusize dkOrdinal_setSize(DKordinal *ORDINAL,DKusize SIZE)
{
	DKusize size;
	safe_start(ORDINAL);
	block_setSize(ORDINAL->block,DKhandle,SIZE,size);
	safe_endReturn(ORDINAL,size);
};

DKusize dkOrdinal_getSize(DKordinal *ORDINAL)
{
	safe_start(ORDINAL);
	DKusize size = block_getSize(ORDINAL->block);
	safe_endReturn(ORDINAL,size);
};

DKboolean dkOrdinal_isEmpty(DKordinal *ORDINAL)
{
	safe_start(ORDINAL);
	DKboolean empty = block_isEmpty(ORDINAL->block);
	safe_endReturn(ORDINAL,empty);
};

void dkOrdinal_setLock(DKordinal *ORDINAL,DKboolean LOCK)
{
	safe_start(ORDINAL);
	mutex_setLock(ORDINAL->mutex,LOCK);
	safe_end(ORDINAL);
};

DKboolean dkOrdinal_getLock(DKordinal *ORDINAL)
{
	safe_start(ORDINAL);
	DKboolean lock = mutex_getLock(ORDINAL->mutex);
	safe_endReturn(ORDINAL,lock);
};
