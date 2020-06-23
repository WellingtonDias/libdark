block_define(DKblock_char,DKcharacter);

struct _string
{
	DKblock_char block;
	DKmutex mutex;
};

void dkString_debug(DKstring *STRING,DKcharacter *LABEL)
{
	safe_start(STRING);
	printf("STRING { size: %lli, source: \"%.*s\" } #%s\n",(STRING->block).size,(DKu32) (STRING->block).size,(STRING->block).source,LABEL);
	safe_end(STRING);
};
