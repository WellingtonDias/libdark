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
	stream_insert(BUFFER->stream,DKu8,BUFFER->offset,source,size);
	BUFFER->offset += size;
	safe_end(BUFFER);
};

void dkBuffer_insertScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKscalar SOURCE,DKu8 TYPE)
{
	DKusize offset = 0;
	DKu8 *source = NULL;
	DKusize size = 0;
	safe_start(BUFFER);
	stream_calculateUnsafePosition(OFFSET,(BUFFER->stream).size,offset);
	error_bypass();
	buffer_getScalar(BUFFER,SOURCE,TYPE,source,size);
	stream_insert(BUFFER->stream,DKu8,offset,source,size);
	safe_end(BUFFER);
};

void dkBuffer_insertRaw(DKbuffer *BUFFER,DKu8 *SOURCE,DKusize SIZE)
{
	safe_start(BUFFER);
	stream_insert(BUFFER->stream,DKu8,BUFFER->offset,SOURCE,SIZE);
	BUFFER->offset += SIZE;
	safe_end(BUFFER);
};

void dkBuffer_insertRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE)
{
	DKusize offset = 0;
	safe_start(BUFFER);
	stream_calculateUnsafePosition(OFFSET,(BUFFER->stream).size,offset);
	error_bypass();
	stream_insert(BUFFER->stream,DKu8,offset,SOURCE,SIZE);
	safe_end(BUFFER);
};

void dkBuffer_writeScalar(DKbuffer *BUFFER,DKscalar SOURCE,DKu8 TYPE)
{
	DKu8 *source = NULL;
	DKusize size = 0;
	safe_start(BUFFER);
	buffer_getScalar(BUFFER,SOURCE,TYPE,source,size);
	stream_write(BUFFER->stream,DKu8,BUFFER->offset,source,size);
	BUFFER->offset += size;
	safe_end(BUFFER);
};

void dkBuffer_writeScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKscalar SOURCE,DKu8 TYPE)
{
	DKusize offset = 0;
	DKu8 *source = NULL;
	DKusize size = 0;
	safe_start(BUFFER);
	stream_calculateUnsafePosition(OFFSET,(BUFFER->stream).size,offset);
	error_bypass();
	buffer_getScalar(BUFFER,SOURCE,TYPE,source,size);
	stream_write(BUFFER->stream,DKu8,offset,source,size);
	safe_end(BUFFER);
};

void dkBuffer_writeRaw(DKbuffer *BUFFER,DKu8 *SOURCE,DKusize SIZE)
{
	safe_start(BUFFER);
	stream_write(BUFFER->stream,DKu8,BUFFER->offset,SOURCE,SIZE);
	BUFFER->offset += SIZE;
	safe_end(BUFFER);
};

void dkBuffer_writeRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE)
{
	DKusize offset = 0;
	safe_start(BUFFER);
	stream_calculateUnsafePosition(OFFSET,(BUFFER->stream).size,offset);
	error_bypass();
	stream_write(BUFFER->stream,DKu8,offset,SOURCE,SIZE);
	safe_end(BUFFER);
};

#macro buffer_getStringLength(STREAM,OFFSET,LENGTH)
{
	if (OFFSET >= STREAM.size) error_throwCastReturn("invalid OFFSET",DKscalar);
	while (true)
	{
		if (STREAM.source[OFFSET + LENGTH] == '\0') break;
		++LENGTH;
		if (OFFSET + LENGTH == STREAM.size) error_throwCastReturn("invalid TYPE",DKscalar);
	};
	++LENGTH;
};

#macro buffer_readScalar(STREAM,OFFSET,TYPE,SOURCE,SIZE)
{
	if (TYPE > DARK_BUFFER_NSTRING) error_throwCastReturn("invalid TYPE",DKscalar);
	if (TYPE != DARK_BUFFER_NSTRING)
	{
		SIZE = BufferSize[TYPE];
		if (SIZE > STREAM.size) error_throwCastReturn("invalid SIZE",DKscalar);
		if ((DKssize) OFFSET > (DKssize) STREAM.size - (DKssize) SIZE) error_throwCastReturn("invalid OFFSET",DKscalar);
		memcpy(&SOURCE,STREAM.source + OFFSET,SIZE);
	}
	else
	{
		buffer_getStringLength(STREAM,OFFSET,SIZE);
		if (!(SOURCE.nstring = malloc(SIZE))) error_throwCastReturn("MEMORY: malloc",DKscalar);
		memcpy(SOURCE.nstring,STREAM.source + OFFSET,SIZE);
	};
};

DKscalar dkBuffer_readScalar(DKbuffer *BUFFER,DKu8 TYPE)
{
	DKscalar source = (DKscalar) 0;
	DKusize size = 0;
	safe_start(BUFFER);
	buffer_readScalar(BUFFER->stream,BUFFER->offset,TYPE,source,size);
	BUFFER->offset += size;
	safe_endCastReturn(BUFFER,source,DKscalar);
};

DKscalar dkBuffer_readScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE)
{
	DKusize offset = 0;
	DKscalar source = (DKscalar) 0;
	DKusize size = 0;
	safe_start(BUFFER);
	stream_calculateUnsafePosition(OFFSET,(BUFFER->stream).size,offset);
	error_bypassCastReturn(DKscalar);
	buffer_readScalar(BUFFER->stream,offset,TYPE,source,size);
	safe_endCastReturn(BUFFER,source,DKscalar);
};

#macro buffer_readRaw(STREAM,OFFSET,SIZE,SOURCE)
{
	if (SIZE > STREAM.size) error_throwReturn("invalid SIZE");
	if ((DKssize) OFFSET > (DKssize) STREAM.size - (DKssize) SIZE) error_throwReturn("invalid OFFSET");
	if (!(SOURCE = malloc(SIZE))) error_throwReturn("MEMORY: malloc");
	memcpy(SOURCE,STREAM.source + OFFSET,SIZE);
};

DKu8 *dkBuffer_readRaw(DKbuffer *BUFFER,DKusize SIZE)
{
	DKu8 *source = NULL;
	safe_start(BUFFER);
	buffer_readRaw(BUFFER->stream,BUFFER->offset,SIZE,source);
	BUFFER->offset += SIZE;
	safe_endReturn(BUFFER,source);
};

DKu8 *dkBuffer_readRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE)
{
	DKusize offset = 0;
	DKu8 *source = NULL;
	safe_start(BUFFER);
	stream_calculateUnsafePosition(OFFSET,(BUFFER->stream).size,offset);
	error_bypassReturn();
	buffer_readRaw(BUFFER->stream,offset,SIZE,source);
	safe_endReturn(BUFFER,source);
};

#macro buffer_erase(STREAM,OFFSET,SIZE)
{
	#local DKusize offset;
	stream_calculateUnsafePosition(OFFSET,STREAM.size,offset);
	error_bypass();
	stream_erase(STREAM,DKu8,offset,SIZE);
};

void dkBuffer_eraseScalar(DKbuffer *BUFFER,DKu8 TYPE)
{
	safe_start(BUFFER);
	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
	stream_erase(BUFFER->stream,DKu8,BUFFER->offset,BufferSize[TYPE]);
	safe_end(BUFFER);
};

void dkBuffer_eraseScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE)
{
	safe_start(BUFFER);
	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
	buffer_erase(BUFFER->stream,OFFSET,BufferSize[TYPE]);
	safe_end(BUFFER);
};

void dkBuffer_eraseRaw(DKbuffer *BUFFER,DKusize SIZE)
{
	safe_start(BUFFER);
	stream_erase(BUFFER->stream,DKu8,BUFFER->offset,SIZE);
	safe_end(BUFFER);
};

void dkBuffer_eraseRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE)
{
	safe_start(BUFFER);
	buffer_erase(BUFFER->stream,OFFSET,SIZE);
	safe_end(BUFFER);
};

#macro buffer_remove(STREAM,OFFSET,SIZE)
{
	#local DKusize offset;
	stream_calculateUnsafePosition(OFFSET,STREAM.size,offset);
	error_bypass();
	stream_remove(STREAM,DKu8,offset,SIZE);
};

void dkBuffer_removeScalar(DKbuffer *BUFFER,DKu8 TYPE)
{
	safe_start(BUFFER);
	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
	stream_remove(BUFFER->stream,DKu8,BUFFER->offset,BufferSize[TYPE]);
	safe_end(BUFFER);
};

void dkBuffer_removeScalarAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE)
{
	safe_start(BUFFER);
	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
	buffer_remove(BUFFER->stream,OFFSET,BufferSize[TYPE]);
	safe_end(BUFFER);
};

void dkBuffer_removeRaw(DKbuffer *BUFFER,DKusize SIZE)
{
	safe_start(BUFFER);
	stream_remove(BUFFER->stream,DKu8,BUFFER->offset,SIZE);
	safe_end(BUFFER);
};

void dkBuffer_removeRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE)
{
	safe_start(BUFFER);
	buffer_remove(BUFFER->stream,OFFSET,SIZE);
	safe_end(BUFFER);
};
