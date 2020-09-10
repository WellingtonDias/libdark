typedef struct
{
	NullString message;
} Exception;

thread_local UnsignedSize ExceptionBlock;
thread_local Exception ExceptionGlobal;


#routine exception_destroy(EXCEPTION)
{
	EXCEPTION.message = NULL;
};

#routine exception_panic(MESSAGE)
{
	printf("EXCEPTION: %s.\n",MESSAGE);
	exit(EXIT_FAILURE);
};

#routine exception_globalThrowBreak(MESSAGE)
{
	if (!ExceptionBlock) exception_panic(MESSAGE);
	ExceptionGlobal.message = MESSAGE;
	break;
};

#routine exception_globalThrowExit(MESSAGE)
{
	if (!ExceptionBlock) exception_panic(MESSAGE);
	ExceptionGlobal.message = MESSAGE;
	return;
};

#routine exception_globalThrowReturn(MESSAGE)
{
	if (!ExceptionBlock) exception_panic(MESSAGE);
	ExceptionGlobal.message = MESSAGE;
	return 0;
};

#routine exception_globalThrowReturnCast(MESSAGE,#TYPE)
{
	if (!ExceptionBlock) exception_panic(MESSAGE);
	ExceptionGlobal.message = MESSAGE;
	return (TYPE) 0;
};

#routine exception_globalThrowReturnValue(MESSAGE,VALUE)
{
	if (!ExceptionBlock) exception_panic(MESSAGE);
	ExceptionGlobal.message = MESSAGE;
	return VALUE;
};

#routine exception_globalBypassBreak()
{
	if (ExceptionGlobal.message) break;
};

#routine exception_globalBypassExit()
{
	if (ExceptionGlobal.message) return;
};

#routine exception_globalBypassReturn()
{
	if (ExceptionGlobal.message) return 0;
};

#routine exception_globalBypassReturnCast(#TYPE)
{
	if (ExceptionGlobal.message) return (TYPE) 0;
};

#routine exception_globalBypassReturnValue(VALUE)
{
	if (ExceptionGlobal.message) return VALUE;
};

#routine exception_structThrowExit(EXCEPTION,STRUCT,MESSAGE)
{
	if (!ExceptionBlock) exception_panic(MESSAGE);
	EXCEPTION.message = MESSAGE;
	mutex_unlock(STRUCT->mutex);
	return;
};

#routine exception_structThrowReturn(EXCEPTION,STRUCT,MESSAGE)
{
	if (!ExceptionBlock) exception_panic(MESSAGE);
	EXCEPTION.message = MESSAGE;
	mutex_unlock(STRUCT->mutex);
	return 0;
};

#routine exception_structThrowReturnCast(EXCEPTION,STRUCT,MESSAGE,#TYPE)
{
	if (!ExceptionBlock) exception_panic(MESSAGE);
	EXCEPTION.message = MESSAGE;
	mutex_unlock(STRUCT->mutex);
	return (TYPE) 0;
};

#routine exception_structThrowReturnValue(EXCEPTION,STRUCT,MESSAGE,VALUE)
{
	if (!ExceptionBlock) exception_panic(MESSAGE);
	EXCEPTION.message = MESSAGE;
	mutex_unlock(STRUCT->mutex);
	return VALUE;
};

#routine exception_structBypassExit(EXCEPTION,STRUCT)
{
	if (EXCEPTION.message)
	{
		mutex_unlock(STRUCT->mutex);
		return;
	};
};

#routine exception_structBypassReturn(EXCEPTION,STRUCT)
{
	if (EXCEPTION.message)
	{
		mutex_unlock(STRUCT->mutex);
		return 0;
	};
};

#routine exception_structBypassReturnCast(EXCEPTION,STRUCT,#TYPE)
{
	if (EXCEPTION.message)
	{
		mutex_unlock(STRUCT->mutex);
		return (TYPE) 0;
	};
};

#routine exception_structBypassReturnValue(EXCEPTION,STRUCT,VALUE)
{
	if (EXCEPTION.message)
	{
		mutex_unlock(STRUCT->mutex);
		return VALUE;
	};
};

#routine exception_routineThrow(EXCEPTION,MESSAGE)
{
	if (!ExceptionBlock) exception_panic(MESSAGE);
	EXCEPTION.message = MESSAGE;
	break;
};

#routine exception_routineBypass(EXCEPTION)
{
	if (EXCEPTION.message) break;
};

#routine exception_catch(EXCEPTION,RETURN)
{
	if ((RETURN = EXCEPTION.message)) EXCEPTION.message = NULL;
};

void Exception_start(void)
{
	ExceptionBlock += 1;
};

void Exception_end(void)
{
	if (!ExceptionBlock) exception_panic("There is no exception block to end");
	ExceptionBlock -= 1;
};

NullString Exception_catch(void)
{
	NullString message;
	exception_catch(ExceptionGlobal,message);
	return message;
};

void Exception_throw(NullString MESSAGE)
{
	exception_panic(MESSAGE);
};

void Exception_debug(NullString MESSAGE)
{
	printf("EXCEPTION: %s.\n",MESSAGE);
};
