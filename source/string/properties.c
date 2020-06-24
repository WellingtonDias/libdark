DKcharacter dkString_getCharacter(DKstring *STRING,DKssize INDEX)
{
	DKusize index = 0;
	safe_start(STRING);
	block_calculateSafePosition(INDEX,(STRING->block).size,index);
	error_bypassReturn();
	DKcharacter character = (STRING->block).source[index];
	safe_endReturn(STRING,character);
};

DKnstring dkString_getSource(DKstring *STRING)
{
	safe_start(STRING);
	DKnstring source = block_getSource(STRING->block);
	safe_endReturn(STRING,source);
};

DKusize dkString_getLength(DKstring *STRING)
{
	safe_start(STRING);
	DKusize size = block_getSize(STRING->block);
	safe_endReturn(STRING,size);
};

DKboolean dkString_isEmpty(DKstring *STRING)
{
	safe_start(STRING);
	DKboolean empty = block_isEmpty(STRING->block);
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
