#routine safe_throwExit(STRUCT,MESSAGE)
{
	exception_set(MESSAGE);
	exception_try();
	mutex_unlock(STRUCT->mutex);
	return;
};

#routine safe_throwReturn(STRUCT,MESSAGE)
{
	exception_set(MESSAGE);
	exception_try();
	mutex_unlock(STRUCT->mutex);
	return 0;
};

#routine safe_throwReturnCast(STRUCT,MESSAGE,#TYPE)
{
	exception_set(MESSAGE);
	exception_try();
	mutex_unlock(STRUCT->mutex);
	return (TYPE) 0;
};

#routine safe_throwReturnValue(STRUCT,MESSAGE,VALUE)
{
	exception_set(MESSAGE);
	exception_try();
	mutex_unlock(STRUCT->mutex);
	return VALUE;
};

#routine safe_bypassExit(STRUCT)
{
	if (exception_get())
	{
		exception_try();
		mutex_unlock(STRUCT->mutex);
		return;
	};
};

#routine safe_bypassReturn(STRUCT)
{
	if (exception_get())
	{
		exception_try();
		mutex_unlock(STRUCT->mutex);
		return 0;
	};
};

#routine safe_bypassReturnCast(STRUCT,#TYPE)
{
	if (exception_get())
	{
		exception_try();
		mutex_unlock(STRUCT->mutex);
		return (TYPE) 0;
	};
};

#routine safe_bypassReturnValue(STRUCT,VALUE)
{
	if (exception_get())
	{
		exception_try();
		mutex_unlock(STRUCT->mutex);
		return VALUE;
	};
};
