stream_define(DKstream_u8,DKu8);

struct _buffer
{
	DKu8 endian;
	DKusize offset;
	DKstream_u8 stream;
	DKmutex mutex;
};

DKu8 BufferSize[28] = {1,1,1,2,2,2,2,2,2,4,4,4,4,4,4,8,8,8,8,8,8,4,4,4,8,8,8,1};
DKnstring BufferNominalEndian[3] = {"UNDEFINED","LITTLE","BIG"};

#macro buffer_calculateEndian(INPUT_ENDIAN,OUTPUT_ENDIAN)
{
	switch (INPUT_ENDIAN)
	{
		case DARK_BUFFER_UNDEFINED_ENDIAN:
		case DARK_BUFFER_LITTLE_ENDIAN:
		case DARK_BUFFER_BIG_ENDIAN: OUTPUT_ENDIAN = INPUT_ENDIAN; break;
		case DARK_BUFFER_SYSTEM_ENDIAN: OUTPUT_ENDIAN = DARK_ENDIAN; break;
		default: error_set("invalid ENDIAN");
	};
};

void dkBuffer_debug(DKbuffer *BUFFER,DKnstring LABEL)
{
	safe_start(BUFFER);
	printf("BUFFER { endian: %s, offset: %lli, size: %lli, capacity: %lli, source: ",BufferNominalEndian[BUFFER->endian],BUFFER->offset,(BUFFER->stream).size,(BUFFER->stream).capacity);
	for (DKusize i = 0; i < (BUFFER->stream).size; ++i) printf("%lli ",(DKusize) (BUFFER->stream).source[i]);
	printf("} #%s\n",LABEL);
	safe_end(BUFFER);
};
