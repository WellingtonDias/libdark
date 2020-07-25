DKstring *dkString_create(void)
{
	DKstring *string;
	unsafe_start();
	struct_createFromNothing(DKstring,DKcharacter,string);
	return string;
};

DKstring *dkString_createFromMemory(DKnullString SOURCE,DKusize LENGTH,DKssize START,DKssize END)
{
	DKstring *string;
	unsafe_start();
	DKusize length = (LENGTH > 0)? LENGTH : strlen(SOURCE);
	struct_createFromMemory(DKstring,DKcharacter,SOURCE,length,START,END,string);
	return string;
};

DKstring *dkString_createFromFile(DKnullString FILE_NAME,DKssize START,DKssize END)
{
	DKstring *string;
	unsafe_start();
	struct_create(DKstring,string);
	buffer_createFromFile(string->block,DKcharacter,FILE_NAME,"r",START,END);
	return string;
};

DKstring *dkString_createFromCopy(DKstring *STRING,DKssize START,DKssize END)
{
	DKstring *string;
	safe_start(STRING);
	struct_createFromMemory(DKstring,DKcharacter,(STRING->block).start,(STRING->block).size,START,END,string);
	safe_endReturn(STRING,string);
};

DKstring *dkString_destroy(DKstring *STRING)
{
	safe_start(STRING);
	struct_destroy(STRING);
	return NULL;
};
