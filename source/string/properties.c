DKnullString dkString_getSource(DKstring *STRING)
{
	safe_start(STRING);
	DKnullString source = block_getSource(STRING->block);
	safe_endReturnValue(STRING,source);
};

DKusize dkString_setLength(DKstring *STRING,DKusize LENGTH)
{
	DKusize length;
	safe_start(STRING);
	block_setLength(STRING->block,DKcharacter,LENGTH,length);
	safe_endReturnValue(STRING,length);
};

DKusize dkString_getLength(DKstring *STRING)
{
	safe_start(STRING);
	DKusize length = block_getLength(STRING->block);
	safe_endReturnValue(STRING,length);
};

DKboolean dkString_isEmpty(DKstring *STRING)
{
	safe_start(STRING);
	DKboolean empty = block_isEmpty(STRING->block);
	safe_endReturnValue(STRING,empty);
};

DKboolean dkString_isNotEmpty(DKstring *STRING)
{
	safe_start(STRING);
	DKboolean empty = block_isNotEmpty(STRING->block);
	safe_endReturnValue(STRING,empty);
};

DKboolean dkString_setLock(DKstring *STRING,DKboolean LOCK)
{
	safe_start(STRING);
	mutex_setLock(STRING->mutex,LOCK);
	safe_endReturnValue(STRING,!LOCK);
};

DKboolean dkString_getLock(DKstring *STRING)
{
	safe_start(STRING);
	DKboolean lock = mutex_getLock(STRING->mutex);
	safe_endReturnValue(STRING,lock);
};
