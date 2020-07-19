DKstring *dkString_create(void)
{
	DKstring *string = NULL;
	unsafe_start();
	struct_createFromNothing(DKstring,DKcharacter,string);
	return string;
};

DKstring *dkString_createFromMemory(DKnstring SOURCE,DKusize SIZE,DKssize START,DKssize END)
{
	DKstring *string = NULL;
	unsafe_start();
	DKusize size = (SIZE > 0)? SIZE : strlen(SOURCE);
	struct_createFromMemory(DKstring,DKcharacter,SOURCE,size,START,END,string);
	return string;
};

DKstring *dkString_createFromFile(DKnstring FILE_NAME,DKssize START,DKssize END)
{
	DKstring *string = NULL;
	unsafe_start();
	struct_createFromFile(DKstring,DKcharacter,FILE_NAME,"r",START,END,string);
	return string;
};

DKstring *dkString_createFromCopy(DKstring *STRING,DKssize START,DKssize END)
{
	DKstring *string = NULL;
	safe_start(STRING);
	struct_createFromMemory(DKstring,DKcharacter,(STRING->stream).start,(STRING->stream).size,START,END,string);
	safe_endReturn(STRING,string);
};

DKstring *dkString_destroy(DKstring *STRING)
{
	safe_start(STRING);
	struct_destroy(STRING);
	return NULL;
};
