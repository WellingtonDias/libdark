thread_local UnsignedSize ExceptionBlock;
thread_local Exception ExceptionGlobal;

#routine exception_panic(MESSAGE)
{
	printf("EXCEPTION: %s.\n",MESSAGE);
	exit(EXIT_FAILURE);
};

#routine exception_throw(EXCEPTION,MESSAGE)
{
	if (ExceptionBlock == 0) exception_panic(MESSAGE);
	EXCEPTION.message = MESSAGE;
};

#routine exception_routineThrow(EXCEPTION,MESSAGE)
{
	exception_throw(EXCEPTION,MESSAGE);
	break;
};

#routine exception_routineBypass(EXCEPTION)
{
	if (EXCEPTION.message != NULL) break;
};

#routine exception_globalThrowExit(MESSAGE)
{
	exception_throw(ExceptionGlobal,MESSAGE);
	return;
};

#routine exception_globalThrowReturn(MESSAGE)
{
	exception_throw(ExceptionGlobal,MESSAGE);
	return 0;
};

#routine exception_globalThrowReturnCast(MESSAGE,#TYPE)
{
	exception_throw(ExceptionGlobal,MESSAGE);
	return (TYPE) 0;
};

#routine exception_globalThrowReturnValue(MESSAGE,VALUE)
{
	exception_throw(ExceptionGlobal,MESSAGE);
	return VALUE;
};

#routine exception_globalBypassExit()
{
	if (ExceptionGlobal.message != NULL) return;
};

#routine exception_globalBypassReturn()
{
	if (ExceptionGlobal.message != NULL) return 0;
};

#routine exception_globalBypassReturnCast(#TYPE)
{
	if (ExceptionGlobal.message != NULL) return (TYPE) 0;
};

#routine exception_globalBypassReturnValue(VALUE)
{
	if (ExceptionGlobal.message != NULL) return VALUE;
};

#routine exception_destroy(STRUCT)
{
	STRUCT->exception.message = NULL;
};

#routine exception_structThrowExit(STRUCT,MESSAGE)
{
	exception_throw(STRUCT->exception,MESSAGE);
	mutex_unlock(STRUCT);
	return;
};

#routine exception_structThrowReturn(STRUCT,MESSAGE)
{
	exception_throw(STRUCT->exception,MESSAGE);
	mutex_unlock(STRUCT);
	return 0;
};

#routine exception_structThrowReturnCast(STRUCT,MESSAGE,#TYPE)
{
	exception_throw(STRUCT->exception,MESSAGE);
	mutex_unlock(STRUCT);
	return (TYPE) 0;
};

#routine exception_structThrowReturnValue(STRUCT,MESSAGE,VALUE)
{
	exception_throw(STRUCT->exception,MESSAGE);
	mutex_unlock(STRUCT);
	return VALUE;
};

#routine exception_structBypassExit(STRUCT)
{
	if (STRUCT->exception.message != NULL)
	{
		mutex_unlock(STRUCT);
		return;
	};
};

#routine exception_structBypassReturn(STRUCT)
{
	if (STRUCT->exception.message != NULL)
	{
		mutex_unlock(STRUCT);
		return 0;
	};
};

#routine exception_structBypassReturnCast(STRUCT,#TYPE)
{
	if (STRUCT->exception.message != NULL)
	{
		mutex_unlock(STRUCT);
		return (TYPE) 0;
	};
};

#routine exception_structBypassReturnValue(STRUCT,VALUE)
{
	if (STRUCT->exception.message != NULL)
	{
		mutex_unlock(STRUCT);
		return VALUE;
	};
};

#routine exception_getMessage(STRUCT,RETURN)
{
	if ((RETURN = STRUCT->exception.message) != NULL) STRUCT->exception.message = NULL;
};

void Exception_start(void)
{
	ExceptionBlock += 1;
};

void Exception_end(void)
{
	if (ExceptionBlock == 0) exception_panic("There is no exception block to end");
	ExceptionBlock -= 1;
};

void Exception_throw(NullString MESSAGE)
{
	exception_panic(MESSAGE);
};

NullString Exception_catch(void)
{
	NullString message;
	if ((message = ExceptionGlobal.message) != NULL) ExceptionGlobal.message = NULL;
	return message;
};

void Exception_debug(NullString MESSAGE)
{
	printf("EXCEPTION: %s.\n",MESSAGE);
};
