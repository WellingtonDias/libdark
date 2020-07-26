#macro blob_getHandle(BLOB,HANDLE,TYPE,SOURCE,SIZE)
{
	if (TYPE < DARK_BLOB_NULL_STRING)
	{
		SOURCE = (DKu8*) &HANDLE;
		SIZE = blob_typeToSize[TYPE];
	}
	else
	{
		switch (TYPE)
		{
			case DARK_BLOB_NULL_STRING:
			case DARK_BLOB_RAW_STRING:
			{
				SOURCE = (DKu8*) HANDLE.nullString;
				SIZE = strlen(HANDLE.nullString);
				if (TYPE == DARK_BLOB_NULL_STRING) ++SIZE;
				else if (SIZE == 0) error_throw("invalid SOURCE");
				break;
			};
			default: error_throw("invalid TYPE");
		};
	};
};

#macro blob_read(BUFFER,OFFSET,SIZE,SOURCE)
{
	if (SIZE > block_getSize(BUFFER)) error_throwReturn("invalid SIZE");
	if ((DKssize) OFFSET > (DKssize) block_getSize(BUFFER) - (DKssize) SIZE) error_throwReturn("invalid OFFSET");
	if (!(SOURCE = malloc(SIZE))) error_throwReturn("MEMORY: malloc");
	memcpy(SOURCE,block_getSource(BUFFER) + OFFSET,SIZE);
};

#macro blob_getStringLength(BUFFER,OFFSET,LENGTH)
{
	if (OFFSET >= block_getSize(BUFFER)) error_throwCastReturn("invalid OFFSET",DKhandleUnion);
	while (true)
	{
		if (block_getSource(BUFFER)[OFFSET + LENGTH] == '\0') break;
		++LENGTH;
		if (OFFSET + LENGTH == block_getSize(BUFFER)) error_throwCastReturn("invalid TYPE",DKhandleUnion);
	};
	++LENGTH;
};

#macro blob_readHandle(BUFFER,OFFSET,TYPE,SOURCE,SIZE)
{
	if (TYPE > DARK_BLOB_NULL_STRING) error_throwCastReturn("invalid TYPE",DKhandleUnion);
	if (TYPE != DARK_BLOB_NULL_STRING)
	{
		SIZE = blob_typeToSize[TYPE];
		if (SIZE > block_getSize(BUFFER)) error_throwCastReturn("invalid SIZE",DKhandleUnion);
		if ((DKssize) OFFSET > (DKssize) block_getSize(BUFFER) - (DKssize) SIZE) error_throwCastReturn("invalid OFFSET",DKhandleUnion);
		memcpy(&SOURCE,block_getSource(BUFFER) + OFFSET,SIZE);
	}
	else
	{
		blob_getStringLength(BUFFER,OFFSET,SIZE);
		if (!(SOURCE.nullString = malloc(SIZE))) error_throwCastReturn("MEMORY: malloc",DKhandleUnion);
		memcpy(SOURCE.nullString,block_getSource(BUFFER) + OFFSET,SIZE);
	};
};

#macro blob_erase(BUFFER,OFFSET,SIZE)
{
	#local DKusize offset;
	block_calculateUnsafePosition(OFFSET,block_getSize(BUFFER),offset);
	error_bypass();
	buffer_erase(BUFFER,DKu8,offset,SIZE);
};

#macro blob_remove(BUFFER,OFFSET,SIZE)
{
	#local DKusize offset;
	block_calculateUnsafePosition(OFFSET,block_getSize(BUFFER),offset);
	error_bypass();
	buffer_remove(BUFFER,DKu8,offset,SIZE);
};

void dkBlob_insert(DKblob *BLOB,DKu8 *SOURCE,DKusize SIZE)
{
	safe_start(BLOB);
	buffer_insert(BLOB->block,DKu8,BLOB->offset,SOURCE,SIZE);
	BLOB->offset += SIZE;
	safe_end(BLOB);
};

void dkBlob_insertAt(DKblob *BLOB,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE)
{
	DKusize offset;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getSize(BLOB->block),offset);
	error_bypass();
	buffer_insert(BLOB->block,DKu8,offset,SOURCE,SIZE);
	safe_end(BLOB);
};

void dkBlob_insertHandle(DKblob *BLOB,DKhandleUnion SOURCE,DKu8 TYPE)
{
	DKu8 *source;
	DKusize size;
	safe_start(BLOB);
	blob_getHandle(BLOB,SOURCE,TYPE,source,size);
	buffer_insert(BLOB->block,DKu8,BLOB->offset,source,size);
	BLOB->offset += size;
	safe_end(BLOB);
};

void dkBlob_insertHandleAt(DKblob *BLOB,DKssize OFFSET,DKhandleUnion SOURCE,DKu8 TYPE)
{
	DKu8 *source;
	DKusize size;
	DKusize offset;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getSize(BLOB->block),offset);
	error_bypass();
	blob_getHandle(BLOB,SOURCE,TYPE,source,size);
	buffer_insert(BLOB->block,DKu8,offset,source,size);
	safe_end(BLOB);
};

void dkBlob_write(DKblob *BLOB,DKu8 *SOURCE,DKusize SIZE)
{
	safe_start(BLOB);
	buffer_write(BLOB->block,DKu8,BLOB->offset,SOURCE,SIZE);
	BLOB->offset += SIZE;
	safe_end(BLOB);
};

void dkBlob_writeAt(DKblob *BLOB,DKssize OFFSET,DKu8 *SOURCE,DKusize SIZE)
{
	DKusize offset;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getSize(BLOB->block),offset);
	error_bypass();
	buffer_write(BLOB->block,DKu8,offset,SOURCE,SIZE);
	safe_end(BLOB);
};

void dkBlob_writeHandle(DKblob *BLOB,DKhandleUnion SOURCE,DKu8 TYPE)
{
	DKu8 *source;
	DKusize size;
	safe_start(BLOB);
	blob_getHandle(BLOB,SOURCE,TYPE,source,size);
	buffer_write(BLOB->block,DKu8,BLOB->offset,source,size);
	BLOB->offset += size;
	safe_end(BLOB);
};

void dkBlob_writeHandleAt(DKblob *BLOB,DKssize OFFSET,DKhandleUnion SOURCE,DKu8 TYPE)
{
	DKusize offset;
	DKu8 *source;
	DKusize size;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getSize(BLOB->block),offset);
	error_bypass();
	blob_getHandle(BLOB,SOURCE,TYPE,source,size);
	buffer_write(BLOB->block,DKu8,offset,source,size);
	safe_end(BLOB);
};

DKu8 *dkBlob_read(DKblob *BLOB,DKusize SIZE)
{
	DKu8 *source;
	safe_start(BLOB);
	blob_read(BLOB->block,BLOB->offset,SIZE,source);
	BLOB->offset += SIZE;
	safe_endReturn(BLOB,source);
};

DKu8 *dkBlob_readAt(DKblob *BLOB,DKssize OFFSET,DKusize SIZE)
{
	DKu8 *source;
	DKusize offset;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getSize(BLOB->block),offset);
	error_bypassReturn();
	blob_read(BLOB->block,offset,SIZE,source);
	safe_endReturn(BLOB,source);
};

DKhandleUnion dkBlob_readHandle(DKblob *BLOB,DKu8 TYPE)
{
	DKhandleUnion source;
	DKusize size;
	safe_start(BLOB);
	blob_readHandle(BLOB->block,BLOB->offset,TYPE,source,size);
	BLOB->offset += size;
	safe_endCastReturn(BLOB,source,DKhandleUnion);
};

DKhandleUnion dkBlob_readHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE)
{
	DKhandleUnion source;
	DKusize size;
	DKusize offset;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getSize(BLOB->block),offset);
	error_bypassCastReturn(DKhandleUnion);
	blob_readHandle(BLOB->block,offset,TYPE,source,size);
	safe_endCastReturn(BLOB,source,DKhandleUnion);
};

void dkBlob_erase(DKblob *BLOB,DKusize SIZE)
{
	safe_start(BLOB);
	buffer_erase(BLOB->block,DKu8,BLOB->offset,SIZE);
	safe_end(BLOB);
};

void dkBlob_eraseAt(DKblob *BLOB,DKssize OFFSET,DKusize SIZE)
{
	safe_start(BLOB);
	blob_erase(BLOB->block,OFFSET,SIZE);
	safe_end(BLOB);
};

void dkBlob_eraseHandle(DKblob *BLOB,DKu8 TYPE)
{
	safe_start(BLOB);
	if (TYPE > DARK_BLOB_CHARACTER) error_throw("invalid TYPE");
	buffer_erase(BLOB->block,DKu8,BLOB->offset,blob_typeToSize[TYPE]);
	safe_end(BLOB);
};

void dkBlob_eraseHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE)
{
	safe_start(BLOB);
	if (TYPE > DARK_BLOB_CHARACTER) error_throw("invalid TYPE");
	blob_erase(BLOB->block,OFFSET,blob_typeToSize[TYPE]);
	safe_end(BLOB);
};

void dkBlob_remove(DKblob *BLOB,DKusize SIZE)
{
	safe_start(BLOB);
	buffer_remove(BLOB->block,DKu8,BLOB->offset,SIZE);
	safe_end(BLOB);
};

void dkBlob_removeAt(DKblob *BLOB,DKssize OFFSET,DKusize SIZE)
{
	safe_start(BLOB);
	blob_remove(BLOB->block,OFFSET,SIZE);
	safe_end(BLOB);
};

void dkBlob_removeHandle(DKblob *BLOB,DKu8 TYPE)
{
	safe_start(BLOB);
	if (TYPE > DARK_BLOB_CHARACTER) error_throw("invalid TYPE");
	buffer_remove(BLOB->block,DKu8,BLOB->offset,blob_typeToSize[TYPE]);
	safe_end(BLOB);
};

void dkBlob_removeHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE)
{
	safe_start(BLOB);
	if (TYPE > DARK_BLOB_CHARACTER) error_throw("invalid TYPE");
	blob_remove(BLOB->block,OFFSET,blob_typeToSize[TYPE]);
	safe_end(BLOB);
};
