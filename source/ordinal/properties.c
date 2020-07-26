DKusize dkOrdinal_setLength(DKordinal *ORDINAL,DKusize LENGTH)
{
	DKusize length;
	safe_start(ORDINAL);
	block_setLength(ORDINAL->block,DKvalue,LENGTH,length);
	safe_endReturnValue(ORDINAL,length);
};

DKusize dkOrdinal_getLength(DKordinal *ORDINAL)
{
	safe_start(ORDINAL);
	DKusize length = block_getLength(ORDINAL->block);
	safe_endReturnValue(ORDINAL,length);
};

DKboolean dkOrdinal_isEmpty(DKordinal *ORDINAL)
{
	safe_start(ORDINAL);
	DKboolean empty = block_isEmpty(ORDINAL->block);
	safe_endReturnValue(ORDINAL,empty);
};

DKboolean dkOrdinal_isNotEmpty(DKordinal *ORDINAL)
{
	safe_start(ORDINAL);
	DKboolean empty = block_isNotEmpty(ORDINAL->block);
	safe_endReturnValue(ORDINAL,empty);
};

DKboolean dkOrdinal_setLock(DKordinal *ORDINAL,DKboolean LOCK)
{
	safe_start(ORDINAL);
	mutex_setLock(ORDINAL->mutex,LOCK);
	safe_endReturnValue(ORDINAL,!LOCK);
};

DKboolean dkOrdinal_getLock(DKordinal *ORDINAL)
{
	safe_start(ORDINAL);
	DKboolean lock = mutex_getLock(ORDINAL->mutex);
	safe_endReturnValue(ORDINAL,lock);
};
