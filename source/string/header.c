block_define(DKblock_character,DKcharacter);

struct _string
{
	DKblock_character block;
	DKmutex mutex;
};

void dkString_debug(DKstring *STRING,DKnullString LABEL)
{
	safe_start(STRING);
	printf("STRING { length: %lli, source: \"%.*s\" } #%s\n",block_getLength(STRING->block),(DKu32) block_getLength(STRING->block),block_getSource(STRING->block),LABEL);
	safe_endExit(STRING);
};
