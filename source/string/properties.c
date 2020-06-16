DKchar dkString_getCharacter(DKstring *STRING,DKssize INDEX)
{
	DKusize index = 0;
	safe_start(STRING);
	helper_calculateSafePosition(INDEX,(STRING->block).size,index);
	error_bypassReturn();
	DKchar code = (STRING->block).source[index];
	safe_endReturn(STRING,code);
}

DKchar *dkString_getSource(DKstring *STRING)
{
	unsafe_start();
	return block_getSource(STRING->block);
}

DKusize dkString_getLength(DKstring *STRING)
{
	unsafe_start();
	return block_getSize(STRING->block);
}

DKboolean dkString_isEmpty(DKstring *STRING)
{
	unsafe_start();
	return block_isEmpty(STRING->block);
}

void dkString_setLock(DKstring *STRING,DKboolean LOCK)
{
	safe_start(STRING);
	mutex_setLock(STRING->mutex,LOCK);
	safe_end(STRING);
}

DKboolean dkString_getLock(DKstring *STRING)
{
	unsafe_start();
	return mutex_getLock(STRING->mutex);
}
