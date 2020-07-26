void dkOrdinal_merge(DKordinal *ORDINAL,DKssize INDEX,DKordinal *SOURCE,DKssize START,DKssize END)
{
	safe_start(ORDINAL);
	mutex_lock(SOURCE->mutex);
	block_merge(ORDINAL->block,DKhandleUnion,INDEX,SOURCE->block,START,END);
	mutex_unlock(SOURCE->mutex);
	safe_end(ORDINAL);
};

void dkOrdinal_clear(DKordinal *ORDINAL)
{
	safe_start(ORDINAL);
	block_clear(ORDINAL->block,DKhandleUnion);
	safe_end(ORDINAL);
};

DKboolean dkOrdinal_compare(DKordinal *ORDINAL1,DKordinal *ORDINAL2)
{
	safe_start(ORDINAL1);
	mutex_lock(ORDINAL2->mutex);
	DKboolean comparison = block_compare(ORDINAL1->block,ORDINAL2->block,DKhandleUnion);
	mutex_unlock(ORDINAL2->mutex);
	safe_endReturn(ORDINAL1,comparison);
};
