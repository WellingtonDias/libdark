void dkBuffer_insertScalar(DKbuffer *BUFFER,DKscalar SOURCE,DKu8 TYPE)
{
	DKu8 *source = NULL;
	DKusize size = 0;
	safe_start(BUFFER);
	buffer_getScalar(BUFFER,SOURCE,TYPE,source,size);
	block_insert(BUFFER->block,DKu8,BUFFER->offset,source,size);
	BUFFER->offset += size;
	safe_end(BUFFER);
};

void dkBuffer_insertScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKscalar SOURCE,DKu8 TYPE)
{
	DKusize offset = 0;
	DKu8 *source = NULL;
	DKusize size = 0;
	safe_start(BUFFER);
	helper_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
	error_bypass();
	buffer_getScalar(BUFFER,SOURCE,TYPE,source,size);
	block_insert(BUFFER->block,DKu8,offset,source,size);
	safe_end(BUFFER);
};

void dkBuffer_insertRaw(DKbuffer *BUFFER,DKu8 *SOURCE,DKusize SIZE)
{
	safe_start(BUFFER);
	block_insert(BUFFER->block,DKu8,BUFFER->offset,SOURCE,SIZE);
	BUFFER->offset += SIZE;
	safe_end(BUFFER);
};

void dkBuffer_insertRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE)
{
	DKusize offset = 0;
	safe_start(BUFFER);
	helper_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
	error_bypass();
	block_insert(BUFFER->block,DKu8,offset,SOURCE,SIZE);
	safe_end(BUFFER);
};

void dkBuffer_writeScalar(DKbuffer *BUFFER,DKscalar SOURCE,DKu8 TYPE)
{
	DKu8 *source = NULL;
	DKusize size = 0;
	safe_start(BUFFER);
	buffer_getScalar(BUFFER,SOURCE,TYPE,source,size);
	block_write(BUFFER->block,DKu8,BUFFER->offset,source,size);
	BUFFER->offset += size;
	safe_end(BUFFER);
};

void dkBuffer_writeScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKscalar SOURCE,DKu8 TYPE)
{
	DKusize offset = 0;
	DKu8 *source = NULL;
	DKusize size = 0;
	safe_start(BUFFER);
	helper_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
	error_bypass();
	buffer_getScalar(BUFFER,SOURCE,TYPE,source,size);
	block_write(BUFFER->block,DKu8,offset,source,size);
	safe_end(BUFFER);
};

void dkBuffer_writeRaw(DKbuffer *BUFFER,DKu8 *SOURCE,DKusize SIZE)
{
	safe_start(BUFFER);
	block_write(BUFFER->block,DKu8,BUFFER->offset,SOURCE,SIZE);
	BUFFER->offset += SIZE;
	safe_end(BUFFER);
};

void dkBuffer_writeRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE)
{
	DKusize offset = 0;
	safe_start(BUFFER);
	helper_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
	error_bypass();
	block_write(BUFFER->block,DKu8,offset,SOURCE,SIZE);
	safe_end(BUFFER);
};

DKscalar dkBuffer_readScalar(DKbuffer *BUFFER,DKu8 TYPE)
{
	DKscalar scalar = (DKscalar) 0;
	DKusize size = 0;
	safe_start(BUFFER);
	buffer_readScalar(BUFFER->block,BUFFER->offset,TYPE,scalar,size);
	error_bypassCastReturn(DKscalar);
	BUFFER->offset += size;
	safe_endCastReturn(BUFFER,scalar,DKscalar);
};

DKscalar dkBuffer_readScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE)
{
	DKusize offset = 0;
	DKscalar scalar = (DKscalar) 0;
	DKusize size = 0;
	safe_start(BUFFER);
	helper_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
	error_bypassCastReturn(DKscalar);
	buffer_readScalar(BUFFER->block,offset,TYPE,scalar,size);
	error_bypassCastReturn(DKscalar);
	safe_endCastReturn(BUFFER,scalar,DKscalar);
};

DKu8 *dkBuffer_readRaw(DKbuffer *BUFFER,DKusize SIZE)
{
	DKu8 *source = NULL;
	safe_start(BUFFER);
	buffer_readRaw(BUFFER->block,BUFFER->offset,SIZE,source);
	error_bypassReturn();
	BUFFER->offset += SIZE;
	safe_endReturn(BUFFER,source);
};

DKu8 *dkBuffer_readRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE)
{
	DKusize offset = 0;
	DKu8 *source = NULL;
	safe_start(BUFFER);
	helper_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
	error_bypassReturn();
	buffer_readRaw(BUFFER->block,offset,SIZE,source);
	error_bypassReturn();
	safe_endReturn(BUFFER,source);
};

void dkBuffer_eraseScalar(DKbuffer *BUFFER,DKu8 TYPE)
{
	safe_start(BUFFER);
	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
	block_erase(BUFFER->block,DKu8,BUFFER->offset,BufferSize[TYPE]);
	safe_end(BUFFER);
};

void dkBuffer_eraseScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE)
{
	safe_start(BUFFER);
	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
	buffer_erase(BUFFER->block,OFFSET,BufferSize[TYPE]);
	safe_end(BUFFER);
};

void dkBuffer_eraseRaw(DKbuffer *BUFFER,DKusize SIZE)
{
	safe_start(BUFFER);
	block_erase(BUFFER->block,DKu8,BUFFER->offset,SIZE);
	safe_end(BUFFER);
};

void dkBuffer_eraseRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE)
{
	safe_start(BUFFER);
	buffer_erase(BUFFER->block,OFFSET,SIZE);
	safe_end(BUFFER);
};

void dkBuffer_removeScalar(DKbuffer *BUFFER,DKu8 TYPE)
{
	safe_start(BUFFER);
	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
	block_remove(BUFFER->block,DKu8,BUFFER->offset,BufferSize[TYPE]);
	safe_end(BUFFER);
};

void dkBuffer_removeScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE)
{
	safe_start(BUFFER);
	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
	buffer_remove(BUFFER->block,OFFSET,BufferSize[TYPE]);
	safe_end(BUFFER);
};

void dkBuffer_removeRaw(DKbuffer *BUFFER,DKusize SIZE)
{
	safe_start(BUFFER);
	block_remove(BUFFER->block,DKu8,BUFFER->offset,SIZE);
	safe_end(BUFFER);
};

void dkBuffer_removeRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE)
{
	safe_start(BUFFER);
	buffer_remove(BUFFER->block,OFFSET,SIZE);
	safe_end(BUFFER);
};
