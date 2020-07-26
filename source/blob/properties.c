DKu8 dkBlob_setEndian(DKblob *BLOB,DKu8 ENDIAN)
{
	safe_start(BLOB);
	DKu8 endian = BLOB->endian;
	blob_calculateEndian(ENDIAN,BLOB->endian);
	safe_endReturn(BLOB,endian);
};

DKu8 dkBlob_getEndian(DKblob *BLOB)
{
	safe_start(BLOB);
	DKu8 endian = BLOB->endian;
	safe_endReturn(BLOB,endian);
};

DKusize dkBlob_setOffset(DKblob *BLOB,DKusize OFFSET)
{
	safe_start(BLOB);
	DKusize offset = BLOB->offset;
	BLOB->offset = OFFSET;
	safe_endReturn(BLOB,offset);
};

DKusize dkBlob_resetOffset(DKblob *BLOB)
{
	safe_start(BLOB);
	DKusize offset = BLOB->offset;
	BLOB->offset = 0;
	safe_endReturn(BLOB,offset);
};

DKusize dkBlob_getOffset(DKblob *BLOB)
{
	safe_start(BLOB);
	DKusize offset = BLOB->offset;
	safe_endReturn(BLOB,offset);
};

DKu8 *dkBlob_getSource(DKblob *BLOB)
{
	safe_start(BLOB);
	DKu8 *source = block_getSource(BLOB->block);
	safe_endReturn(BLOB,source);
};

DKusize dkBlob_setSize(DKblob *BLOB,DKusize SIZE)
{
	DKusize size;
	safe_start(BLOB);
	block_setSize(BLOB->block,DKu8,SIZE,size);
	safe_endReturn(BLOB,size);
};

DKusize dkBlob_getSize(DKblob *BLOB)
{
	safe_start(BLOB);
	DKusize size = block_getSize(BLOB->block);
	safe_endReturn(BLOB,size);
};

DKboolean dkBlob_isEmpty(DKblob *BLOB)
{
	safe_start(BLOB);
	DKboolean empty = block_isEmpty(BLOB->block);
	safe_endReturn(BLOB,empty);
};

DKboolean dkBlob_isNotEmpty(DKblob *BLOB)
{
	safe_start(BLOB);
	DKboolean empty = block_isNotEmpty(BLOB->block);
	safe_endReturn(BLOB,empty);
};

DKboolean dkBlob_setLock(DKblob *BLOB,DKboolean LOCK)
{
	safe_start(BLOB);
	mutex_setLock(BLOB->mutex,LOCK);
	safe_endReturn(BLOB,!LOCK);
};

DKboolean dkBlob_getLock(DKblob *BLOB)
{
	safe_start(BLOB);
	DKboolean lock = mutex_getLock(BLOB->mutex);
	safe_endReturn(BLOB,lock);
};
