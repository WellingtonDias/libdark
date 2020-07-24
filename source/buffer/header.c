block_define(DKblock_u8,DKu8);

struct _buffer
{
	DKu8 endian;
	DKusize offset;
	DKblock_u8 block;
	DKmutex mutex;
};

DKu8 BufferSize[28] = {1,1,1,2,2,2,2,2,2,4,4,4,4,4,4,8,8,8,8,8,8,4,4,4,8,8,8,1};
DKnstring BufferNominalEndian[3] = {"UNDEFINED","LITTLE","BIG"};
DKboolean BufferUndefinedEndian[28] = {true,true,true,true,true,false,true,true,false,true,true,false,true,true,false,true,true,false,true,true,false,true,true,false,true,true,false,true};
DKboolean BufferDefinedEndian[28] = {true,true,true,false,false,true,false,false,true,false,false,true,false,false,true,false,false,true,false,false,true,false,false,true,false,false,true,true};

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
	printf("BUFFER { endian: %s, offset: %lli, size: %lli, capacity: %lli, source: ",BufferNominalEndian[BUFFER->endian],BUFFER->offset,(BUFFER->block).size,(BUFFER->block).capacity);
	for (DKusize i = 0; i < (BUFFER->block).size; ++i) printf("%lli ",(DKusize) (BUFFER->block).start[i]);
	printf("} #%s\n",LABEL);
	safe_end(BUFFER);
};
