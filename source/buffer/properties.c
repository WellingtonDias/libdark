DKu8 dkBuffer_setEndian(DKbuffer *BUFFER,DKu8 ENDIAN)
{
	safe_start(BUFFER);
	DKu8 endian = BUFFER->endian;
	buffer_calculateEndian(ENDIAN,BUFFER->endian);
	error_bypassReturn();
	safe_endReturn(BUFFER,endian);
};

DKu8 dkBuffer_getEndian(DKbuffer *BUFFER)
{
	safe_start(BUFFER);
	DKu8 endian = BUFFER->endian;
	safe_endReturn(BUFFER,endian);
};

DKusize dkBuffer_setOffset(DKbuffer *BUFFER,DKusize OFFSET)
{
	safe_start(BUFFER);
	DKusize offset = BUFFER->offset;
	BUFFER->offset = OFFSET;
	safe_endReturn(BUFFER,offset);
};

DKusize dkBuffer_resetOffset(DKbuffer *BUFFER)
{
	safe_start(BUFFER);
	DKusize offset = BUFFER->offset;
	BUFFER->offset = 0;
	safe_endReturn(BUFFER,offset);
};

DKusize dkBuffer_getOffset(DKbuffer *BUFFER)
{
	safe_start(BUFFER);
	DKusize offset = BUFFER->offset;
	safe_endReturn(BUFFER,offset);
};

DKu8 *dkBuffer_getSource(DKbuffer *BUFFER)
{
	safe_start(BUFFER);
	DKu8 *source = block_getSource(BUFFER->block);
	safe_endReturn(BUFFER,source);
};

DKusize dkBuffer_setSize(DKbuffer *BUFFER,DKusize SIZE)
{
	DKusize size;
	safe_start(BUFFER);
	block_setSize(BUFFER->block,DKu8,SIZE,size);
	safe_endReturn(BUFFER,size);
};

DKusize dkBuffer_getSize(DKbuffer *BUFFER)
{
	safe_start(BUFFER);
	DKusize size = block_getSize(BUFFER->block);
	safe_endReturn(BUFFER,size);
};

DKboolean dkBuffer_isEmpty(DKbuffer *BUFFER)
{
	safe_start(BUFFER);
	DKboolean empty = block_isEmpty(BUFFER->block);
	safe_endReturn(BUFFER,empty);
};

void dkBuffer_setLock(DKbuffer *BUFFER,DKboolean LOCK)
{
	safe_start(BUFFER);
	mutex_setLock(BUFFER->mutex,LOCK);
	safe_end(BUFFER);
};

DKboolean dkBuffer_getLock(DKbuffer *BUFFER)
{
	safe_start(BUFFER);
	DKboolean lock = mutex_getLock(BUFFER->mutex);
	safe_endReturn(BUFFER,lock);
};
