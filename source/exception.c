thread_local NullString ExceptionMessage;
thread_local UnsignedSize ExceptionBlock;

#routine exception_try()
{
	if (!ExceptionBlock) exception_throw(ExceptionMessage);
};

#routine exception_throwBreak(MESSAGE)
{
	ExceptionMessage = MESSAGE;
	break;
};

#routine exception_throwExit(MESSAGE)
{
	ExceptionMessage = MESSAGE;
	exception_try();
	return;
};

#routine exception_throwReturn(MESSAGE)
{
	ExceptionMessage = MESSAGE;
	exception_try();
	return 0;
};

#routine exception_throwReturnCast(MESSAGE,#TYPE)
{
	ExceptionMessage = MESSAGE;
	exception_try();
	return (TYPE) 0;
};

#routine exception_throwReturnValue(MESSAGE,VALUE)
{
	ExceptionMessage = MESSAGE;
	exception_try();
	return VALUE;
};

#routine exception_safeThrowExit(STRUCT,MESSAGE)
{
	ExceptionMessage = MESSAGE;
	exception_try();
	mutex_unlock(STRUCT->mutex);
	return;
};

#routine exception_safeThrowReturn(STRUCT,MESSAGE)
{
	ExceptionMessage = MESSAGE;
	exception_try();
	mutex_unlock(STRUCT->mutex);
	return 0;
};

#routine exception_safeThrowReturnCast(STRUCT,MESSAGE,#TYPE)
{
	ExceptionMessage = MESSAGE;
	exception_try();
	mutex_unlock(STRUCT->mutex);
	return (TYPE) 0;
};

#routine exception_safeThrowReturnValue(STRUCT,MESSAGE,VALUE)
{
	ExceptionMessage = MESSAGE;
	exception_try();
	mutex_unlock(STRUCT->mutex);
	return VALUE;
};

#routine exception_bypassBreak()
{
	if (ExceptionMessage) break;
};

#routine exception_bypassExit()
{
	if (ExceptionMessage)
	{
		exception_try();
		return;
	};
};

#routine exception_bypassReturn()
{
	if (ExceptionMessage)
	{
		exception_try();
		return 0;
	};
};

#routine exception_bypassReturnCast(#TYPE)
{
	if (ExceptionMessage)
	{
		exception_try();
		return (TYPE) 0;
	};
};

#routine exception_bypassReturnValue(VALUE)
{
	if (ExceptionMessage)
	{
		exception_try();
		return VALUE;
	};
};

#routine exception_safeBypassExit(STRUCT)
{
	if (ExceptionMessage)
	{
		exception_try();
		mutex_unlock(STRUCT->mutex);
		return;
	};
};

#routine exception_safeBypassReturn(STRUCT)
{
	if (ExceptionMessage)
	{
		exception_try();
		mutex_unlock(STRUCT->mutex);
		return 0;
	};
};

#routine exception_safeBypassReturnCast(STRUCT,#TYPE)
{
	if (ExceptionMessage)
	{
		exception_try();
		mutex_unlock(STRUCT->mutex);
		return (TYPE) 0;
	};
};

#routine exception_safeBypassReturnValue(STRUCT,VALUE)
{
	if (ExceptionMessage)
	{
		exception_try();
		mutex_unlock(STRUCT->mutex);
		return VALUE;
	};
};

void exception_start(void)
{
	ExceptionBlock += 1;
};

void exception_end(void)
{
	if (!ExceptionBlock) exception_throw("There is no exception block to end");
	ExceptionBlock -= 1;
};

NullString exception_catch(void)
{
	NullString exception;
	if (!(exception = ExceptionMessage)) return NULL;
	ExceptionMessage = NULL;
	return exception;
};

void exception_throw(NullString MESSAGE)
{
	printf("EXCEPTION: %s.\n",MESSAGE);
	exit(EXIT_FAILURE);
};

void exception_debug(NullString MESSAGE)
{
	printf("EXCEPTION: %s.\n",MESSAGE);
};
