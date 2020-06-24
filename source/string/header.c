block_define(DKblock_character,DKcharacter);

struct _string
{
	DKblock_character block;
	DKmutex mutex;
};

void dkString_debug(DKstring *STRING,DKnstring LABEL)
{
	safe_start(STRING);
	printf("STRING { size: %lli, source: \"%.*s\" } #%s\n",(STRING->block).size,(DKu32) (STRING->block).size,(STRING->block).source,LABEL);
	safe_end(STRING);
};
