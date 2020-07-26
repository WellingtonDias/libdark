#macro safe_start(STRUCT)
{
	error_throwUnhandled();
	mutex_lock(STRUCT->mutex);
};

#macro safe_endExit(STRUCT)
{
	mutex_unlock(STRUCT->mutex);
	return;
};

#macro safe_endReturnValue(STRUCT,RETURN)
{
	mutex_unlock(STRUCT->mutex);
	return RETURN;
};

#macro safe_endReturnCast(STRUCT,RETURN,#TYPE)
{
	mutex_unlock(STRUCT->mutex);
	return (TYPE) RETURN;
};

#macro safe_bypassExit(STRUCT)
{
	if (ErrorMessage)
	{
		mutex_unlock(STRUCT->mutex);
		return;
	};
};

#macro safe_bypassReturn(STRUCT)
{
	if (ErrorMessage)
	{
		mutex_unlock(STRUCT->mutex);
		return 0;
	};
};

#macro safe_bypassReturnValue(STRUCT,RETURN)
{
	if (ErrorMessage)
	{
		mutex_unlock(STRUCT->mutex);
		return RETURN;
	};
};

#macro safe_bypassReturnCast(STRUCT,RETURN,#TYPE)
{
	if (ErrorMessage)
	{
		mutex_unlock(STRUCT->mutex);
		return (TYPE) RETURN;
	};
};
