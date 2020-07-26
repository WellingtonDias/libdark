thread_local DKnullString ErrorMessage;
thread_local DKboolean ErrorUnsafe;

#macro error_safeThrow()
{
	if (!ErrorUnsafe) dkError_throw(ErrorMessage);
};

#macro error_throwBreak(MESSAGE)
{
	ErrorMessage = MESSAGE;
	error_safeThrow();
	break;
};

#macro error_throwExit(MESSAGE)
{
	ErrorMessage = MESSAGE;
	error_safeThrow();
	return;
};

#macro error_throwReturn(MESSAGE)
{
	ErrorMessage = MESSAGE;
	error_safeThrow();
	return 0;
};

#macro error_throwReturnCast(MESSAGE,#TYPE)
{
	ErrorMessage = MESSAGE;
	error_safeThrow();
	return (TYPE) 0;
};

#macro error_throwReturnValue(MESSAGE,VALUE)
{
	ErrorMessage = MESSAGE;
	error_safeThrow();
	return VALUE;
};

#macro error_throwUnhandled()
{
	if (ErrorMessage) dkError_throw("Unhandled error found");
};

#macro error_bypassBreak()
{
	if (ErrorMessage) break;
};

#macro error_bypassExit()
{
	if (ErrorMessage) return;
};

#macro error_bypassReturn()
{
	if (ErrorMessage) return 0;
};

#macro error_bypassReturnCast(#TYPE)
{
	if (ErrorMessage) return (TYPE) 0;
};

#macro error_bypassReturnValue(VALUE)
{
	if (ErrorMessage) return VALUE;
};

void dkError_start(void)
{
	ErrorUnsafe += 1;
};

void dkError_end(void)
{
	if (!ErrorUnsafe) dkError_throw("There is no unsafe zone to end");
	ErrorUnsafe -= 1;
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
