void dkString_saveToFile(DKstring *STRING,DKssize START,DKssize END,DKnullString FILE_NAME)
{
	safe_start(STRING);
	buffer_saveToFile(STRING->block,START,END,FILE_NAME,"w");
	safe_end(STRING);
};

void dkString_merge(DKstring *STRING,DKssize INDEX,DKstring *SOURCE,DKssize START,DKssize END)
{
	safe_start(STRING);
	mutex_lock(SOURCE->mutex);
	block_merge(STRING->block,DKcharacter,INDEX,SOURCE->block,START,END);
	mutex_unlock(SOURCE->mutex);
	safe_end(STRING);
};

void dkString_clear(DKstring *STRING)
{
	safe_start(STRING);
	block_clear(STRING->block,DKcharacter);
	safe_end(STRING);
};

DKboolean dkString_compare(DKstring *STRING1,DKstring *STRING2)
{
	safe_start(STRING1);
	mutex_lock(STRING2->mutex);
	DKboolean comparison = block_compare(STRING1->block,STRING2->block,DKcharacter);
	mutex_unlock(STRING2->mutex);
	safe_endReturn(STRING1,comparison);
};
