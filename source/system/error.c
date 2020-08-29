thread_local DKnullString ErrorMessage;
thread_local DKusize ErrorBlock;

#routine error_set(MESSAGE)
{
	ErrorMessage = MESSAGE;
};

#macro error_get()
{
	ErrorMessage
};

#routine error_throw()
{
	if (!ErrorBlock) dkError_throw(ErrorMessage);
};

#routine error_throwBreak(MESSAGE)
{
	ErrorMessage = MESSAGE;
	error_throw();
	break;
};

#routine error_throwExit(MESSAGE)
{
	ErrorMessage = MESSAGE;
	error_throw();
	return;
};

#routine error_throwReturn(MESSAGE)
{
	ErrorMessage = MESSAGE;
	error_throw();
	return 0;
};

#routine error_throwReturnCast(MESSAGE,#TYPE)
{
	ErrorMessage = MESSAGE;
	error_throw();
	return (TYPE) 0;
};

#routine error_throwReturnValue(MESSAGE,VALUE)
{
	ErrorMessage = MESSAGE;
	error_throw();
	return VALUE;
};

#routine error_throwUnhandled()
{
	if (ErrorMessage) dkError_throw("Unhandled error found");
};

#routine error_bypassBreak()
{
	if (ErrorMessage) break;
};

#routine error_bypassExit()
{
	if (ErrorMessage) return;
};

#routine error_bypassReturn()
{
	if (ErrorMessage) return 0;
};

#routine error_bypassReturnCast(#TYPE)
{
	if (ErrorMessage) return (TYPE) 0;
};

#routine error_bypassReturnValue(VALUE)
{
	if (ErrorMessage) return VALUE;
};

void dkError_start(void)
{
	ErrorBlock += 1;
};

void dkError_end(void)
{
	if (!ErrorBlock) dkError_throw("There is no error zone to end");
	ErrorBlock -= 1;
};

DKnullString dkError_catch(void)
{
	DKnullString error;
	if (!(error = ErrorMessage)) return NULL;
	ErrorMessage = NULL;
	return error;
};

void dkError_throw(DKnullString MESSAGE)
{
	printf("ERROR: %s.\n",MESSAGE);
	exit(EXIT_FAILURE);
};

void dkError_debug(DKnullString MESSAGE)
{
	printf("ERROR: %s.\n",MESSAGE);
};
