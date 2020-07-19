DKcharacter dkString_getCharacter(DKstring *STRING,DKssize INDEX)
{
	DKusize index = 0;
	safe_start(STRING);
	stream_calculateSafePosition(INDEX,(STRING->stream).size,index);
	error_bypassReturn();
	DKcharacter character = (STRING->stream).source[index];
	safe_endReturn(STRING,character);
};

DKnstring dkString_getSource(DKstring *STRING)
{
	safe_start(STRING);
	DKnstring source = stream_getSource(STRING->stream);
	safe_endReturn(STRING,source);
};

DKusize dkString_getLength(DKstring *STRING)
{
	safe_start(STRING);
	DKusize size = stream_getSize(STRING->stream);
	safe_endReturn(STRING,size);
};

DKboolean dkString_isEmpty(DKstring *STRING)
{
	safe_start(STRING);
	DKboolean empty = stream_isEmpty(STRING->stream);
	safe_endReturn(STRING,empty);
};

void dkString_setLock(DKstring *STRING,DKboolean LOCK)
{
	safe_start(STRING);
	mutex_setLock(STRING->mutex,LOCK);
	safe_end(STRING);
};

DKboolean dkString_getLock(DKstring *STRING)
{
	safe_start(STRING);
	DKboolean lock = mutex_getLock(STRING->mutex);
	safe_endReturn(STRING,lock);
};
