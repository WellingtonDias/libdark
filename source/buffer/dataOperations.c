#macro buffer_getScalar(BUFFER,SCALAR,TYPE,SOURCE,SIZE)
{
	if (TYPE < DARK_BUFFER_NSTRING)
	{
		SOURCE = (DKu8*) &SCALAR;
		SIZE = BufferSize[TYPE];
	}
	else
	{
		switch (TYPE)
		{
			case DARK_BUFFER_NSTRING:
			case DARK_BUFFER_RSTRING:
			{
				SOURCE = (DKu8*) SCALAR.nstring;
				SIZE = strlen(SCALAR.nstring);
				if (TYPE == DARK_BUFFER_NSTRING) ++SIZE;
				else if (SIZE == 0) error_throw("invalid SOURCE");
				break;
			};
			default: error_throw("invalid TYPE");
		};
	};
};

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
	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
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
	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
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
	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
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
	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
	error_bypass();
	block_write(BUFFER->block,DKu8,offset,SOURCE,SIZE);
	safe_end(BUFFER);
};

#macro buffer_getStringLength(BLOCK,OFFSET,LENGTH)
{
	if (OFFSET >= BLOCK.size) error_throwCastReturn("invalid OFFSET",DKscalar);
	while (true)
	{
		if (BLOCK.source[OFFSET + LENGTH] == '\0') break;
		++LENGTH;
		if (OFFSET + LENGTH == BLOCK.size) error_throwCastReturn("invalid TYPE",DKscalar);
	};
	++LENGTH;
};

#macro buffer_readScalar(BLOCK,OFFSET,TYPE,SOURCE,SIZE)
{
	if (TYPE > DARK_BUFFER_NSTRING) error_throwCastReturn("invalid TYPE",DKscalar);
	if (TYPE != DARK_BUFFER_NSTRING)
	{
		SIZE = BufferSize[TYPE];
		if (SIZE > BLOCK.size) error_throwCastReturn("invalid SIZE",DKscalar);
		if ((DKssize) OFFSET > (DKssize) BLOCK.size - (DKssize) SIZE) error_throwCastReturn("invalid OFFSET",DKscalar);
		memcpy(&SOURCE,BLOCK.source + OFFSET,SIZE);
	}
	else
	{
		buffer_getStringLength(BLOCK,OFFSET,SIZE);
		if (!(SOURCE.nstring = malloc(SIZE))) error_throwCastReturn("MEMORY: malloc",DKscalar);
		memcpy(SOURCE.nstring,BLOCK.source + OFFSET,SIZE);
	};
};

DKscalar dkBuffer_readScalar(DKbuffer *BUFFER,DKu8 TYPE)
{
	DKscalar source = (DKscalar) 0;
	DKusize size = 0;
	safe_start(BUFFER);
	buffer_readScalar(BUFFER->block,BUFFER->offset,TYPE,source,size);
	BUFFER->offset += size;
	safe_endCastReturn(BUFFER,source,DKscalar);
};

DKscalar dkBuffer_readScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE)
{
	DKusize offset = 0;
	DKscalar source = (DKscalar) 0;
	DKusize size = 0;
	safe_start(BUFFER);
	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
	error_bypassCastReturn(DKscalar);
	buffer_readScalar(BUFFER->block,offset,TYPE,source,size);
	safe_endCastReturn(BUFFER,source,DKscalar);
};

#macro buffer_readRaw(BLOCK,OFFSET,SIZE,SOURCE)
{
	if (SIZE > BLOCK.size) error_throwReturn("invalid SIZE");
	if ((DKssize) OFFSET > (DKssize) BLOCK.size - (DKssize) SIZE) error_throwReturn("invalid OFFSET");
	if (!(SOURCE = malloc(SIZE))) error_throwReturn("MEMORY: malloc");
	memcpy(SOURCE,BLOCK.source + OFFSET,SIZE);
};

DKu8 *dkBuffer_readRaw(DKbuffer *BUFFER,DKusize SIZE)
{
	DKu8 *source = NULL;
	safe_start(BUFFER);
	buffer_readRaw(BUFFER->block,BUFFER->offset,SIZE,source);
	BUFFER->offset += SIZE;
	safe_endReturn(BUFFER,source);
};

DKu8 *dkBuffer_readRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE)
{
	DKusize offset = 0;
	DKu8 *source = NULL;
	safe_start(BUFFER);
	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
	error_bypassReturn();
	buffer_readRaw(BUFFER->block,offset,SIZE,source);
	safe_endReturn(BUFFER,source);
};

#macro buffer_erase(BLOCK,OFFSET,SIZE)
{
	#local DKusize offset;
	block_calculateUnsafePosition(OFFSET,BLOCK.size,offset);
	error_bypass();
	block_erase(BLOCK,DKu8,offset,SIZE);
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

#macro buffer_remove(BLOCK,OFFSET,SIZE)
{
	#local DKusize offset;
	block_calculateUnsafePosition(OFFSET,BLOCK.size,offset);
	error_bypass();
	block_remove(BLOCK,DKu8,offset,SIZE);
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
