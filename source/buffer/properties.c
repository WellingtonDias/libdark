void dkBuffer_setEndian(DKbuffer *BUFFER,DKu8 ENDIAN)
{
	safe_start(BUFFER);
	buffer_calculateEndian(BUFFER,ENDIAN,BUFFER->endian);
	safe_end(BUFFER);
};

DKu8 dkBuffer_getEndian(DKbuffer *BUFFER)
{
	unsafe_start();
	return BUFFER->endian;
};

DKusize dkBuffer_setOffset(DKbuffer *BUFFER,DKu8 KIND,DKssize OFFSET)
{
	DKssize newOffset = 0;
	safe_start(BUFFER);
	buffer_calculateOffset(BUFFER,KIND,OFFSET,newOffset);
	DKusize oldOffset = BUFFER->offset;
	BUFFER->offset = newOffset;
	safe_endReturn(BUFFER,oldOffset);
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
	unsafe_start();
	return BUFFER->offset;
};

DKu8 *dkBuffer_getSource(DKbuffer *BUFFER)
{
	unsafe_start();
	return block_getSource(BUFFER->block);
};

DKusize dkBuffer_setSize(DKbuffer *BUFFER,DKu8 KIND,DKssize SIZE)
{
	DKusize size = 0;
	safe_start(BUFFER);
	block_setSize(BUFFER->block,DKu8,KIND,SIZE,size);
	safe_endReturn(BUFFER,size);
};

DKusize dkBuffer_getSize(DKbuffer *BUFFER)
{
	unsafe_start();
	return block_getSize(BUFFER->block);
};

DKboolean dkBuffer_isEmpty(DKbuffer *BUFFER)
{
	unsafe_start();
	return block_isEmpty(BUFFER->block);
};

void dkBuffer_setLock(DKbuffer *BUFFER,DKboolean LOCK)
{
	safe_start(BUFFER);
	mutex_setLock(BUFFER->mutex,LOCK);
	safe_end(BUFFER);
};

DKboolean dkBuffer_getLock(DKbuffer *BUFFER)
{
	unsafe_start();
	return mutex_getLock(BUFFER->mutex);
};
