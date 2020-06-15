block_define(DKblock_u8,DKu8);

struct _buffer
{
	DKusize offset;
	DKblock_u8 block;
	DKmutex mutex;
};

DKu8 BufferSize[] = {0,1,1,1,1,1,2,2,2,2,4,4,4,4,8,8,8,8,8,8,8,8,4,8};

void dkBuffer_debug(DKbuffer *BUFFER,DKchar *LABEL)
{
	safe_start(BUFFER);
	printf("BUFFER { offset: %lli, size: %lli, capacity: %lli, source: ",BUFFER->offset,(BUFFER->block).size,(BUFFER->block).capacity);
	for (DKusize i = 0; i < (BUFFER->block).size; ++i) printf("%lli ",(DKusize) (BUFFER->block).source[i]);
	printf("} #%s\n",LABEL);
	safe_end(BUFFER);
}
