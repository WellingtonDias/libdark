DKstring *dkString_create(void)
{
	DKstring *string = NULL;
	DKnstring source = NULL;
	unsafe_start();
	if (!(source = malloc(1))) error_throwReturn("MEMORY: malloc");
	blob_create(DKstring,source,0,1,string);
	return string;
};

DKstring *dkString_createFromRaw(DKnstring SOURCE,DKusize SIZE,DKssize START,DKssize END)
{
	DKstring *string = NULL;
	unsafe_start();
	DKusize size = (SIZE > 0)? SIZE : strlen(SOURCE);
	blob_createFromRaw(DKstring,DKcharacter,SOURCE,size,START,END,string);
	return string;
};

DKstring *dkString_createFromFile(DKnstring FILE_NAME,DKssize START,DKssize END)
{
	DKstring *string = NULL;
	unsafe_start();
	blob_createFromFile(DKstring,DKcharacter,FILE_NAME,"r",START,END,string);
	return string;
};

DKstring *dkString_createFromCopy(DKstring *STRING,DKssize START,DKssize END)
{
	DKstring *string = NULL;
	safe_start(STRING);
	blob_createFromRaw(DKstring,DKcharacter,(STRING->block).source,(STRING->block).size,START,END,string);
	safe_endReturn(STRING,string);
};

DKstring *dkString_destroy(DKstring *STRING)
{
	safe_start(STRING);
	blob_destroy(STRING);
	return NULL;
};
