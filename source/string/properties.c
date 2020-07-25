DKcharacter dkString_getCode(DKstring *STRING,DKssize INDEX)
{
	DKusize index;
	safe_start(STRING);
	block_calculateSafePosition(INDEX,(STRING->block).size,index);
	error_bypassReturn();
	DKcharacter code = (STRING->block).start[index];
	safe_endReturn(STRING,code);
};

DKnullString dkString_getCharacter(DKstring *STRING,DKssize INDEX)
{
	DKusize index;
	safe_start(STRING);
	block_calculateSafePosition(INDEX,(STRING->block).size,index);
	error_bypassReturn();
	DKnullString character = (STRING->block).start + index;
	safe_endReturn(STRING,character);
};

DKnullString dkString_getSource(DKstring *STRING)
{
	safe_start(STRING);
	DKnullString source = block_getSource(STRING->block);
	safe_endReturn(STRING,source);
};

DKusize dkString_getLength(DKstring *STRING)
{
	safe_start(STRING);
	DKusize length = block_getSize(STRING->block);
	safe_endReturn(STRING,length);
};

DKboolean dkString_isEmpty(DKstring *STRING)
{
	safe_start(STRING);
	DKboolean empty = block_isEmpty(STRING->block);
	safe_endReturn(STRING,empty);
};

DKboolean dkString_isNotEmpty(DKstring *STRING)
{
	safe_start(STRING);
	DKboolean empty = block_isNotEmpty(STRING->block);
	safe_endReturn(STRING,empty);
};

DKboolean dkString_setLock(DKstring *STRING,DKboolean LOCK)
{
	safe_start(STRING);
	mutex_setLock(STRING->mutex,LOCK);
	safe_endReturn(STRING,!LOCK);
};

DKboolean dkString_getLock(DKstring *STRING)
{
	safe_start(STRING);
	DKboolean lock = mutex_getLock(STRING->mutex);
	safe_endReturn(STRING,lock);
};
