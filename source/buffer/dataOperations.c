// #macro buffer_getHandle(BUFFER,HANDLE,TYPE,SOURCE,SIZE)
// {
// 	if (TYPE < DARK_BUFFER_NSTRING)
// 	{
// 		SOURCE = (DKu8*) &HANDLE;
// 		SIZE = BufferSize[TYPE];
// 	}
// 	else
// 	{
// 		switch (TYPE)
// 		{
// 			case DARK_BUFFER_NSTRING:
// 			case DARK_BUFFER_RSTRING:
// 			{
// 				SOURCE = (DKu8*) HANDLE.nstring;
// 				SIZE = strlen(HANDLE.nstring);
// 				if (TYPE == DARK_BUFFER_NSTRING) ++SIZE;
// 				else if (SIZE == 0) error_throw("invalid SOURCE");
// 				break;
// 			};
// 			default: error_throw("invalid TYPE");
// 		};
// 	};
// };

// void dkBuffer_insertHandle(DKbuffer *BUFFER,DKhandle SOURCE,DKu8 TYPE)
// {
// 	DKu8 *source;
// 	DKusize size;
// 	safe_start(BUFFER);
// 	buffer_getHandle(BUFFER,SOURCE,TYPE,source,size);
// 	blob_insert(BUFFER->block,DKu8,BUFFER->offset,source,size);
// 	BUFFER->offset += size;
// 	safe_end(BUFFER);
// };

// void dkBuffer_insertHandleAt(DKbuffer *BUFFER,DKssize OFFSET,DKhandle SOURCE,DKu8 TYPE)
// {
// 	DKusize offset;
// 	DKu8 *source;
// 	DKusize size;
// 	safe_start(BUFFER);
// 	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
// 	error_bypass();
// 	buffer_getHandle(BUFFER,SOURCE,TYPE,source,size);
// 	blob_insert(BUFFER->block,DKu8,offset,source,size);
// 	safe_end(BUFFER);
// };

// void dkBuffer_insertRaw(DKbuffer *BUFFER,DKu8 *SOURCE,DKusize SIZE)
// {
// 	safe_start(BUFFER);
// 	blob_insert(BUFFER->block,DKu8,BUFFER->offset,SOURCE,SIZE);
// 	BUFFER->offset += SIZE;
// 	safe_end(BUFFER);
// };

// void dkBuffer_insertRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE)
// {
// 	DKusize offset;
// 	safe_start(BUFFER);
// 	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
// 	error_bypass();
// 	blob_insert(BUFFER->block,DKu8,offset,SOURCE,SIZE);
// 	safe_end(BUFFER);
// };

// void dkBuffer_writeHandle(DKbuffer *BUFFER,DKhandle SOURCE,DKu8 TYPE)
// {
// 	DKu8 *source;
// 	DKusize size;
// 	safe_start(BUFFER);
// 	buffer_getHandle(BUFFER,SOURCE,TYPE,source,size);
// 	blob_write(BUFFER->block,DKu8,BUFFER->offset,source,size);
// 	BUFFER->offset += size;
// 	safe_end(BUFFER);
// };

// void dkBuffer_writeHandleAt(DKbuffer *BUFFER,DKssize OFFSET,DKhandle SOURCE,DKu8 TYPE)
// {
// 	DKusize offset;
// 	DKu8 *source;
// 	DKusize size;
// 	safe_start(BUFFER);
// 	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
// 	error_bypass();
// 	buffer_getHandle(BUFFER,SOURCE,TYPE,source,size);
// 	blob_write(BUFFER->block,DKu8,offset,source,size);
// 	safe_end(BUFFER);
// };

// void dkBuffer_writeRaw(DKbuffer *BUFFER,DKu8 *SOURCE,DKusize SIZE)
// {
// 	safe_start(BUFFER);
// 	blob_write(BUFFER->block,DKu8,BUFFER->offset,SOURCE,SIZE);
// 	BUFFER->offset += SIZE;
// 	safe_end(BUFFER);
// };

// void dkBuffer_writeRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE)
// {
// 	DKusize offset;
// 	safe_start(BUFFER);
// 	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
// 	error_bypass();
// 	blob_write(BUFFER->block,DKu8,offset,SOURCE,SIZE);
// 	safe_end(BUFFER);
// };

// #macro buffer_getStringLength(STREAM,OFFSET,LENGTH)
// {
// 	if (OFFSET >= STREAM.size) error_throwCastReturn("invalid OFFSET",DKhandle);
// 	while (true)
// 	{
// 		if (STREAM.source[OFFSET + LENGTH] == '\0') break;
// 		++LENGTH;
// 		if (OFFSET + LENGTH == STREAM.size) error_throwCastReturn("invalid TYPE",DKhandle);
// 	};
// 	++LENGTH;
// };

// #macro buffer_readHandle(STREAM,OFFSET,TYPE,SOURCE,SIZE)
// {
// 	if (TYPE > DARK_BUFFER_NSTRING) error_throwCastReturn("invalid TYPE",DKhandle);
// 	if (TYPE != DARK_BUFFER_NSTRING)
// 	{
// 		SIZE = BufferSize[TYPE];
// 		if (SIZE > STREAM.size) error_throwCastReturn("invalid SIZE",DKhandle);
// 		if ((DKssize) OFFSET > (DKssize) STREAM.size - (DKssize) SIZE) error_throwCastReturn("invalid OFFSET",DKhandle);
// 		memcpy(&SOURCE,STREAM.source + OFFSET,SIZE);
// 	}
// 	else
// 	{
// 		buffer_getStringLength(STREAM,OFFSET,SIZE);
// 		if (!(SOURCE.nstring = malloc(SIZE))) error_throwCastReturn("MEMORY: malloc",DKhandle);
// 		memcpy(SOURCE.nstring,STREAM.source + OFFSET,SIZE);
// 	};
// };

// DKhandle dkBuffer_readHandle(DKbuffer *BUFFER,DKu8 TYPE)
// {
// 	DKhandle source;
// 	DKusize size;
// 	safe_start(BUFFER);
// 	buffer_readHandle(BUFFER->block,BUFFER->offset,TYPE,source,size);
// 	BUFFER->offset += size;
// 	safe_endCastReturn(BUFFER,source,DKhandle);
// };

// DKhandle dkBuffer_readHandleAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE)
// {
// 	DKusize offset;
// 	DKhandle source;
// 	DKusize size;
// 	safe_start(BUFFER);
// 	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
// 	error_bypassCastReturn(DKhandle);
// 	buffer_readHandle(BUFFER->block,offset,TYPE,source,size);
// 	safe_endCastReturn(BUFFER,source,DKhandle);
// };

// #macro buffer_readRaw(STREAM,OFFSET,SIZE,SOURCE)
// {
// 	if (SIZE > STREAM.size) error_throwReturn("invalid SIZE");
// 	if ((DKssize) OFFSET > (DKssize) STREAM.size - (DKssize) SIZE) error_throwReturn("invalid OFFSET");
// 	if (!(SOURCE = malloc(SIZE))) error_throwReturn("MEMORY: malloc");
// 	memcpy(SOURCE,STREAM.source + OFFSET,SIZE);
// };

// DKu8 *dkBuffer_readRaw(DKbuffer *BUFFER,DKusize SIZE)
// {
// 	DKu8 *source;
// 	safe_start(BUFFER);
// 	buffer_readRaw(BUFFER->block,BUFFER->offset,SIZE,source);
// 	BUFFER->offset += SIZE;
// 	safe_endReturn(BUFFER,source);
// };

// DKu8 *dkBuffer_readRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE)
// {
// 	DKusize offset;
// 	DKu8 *source;
// 	safe_start(BUFFER);
// 	block_calculateUnsafePosition(OFFSET,(BUFFER->block).size,offset);
// 	error_bypassReturn();
// 	buffer_readRaw(BUFFER->block,offset,SIZE,source);
// 	safe_endReturn(BUFFER,source);
// };

// #macro buffer_erase(STREAM,OFFSET,SIZE)
// {
// 	#local DKusize offset;
// 	block_calculateUnsafePosition(OFFSET,STREAM.size,offset);
// 	error_bypass();
// 	blob_erase(STREAM,DKu8,offset,SIZE);
// };

// void dkBuffer_eraseHandle(DKbuffer *BUFFER,DKu8 TYPE)
// {
// 	safe_start(BUFFER);
// 	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
// 	blob_erase(BUFFER->block,DKu8,BUFFER->offset,BufferSize[TYPE]);
// 	safe_end(BUFFER);
// };

// void dkBuffer_eraseHandleAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE)
// {
// 	safe_start(BUFFER);
// 	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
// 	buffer_erase(BUFFER->block,OFFSET,BufferSize[TYPE]);
// 	safe_end(BUFFER);
// };

// void dkBuffer_eraseRaw(DKbuffer *BUFFER,DKusize SIZE)
// {
// 	safe_start(BUFFER);
// 	blob_erase(BUFFER->block,DKu8,BUFFER->offset,SIZE);
// 	safe_end(BUFFER);
// };

// void dkBuffer_eraseRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE)
// {
// 	safe_start(BUFFER);
// 	buffer_erase(BUFFER->block,OFFSET,SIZE);
// 	safe_end(BUFFER);
// };

// #macro buffer_remove(STREAM,OFFSET,SIZE)
// {
// 	#local DKusize offset;
// 	block_calculateUnsafePosition(OFFSET,STREAM.size,offset);
// 	error_bypass();
// 	blob_remove(STREAM,DKu8,offset,SIZE);
// };

// void dkBuffer_removeHandle(DKbuffer *BUFFER,DKu8 TYPE)
// {
// 	safe_start(BUFFER);
// 	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
// 	blob_remove(BUFFER->block,DKu8,BUFFER->offset,BufferSize[TYPE]);
// 	safe_end(BUFFER);
// };

// void dkBuffer_removeHandleAt(DKbuffer *BUFFER,DKssize OFFSET,DKu8 TYPE)
// {
// 	safe_start(BUFFER);
// 	if (TYPE > DARK_BUFFER_F64) error_throw("invalid TYPE");
// 	buffer_remove(BUFFER->block,OFFSET,BufferSize[TYPE]);
// 	safe_end(BUFFER);
// };

// void dkBuffer_removeRaw(DKbuffer *BUFFER,DKusize SIZE)
// {
// 	safe_start(BUFFER);
// 	blob_remove(BUFFER->block,DKu8,BUFFER->offset,SIZE);
// 	safe_end(BUFFER);
// };

// void dkBuffer_removeRawAt(DKbuffer *BUFFER,DKssize OFFSET,DKusize SIZE)
// {
// 	safe_start(BUFFER);
// 	buffer_remove(BUFFER->block,OFFSET,SIZE);
// 	safe_end(BUFFER);
// };
