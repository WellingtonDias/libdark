void dkList_merge(DKlist *TARGET_LIST,DKssize TARGET_INDEX,DKlist *SOURCE_LIST,DKssize SOURCE_START,DKssize SOURCE_END)
{
	safe_start(TARGET_LIST);
	mutex_lock(SOURCE_LIST->mutex);
	block_merge(DKundefined,TARGET_LIST->block,TARGET_INDEX,SOURCE_LIST->block,SOURCE_START,SOURCE_END);
	mutex_unlock(SOURCE_LIST->mutex);
	safe_endExit(TARGET_LIST);
};

void dkList_trim(DKlist *LIST)
{
	safe_start(LIST);
	block_trim(DKundefined,LIST->block);
	safe_endExit(LIST);
};

void dkList_clear(DKlist *LIST)
{
	safe_start(LIST);
	block_clear(DKundefined,LIST->block);
	safe_endExit(LIST);
};

DKboolean dkList_compare(DKlist *LIST1,DKlist *LIST2)
{
	safe_start(LIST1);
	mutex_lock(LIST2->mutex);
	DKboolean comparison = block_compare(DKundefined,LIST1->block,LIST2->block);
	mutex_unlock(LIST2->mutex);
	safe_endReturn(LIST1,comparison);
};
