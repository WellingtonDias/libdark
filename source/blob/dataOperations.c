// #macro blob_getHandle(BLOB,HANDLE,TYPE,SOURCE,SIZE)
// {
// 	if (TYPE < DARK_BLOB_NSTRING)
// 	{
// 		SOURCE = (DKu8*) &HANDLE;
// 		SIZE = BlobSize[TYPE];
// 	}
// 	else
// 	{
// 		switch (TYPE)
// 		{
// 			case DARK_BLOB_NSTRING:
// 			case DARK_BLOB_RSTRING:
// 			{
// 				SOURCE = (DKu8*) HANDLE.nstring;
// 				SIZE = strlen(HANDLE.nstring);
// 				if (TYPE == DARK_BLOB_NSTRING) ++SIZE;
// 				else if (SIZE == 0) error_throw("invalid SOURCE");
// 				break;
// 			};
// 			default: error_throw("invalid TYPE");
// 		};
// 	};
// };

// void dkBlob_insertHandle(DKblob *BLOB,DKhandle SOURCE,DKu8 TYPE)
// {
// 	DKu8 *source;
// 	DKusize size;
// 	safe_start(BLOB);
// 	blob_getHandle(BLOB,SOURCE,TYPE,source,size);
// 	buffer_insert(BLOB->block,DKu8,BLOB->offset,source,size);
// 	BLOB->offset += size;
// 	safe_end(BLOB);
// };

// void dkBlob_insertHandleAt(DKblob *BLOB,DKssize OFFSET,DKhandle SOURCE,DKu8 TYPE)
// {
// 	DKusize offset;
// 	DKu8 *source;
// 	DKusize size;
// 	safe_start(BLOB);
// 	block_calculateUnsafePosition(OFFSET,(BLOB->block).size,offset);
// 	error_bypass();
// 	blob_getHandle(BLOB,SOURCE,TYPE,source,size);
// 	buffer_insert(BLOB->block,DKu8,offset,source,size);
// 	safe_end(BLOB);
// };

// void dkBlob_insertRaw(DKblob *BLOB,DKu8 *SOURCE,DKusize SIZE)
// {
// 	safe_start(BLOB);
// 	buffer_insert(BLOB->block,DKu8,BLOB->offset,SOURCE,SIZE);
// 	BLOB->offset += SIZE;
// 	safe_end(BLOB);
// };

// void dkBlob_insertRawAt(DKblob *BLOB,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE)
// {
// 	DKusize offset;
// 	safe_start(BLOB);
// 	block_calculateUnsafePosition(OFFSET,(BLOB->block).size,offset);
// 	error_bypass();
// 	buffer_insert(BLOB->block,DKu8,offset,SOURCE,SIZE);
// 	safe_end(BLOB);
// };

// void dkBlob_writeHandle(DKblob *BLOB,DKhandle SOURCE,DKu8 TYPE)
// {
// 	DKu8 *source;
// 	DKusize size;
// 	safe_start(BLOB);
// 	blob_getHandle(BLOB,SOURCE,TYPE,source,size);
// 	buffer_write(BLOB->block,DKu8,BLOB->offset,source,size);
// 	BLOB->offset += size;
// 	safe_end(BLOB);
// };

// void dkBlob_writeHandleAt(DKblob *BLOB,DKssize OFFSET,DKhandle SOURCE,DKu8 TYPE)
// {
// 	DKusize offset;
// 	DKu8 *source;
// 	DKusize size;
// 	safe_start(BLOB);
// 	block_calculateUnsafePosition(OFFSET,(BLOB->block).size,offset);
// 	error_bypass();
// 	blob_getHandle(BLOB,SOURCE,TYPE,source,size);
// 	buffer_write(BLOB->block,DKu8,offset,source,size);
// 	safe_end(BLOB);
// };

// void dkBlob_writeRaw(DKblob *BLOB,DKu8 *SOURCE,DKusize SIZE)
// {
// 	safe_start(BLOB);
// 	buffer_write(BLOB->block,DKu8,BLOB->offset,SOURCE,SIZE);
// 	BLOB->offset += SIZE;
// 	safe_end(BLOB);
// };

// void dkBlob_writeRawAt(DKblob *BLOB,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE)
// {
// 	DKusize offset;
// 	safe_start(BLOB);
// 	block_calculateUnsafePosition(OFFSET,(BLOB->block).size,offset);
// 	error_bypass();
// 	buffer_write(BLOB->block,DKu8,offset,SOURCE,SIZE);
// 	safe_end(BLOB);
// };

// #macro blob_getStringLength(BUFFER,OFFSET,LENGTH)
// {
// 	if (OFFSET >= BUFFER.size) error_throwCastReturn("invalid OFFSET",DKhandle);
// 	while (true)
// 	{
// 		if (BUFFER.start[OFFSET + LENGTH] == '\0') break;
// 		++LENGTH;
// 		if (OFFSET + LENGTH == BUFFER.size) error_throwCastReturn("invalid TYPE",DKhandle);
// 	};
// 	++LENGTH;
// };

// #macro blob_readHandle(BUFFER,OFFSET,TYPE,SOURCE,SIZE)
// {
// 	if (TYPE > DARK_BLOB_NSTRING) error_throwCastReturn("invalid TYPE",DKhandle);
// 	if (TYPE != DARK_BLOB_NSTRING)
// 	{
// 		SIZE = BlobSize[TYPE];
// 		if (SIZE > BUFFER.size) error_throwCastReturn("invalid SIZE",DKhandle);
// 		if ((DKssize) OFFSET > (DKssize) BUFFER.size - (DKssize) SIZE) error_throwCastReturn("invalid OFFSET",DKhandle);
// 		memcpy(&SOURCE,BUFFER.start + OFFSET,SIZE);
// 	}
// 	else
// 	{
// 		blob_getStringLength(BUFFER,OFFSET,SIZE);
// 		if (!(SOURCE.nstring = malloc(SIZE))) error_throwCastReturn("MEMORY: malloc",DKhandle);
// 		memcpy(SOURCE.nstring,BUFFER.start + OFFSET,SIZE);
// 	};
// };

// DKhandle dkBlob_readHandle(DKblob *BLOB,DKu8 TYPE)
// {
// 	DKhandle source;
// 	DKusize size;
// 	safe_start(BLOB);
// 	blob_readHandle(BLOB->block,BLOB->offset,TYPE,source,size);
// 	BLOB->offset += size;
// 	safe_endCastReturn(BLOB,source,DKhandle);
// };

// DKhandle dkBlob_readHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE)
// {
// 	DKusize offset;
// 	DKhandle source;
// 	DKusize size;
// 	safe_start(BLOB);
// 	block_calculateUnsafePosition(OFFSET,(BLOB->block).size,offset);
// 	error_bypassCastReturn(DKhandle);
// 	blob_readHandle(BLOB->block,offset,TYPE,source,size);
// 	safe_endCastReturn(BLOB,source,DKhandle);
// };

// #macro blob_readRaw(BUFFER,OFFSET,SIZE,SOURCE)
// {
// 	if (SIZE > BUFFER.size) error_throwReturn("invalid SIZE");
// 	if ((DKssize) OFFSET > (DKssize) BUFFER.size - (DKssize) SIZE) error_throwReturn("invalid OFFSET");
// 	if (!(SOURCE = malloc(SIZE))) error_throwReturn("MEMORY: malloc");
// 	memcpy(SOURCE,BUFFER.start + OFFSET,SIZE);
// };

// DKu8 *dkBlob_readRaw(DKblob *BLOB,DKusize SIZE)
// {
// 	DKu8 *source;
// 	safe_start(BLOB);
// 	blob_readRaw(BLOB->block,BLOB->offset,SIZE,source);
// 	BLOB->offset += SIZE;
// 	safe_endReturn(BLOB,source);
// };

// DKu8 *dkBlob_readRawAt(DKblob *BLOB,DKssize OFFSET,DKusize SIZE)
// {
// 	DKusize offset;
// 	DKu8 *source;
// 	safe_start(BLOB);
// 	block_calculateUnsafePosition(OFFSET,(BLOB->block).size,offset);
// 	error_bypassReturn();
// 	blob_readRaw(BLOB->block,offset,SIZE,source);
// 	safe_endReturn(BLOB,source);
// };

// #macro blob_erase(BUFFER,OFFSET,SIZE)
// {
// 	#local DKusize offset;
// 	block_calculateUnsafePosition(OFFSET,BUFFER.size,offset);
// 	error_bypass();
// 	buffer_erase(BUFFER,DKu8,offset,SIZE);
// };

// void dkBlob_eraseHandle(DKblob *BLOB,DKu8 TYPE)
// {
// 	safe_start(BLOB);
// 	if (TYPE > DARK_BLOB_F64) error_throw("invalid TYPE");
// 	buffer_erase(BLOB->block,DKu8,BLOB->offset,BlobSize[TYPE]);
// 	safe_end(BLOB);
// };

// void dkBlob_eraseHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE)
// {
// 	safe_start(BLOB);
// 	if (TYPE > DARK_BLOB_F64) error_throw("invalid TYPE");
// 	blob_erase(BLOB->block,OFFSET,BlobSize[TYPE]);
// 	safe_end(BLOB);
// };

// void dkBlob_eraseRaw(DKblob *BLOB,DKusize SIZE)
// {
// 	safe_start(BLOB);
// 	buffer_erase(BLOB->block,DKu8,BLOB->offset,SIZE);
// 	safe_end(BLOB);
// };

// void dkBlob_eraseRawAt(DKblob *BLOB,DKssize OFFSET,DKusize SIZE)
// {
// 	safe_start(BLOB);
// 	blob_erase(BLOB->block,OFFSET,SIZE);
// 	safe_end(BLOB);
// };

// #macro blob_remove(BUFFER,OFFSET,SIZE)
// {
// 	#local DKusize offset;
// 	block_calculateUnsafePosition(OFFSET,BUFFER.size,offset);
// 	error_bypass();
// 	buffer_remove(BUFFER,DKu8,offset,SIZE);
// };

// void dkBlob_removeHandle(DKblob *BLOB,DKu8 TYPE)
// {
// 	safe_start(BLOB);
// 	if (TYPE > DARK_BLOB_F64) error_throw("invalid TYPE");
// 	buffer_remove(BLOB->block,DKu8,BLOB->offset,BlobSize[TYPE]);
// 	safe_end(BLOB);
// };

// void dkBlob_removeHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE)
// {
// 	safe_start(BLOB);
// 	if (TYPE > DARK_BLOB_F64) error_throw("invalid TYPE");
// 	blob_remove(BLOB->block,OFFSET,BlobSize[TYPE]);
// 	safe_end(BLOB);
// };

// void dkBlob_removeRaw(DKblob *BLOB,DKusize SIZE)
// {
// 	safe_start(BLOB);
// 	buffer_remove(BLOB->block,DKu8,BLOB->offset,SIZE);
// 	safe_end(BLOB);
// };

// void dkBlob_removeRawAt(DKblob *BLOB,DKssize OFFSET,DKusize SIZE)
// {
// 	safe_start(BLOB);
// 	blob_remove(BLOB->block,OFFSET,SIZE);
// 	safe_end(BLOB);
// };
