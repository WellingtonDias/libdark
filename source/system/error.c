thread_local DKnstring ErrorMessage = NULL;
thread_local DKboolean ErrorUnsafe = 0;

#macro error_safeThrow()
{
	if (!ErrorUnsafe) dkError_throw(ErrorMessage);
};

#macro error_set(MESSAGE)
{
	ErrorMessage = MESSAGE;
	error_safeThrow();
	break;
};

#macro error_throw(MESSAGE)
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

#macro error_throwCastReturn(MESSAGE,#TYPE)
{
	ErrorMessage = MESSAGE;
	error_safeThrow();
	return (TYPE) 0;
};

#macro error_throwUnhandled()
{
	if (ErrorMessage) dkError_throw("Unhandled error found");
};

#macro error_bypass()
{
	if (ErrorMessage) return;
};

#macro error_bypassReturn()
{
	if (ErrorMessage) return 0;
};

#macro error_bypassCastReturn(#TYPE)
{
	if (ErrorMessage) return (TYPE) 0;
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

DKnstring dkError_catch(void)
{
	DKnstring error;
	if (!(error = ErrorMessage)) return NULL;
	ErrorMessage = NULL;
	return error;
};

void dkError_throw(DKnstring MESSAGE)
{
	printf("Error: %s.\n",MESSAGE);
	exit(EXIT_FAILURE);
};

void dkError_debug(DKnstring MESSAGE)
{
	printf("Error: %s.\n",MESSAGE);
};
