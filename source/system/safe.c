#routine safe_start(STRUCT)
{
	error_throwUnhandled();
	mutex_lock(STRUCT->mutex);
};

#routine safe_endExit(STRUCT)
{
	mutex_unlock(STRUCT->mutex);
	return;
};

#routine safe_endReturn(STRUCT,VALUE)
{
	mutex_unlock(STRUCT->mutex);
	return VALUE;
};

#routine safe_bypassExit(STRUCT)
{
	if (error_get())
	{
		mutex_unlock(STRUCT->mutex);
		return;
	};
};

#routine safe_bypassReturn(STRUCT)
{
	if (error_get())
	{
		mutex_unlock(STRUCT->mutex);
		return 0;
	};
};

#routine safe_bypassReturnCast(STRUCT,#TYPE)
{
	if (error_get())
	{
		mutex_unlock(STRUCT->mutex);
		return (TYPE) 0;
	};
};

#routine safe_bypassReturnValue(STRUCT,VALUE)
{
	if (error_get())
	{
		mutex_unlock(STRUCT->mutex);
		return VALUE;
	};
};

#routine safe_throwExit(STRUCT,MESSAGE)
{
	error_set(MESSAGE);
	error_throw();
	mutex_unlock(STRUCT->mutex);
	return;
};

#routine safe_throwReturn(STRUCT,MESSAGE)
{
	error_set(MESSAGE);
	error_throw();
	mutex_unlock(STRUCT->mutex);
	return 0;
};

#routine safe_throwReturnCast(STRUCT,MESSAGE,#TYPE)
{
	error_set(MESSAGE);
	error_throw();
	mutex_unlock(STRUCT->mutex);
	return (TYPE) 0;
};

#routine safe_throwReturnValue(STRUCT,MESSAGE,VALUE)
{
	error_set(MESSAGE);
	error_throw();
	mutex_unlock(STRUCT->mutex);
	return VALUE;
};
