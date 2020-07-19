stream_define(DKstream_character,DKcharacter);

struct _string
{
	DKstream_character stream;
	DKmutex mutex;
};

void dkString_debug(DKstring *STRING,DKnstring LABEL)
{
	safe_start(STRING);
	printf("STRING { size: %lli, source: \"%.*s\" } #%s\n",(STRING->stream).size,(DKu32) (STRING->stream).size,(STRING->stream).source,LABEL);
	safe_end(STRING);
};
