#macro blob_getHandle(BLOB,HANDLE,TYPE,SOURCE,LENGTH)
{
	if (TYPE < DARK_BLOB_NULL_STRING)
	{
		SOURCE = (DKu8*) &HANDLE;
		LENGTH = blob_typeToLength[TYPE];
	}
	else
	{
		switch (TYPE)
		{
			case DARK_BLOB_NULL_STRING:
			case DARK_BLOB_RAW_STRING:
			{
				SOURCE = (DKu8*) HANDLE.nullString;
				LENGTH = strlen(HANDLE.nullString);
				if (TYPE == DARK_BLOB_NULL_STRING) ++LENGTH;
				else if (LENGTH == 0) error_throwExit("invalid SOURCE");
				break;
			};
			default: error_throwExit("invalid TYPE");
		};
	};
};

#macro blob_read(BUFFER,OFFSET,LENGTH,SOURCE)
{
	if (LENGTH > block_getLength(BUFFER)) error_throwReturn("invalid LENGTH");
	if ((DKssize) OFFSET > (DKssize) block_getLength(BUFFER) - (DKssize) LENGTH) error_throwReturn("invalid OFFSET");
	if (!(SOURCE = malloc(LENGTH))) error_throwReturn("MEMORY: malloc");
	memcpy(SOURCE,block_getSource(BUFFER) + OFFSET,LENGTH);
};

#macro blob_getStringLength(BUFFER,OFFSET,LENGTH)
{
	if (OFFSET >= block_getLength(BUFFER)) error_throwReturnCast("invalid OFFSET",DKvalue);
	while (true)
	{
		if (block_getSource(BUFFER)[OFFSET + LENGTH] == '\0') break;
		++LENGTH;
		if (OFFSET + LENGTH == block_getLength(BUFFER)) error_throwReturnCast("invalid TYPE",DKvalue);
	};
	++LENGTH;
};

#macro blob_readHandle(BUFFER,OFFSET,TYPE,SOURCE,LENGTH)
{
	if (TYPE > DARK_BLOB_NULL_STRING) error_throwReturnCast("invalid TYPE",DKvalue);
	if (TYPE != DARK_BLOB_NULL_STRING)
	{
		LENGTH = blob_typeToLength[TYPE];
		if (LENGTH > block_getLength(BUFFER)) error_throwReturnCast("invalid LENGTH",DKvalue);
		if ((DKssize) OFFSET > (DKssize) block_getLength(BUFFER) - (DKssize) LENGTH) error_throwReturnCast("invalid OFFSET",DKvalue);
		memcpy(&SOURCE,block_getSource(BUFFER) + OFFSET,LENGTH);
	}
	else
	{
		blob_getStringLength(BUFFER,OFFSET,LENGTH);
		if (!(SOURCE.nullString = malloc(LENGTH))) error_throwReturnCast("MEMORY: malloc",DKvalue);
		memcpy(SOURCE.nullString,block_getSource(BUFFER) + OFFSET,LENGTH);
	};
};

#macro blob_erase(BUFFER,OFFSET,LENGTH)
{
	#local DKusize offset;
	block_calculateUnsafePosition(OFFSET,block_getLength(BUFFER),offset);
	error_bypassExit();
	buffer_erase(BUFFER,DKu8,offset,LENGTH);
};

#macro blob_remove(BUFFER,OFFSET,LENGTH)
{
	#local DKusize offset;
	block_calculateUnsafePosition(OFFSET,block_getLength(BUFFER),offset);
	error_bypassExit();
	buffer_remove(BUFFER,DKu8,offset,LENGTH);
};

void dkBlob_insert(DKblob *BLOB,DKu8 *SOURCE,DKusize LENGTH)
{
	safe_start(BLOB);
	buffer_insert(BLOB->block,DKu8,BLOB->offset,SOURCE,LENGTH);
	BLOB->offset += LENGTH;
	safe_endExit(BLOB);
};

void dkBlob_insertAt(DKblob *BLOB,DKssize OFFSET,DKu8 *SOURCE,DKusize LENGTH)
{
	DKusize offset;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getLength(BLOB->block),offset);
	error_bypassExit();
	buffer_insert(BLOB->block,DKu8,offset,SOURCE,LENGTH);
	safe_endExit(BLOB);
};

void dkBlob_insertHandle(DKblob *BLOB,DKvalue SOURCE,DKu8 TYPE)
{
	DKu8 *source;
	DKusize length;
	safe_start(BLOB);
	blob_getHandle(BLOB,SOURCE,TYPE,source,length);
	buffer_insert(BLOB->block,DKu8,BLOB->offset,source,length);
	BLOB->offset += length;
	safe_endExit(BLOB);
};

void dkBlob_insertHandleAt(DKblob *BLOB,DKssize OFFSET,DKvalue SOURCE,DKu8 TYPE)
{
	DKu8 *source;
	DKusize length;
	DKusize offset;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getLength(BLOB->block),offset);
	error_bypassExit();
	blob_getHandle(BLOB,SOURCE,TYPE,source,length);
	buffer_insert(BLOB->block,DKu8,offset,source,length);
	safe_endExit(BLOB);
};

void dkBlob_write(DKblob *BLOB,DKu8 *SOURCE,DKusize LENGTH)
{
	safe_start(BLOB);
	buffer_write(BLOB->block,DKu8,BLOB->offset,SOURCE,LENGTH);
	BLOB->offset += LENGTH;
	safe_endExit(BLOB);
};

void dkBlob_writeAt(DKblob *BLOB,DKssize OFFSET,DKu8 *SOURCE,DKusize LENGTH)
{
	DKusize offset;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getLength(BLOB->block),offset);
	error_bypassExit();
	buffer_write(BLOB->block,DKu8,offset,SOURCE,LENGTH);
	safe_endExit(BLOB);
};

void dkBlob_writeHandle(DKblob *BLOB,DKvalue SOURCE,DKu8 TYPE)
{
	DKu8 *source;
	DKusize length;
	safe_start(BLOB);
	blob_getHandle(BLOB,SOURCE,TYPE,source,length);
	buffer_write(BLOB->block,DKu8,BLOB->offset,source,length);
	BLOB->offset += length;
	safe_endExit(BLOB);
};

void dkBlob_writeHandleAt(DKblob *BLOB,DKssize OFFSET,DKvalue SOURCE,DKu8 TYPE)
{
	DKusize offset;
	DKu8 *source;
	DKusize length;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getLength(BLOB->block),offset);
	error_bypassExit();
	blob_getHandle(BLOB,SOURCE,TYPE,source,length);
	buffer_write(BLOB->block,DKu8,offset,source,length);
	safe_endExit(BLOB);
};

DKu8 *dkBlob_read(DKblob *BLOB,DKusize LENGTH)
{
	DKu8 *source;
	safe_start(BLOB);
	blob_read(BLOB->block,BLOB->offset,LENGTH,source);
	BLOB->offset += LENGTH;
	safe_endReturnValue(BLOB,source);
};

DKu8 *dkBlob_readAt(DKblob *BLOB,DKssize OFFSET,DKusize LENGTH)
{
	DKu8 *source;
	DKusize offset;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getLength(BLOB->block),offset);
	error_bypassReturn();
	blob_read(BLOB->block,offset,LENGTH,source);
	safe_endReturnValue(BLOB,source);
};

DKvalue dkBlob_readHandle(DKblob *BLOB,DKu8 TYPE)
{
	DKvalue source;
	DKusize length;
	safe_start(BLOB);
	blob_readHandle(BLOB->block,BLOB->offset,TYPE,source,length);
	BLOB->offset += length;
	safe_endReturnCast(BLOB,source,DKvalue);
};

DKvalue dkBlob_readHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE)
{
	DKvalue source;
	DKusize length;
	DKusize offset;
	safe_start(BLOB);
	block_calculateUnsafePosition(OFFSET,block_getLength(BLOB->block),offset);
	error_bypassReturnCast(DKvalue);
	blob_readHandle(BLOB->block,offset,TYPE,source,length);
	safe_endReturnCast(BLOB,source,DKvalue);
};

void dkBlob_erase(DKblob *BLOB,DKusize LENGTH)
{
	safe_start(BLOB);
	buffer_erase(BLOB->block,DKu8,BLOB->offset,LENGTH);
	safe_endExit(BLOB);
};

void dkBlob_eraseAt(DKblob *BLOB,DKssize OFFSET,DKusize LENGTH)
{
	safe_start(BLOB);
	blob_erase(BLOB->block,OFFSET,LENGTH);
	safe_endExit(BLOB);
};

void dkBlob_eraseHandle(DKblob *BLOB,DKu8 TYPE)
{
	safe_start(BLOB);
	if (TYPE > DARK_BLOB_CHARACTER) error_throwExit("invalid TYPE");
	buffer_erase(BLOB->block,DKu8,BLOB->offset,blob_typeToLength[TYPE]);
	safe_endExit(BLOB);
};

void dkBlob_eraseHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE)
{
	safe_start(BLOB);
	if (TYPE > DARK_BLOB_CHARACTER) error_throwExit("invalid TYPE");
	blob_erase(BLOB->block,OFFSET,blob_typeToLength[TYPE]);
	safe_endExit(BLOB);
};

void dkBlob_remove(DKblob *BLOB,DKusize LENGTH)
{
	safe_start(BLOB);
	buffer_remove(BLOB->block,DKu8,BLOB->offset,LENGTH);
	safe_endExit(BLOB);
};

void dkBlob_removeAt(DKblob *BLOB,DKssize OFFSET,DKusize LENGTH)
{
	safe_start(BLOB);
	blob_remove(BLOB->block,OFFSET,LENGTH);
	safe_endExit(BLOB);
};

void dkBlob_removeHandle(DKblob *BLOB,DKu8 TYPE)
{
	safe_start(BLOB);
	if (TYPE > DARK_BLOB_CHARACTER) error_throwExit("invalid TYPE");
	buffer_remove(BLOB->block,DKu8,BLOB->offset,blob_typeToLength[TYPE]);
	safe_endExit(BLOB);
};

void dkBlob_removeHandleAt(DKblob *BLOB,DKssize OFFSET,DKu8 TYPE)
{
	safe_start(BLOB);
	if (TYPE > DARK_BLOB_CHARACTER) error_throwExit("invalid TYPE");
	blob_remove(BLOB->block,OFFSET,blob_typeToLength[TYPE]);
	safe_endExit(BLOB);
};
