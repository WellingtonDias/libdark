DKusize DKnominal_getLength(DKnominal *NOMINAL)
{
	safe_start(NOMINAL);
	DKusize length = NOMINAL->length;
	safe_endReturnValue(NOMINAL,length);
};

DKboolean DKnominal_isEmpty(DKnominal *NOMINAL)
{
	safe_start(NOMINAL);
	DKboolean empty = (NOMINAL->length == 0);
	safe_endReturnValue(NOMINAL,empty);
};

DKboolean DKnominal_isNotEmpty(DKnominal *NOMINAL)
{
	safe_start(NOMINAL);
	DKboolean empty = (NOMINAL->length != 0);
	safe_endReturnValue(NOMINAL,empty);
};

DKboolean DKnominal_setLock(DKnominal *NOMINAL,DKboolean LOCK)
{
	safe_start(NOMINAL);
	mutex_setLock(NOMINAL->mutex,LOCK);
	safe_endReturnValue(NOMINAL,!LOCK);
};

DKboolean DKnominal_getLock(DKnominal *NOMINAL)
{
	safe_start(NOMINAL);
	DKboolean lock = mutex_getLock(NOMINAL->mutex);
	safe_endReturnValue(NOMINAL,lock);
};
