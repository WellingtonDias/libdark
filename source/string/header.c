block_define(DKblock_character,DKcharacter);

struct _string
{
	DKblock_character block;
	DKmutex mutex;
};

void dkString_debug(DKstring *STRING,DKnullString LABEL)
{
	safe_start(STRING);
	printf("STRING { length: %lli,source: \"%.*s\" } #%s\n",(STRING->block).size,(DKu32) (STRING->block).size,(STRING->block).start,LABEL);
	safe_end(STRING);
};
