thread_local NullString ExceptionMessage;
thread_local UnsignedSize ExceptionBlock;

#routine exception_set(MESSAGE)
{
	ExceptionMessage = MESSAGE;
};

#macro exception_get()
{
	ExceptionMessage
};

#routine exception_try()
{
	if (!ExceptionBlock) exception_throw(ExceptionMessage);
};

#routine exception_throwBreak(MESSAGE)
{
	exception_set(MESSAGE);
	exception_try();
	break;
};

#routine exception_throwExit(MESSAGE)
{
	exception_set(MESSAGE);
	exception_try();
	return;
};

#routine exception_throwReturn(MESSAGE)
{
	exception_set(MESSAGE);
	exception_try();
	return 0;
};

#routine exception_throwReturnCast(MESSAGE,#TYPE)
{
	exception_set(MESSAGE);
	exception_try();
	return (TYPE) 0;
};

#routine exception_throwReturnValue(MESSAGE,VALUE)
{
	exception_set(MESSAGE);
	exception_try();
	return VALUE;
};

#routine exception_bypassBreak()
{
	if (exception_get()) break;
};

#routine exception_bypassExit()
{
	if (exception_get()) return;
};

#routine exception_bypassReturn()
{
	if (exception_get()) return 0;
};

#routine exception_bypassReturnCast(#TYPE)
{
	if (exception_get()) return (TYPE) 0;
};

#routine exception_bypassReturnValue(VALUE)
{
	if (exception_get()) return VALUE;
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
