block_define(DKblock_u8,DKu8);

struct _buffer
{
	DKu8 endian;
	DKusize offset;
	DKblock_u8 block;
	DKmutex mutex;
};

DKu8 BufferSize[] = {1,1,1,2,2,4,4,8,8,4,8,1};
DKcharacter *BufferEndian[] = {"UNDEFINED","LITTLE","BIG"};

void dkBuffer_debug(DKbuffer *BUFFER,DKcharacter *LABEL)
{
	safe_start(BUFFER);
	printf("BUFFER { endian: %s, offset: %lli, size: %lli, capacity: %lli, source: ",BufferEndian[BUFFER->endian],BUFFER->offset,(BUFFER->block).size,(BUFFER->block).capacity);
	for (DKusize i = 0; i < (BUFFER->block).size; ++i) printf("%lli ",(DKusize) (BUFFER->block).source[i]);
	printf("} #%s\n",LABEL);
	safe_end(BUFFER);
};
