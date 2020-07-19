void dkString_save(DKstring *STRING,DKssize START,DKssize END,DKnstring FILE_NAME)
{
	safe_start(STRING);
	stream_save(STRING->stream,START,END,FILE_NAME,"w");
	safe_end(STRING);
};

void dkString_merge(DKstring *STRING,DKssize INDEX,DKstring *SOURCE,DKssize START,DKssize END)
{
	safe_start(STRING);
	mutex_lock(SOURCE->mutex);
	stream_merge(STRING->stream,DKcharacter,INDEX,SOURCE->stream,START,END)
	mutex_unlock(SOURCE->mutex);
	safe_end(STRING);
};

void dkString_clear(DKstring *STRING)
{
	safe_start(STRING);
	stream_clear(STRING->stream,DKcharacter);
	safe_end(STRING);
};

DKboolean dkString_compare(DKstring *STRING1,DKstring *STRING2)
{
	safe_start(STRING1);
	mutex_lock(STRING2->mutex);
	DKboolean comparison = stream_compare(STRING1->stream,STRING2->stream,DKcharacter);
	mutex_unlock(STRING2->mutex);
	safe_endReturn(STRING1,comparison);
};
