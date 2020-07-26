DKu8 dkBlob_setEndian(DKblob *BLOB,DKu8 ENDIAN)
{
	safe_start(BLOB);
	DKu8 endian = BLOB->endian;
	blob_calculateEndian(ENDIAN,BLOB->endian);
	safe_endReturnValue(BLOB,endian);
};

DKu8 dkBlob_getEndian(DKblob *BLOB)
{
	safe_start(BLOB);
	DKu8 endian = BLOB->endian;
	safe_endReturnValue(BLOB,endian);
};

DKusize dkBlob_setOffset(DKblob *BLOB,DKusize OFFSET)
{
	safe_start(BLOB);
	DKusize offset = BLOB->offset;
	BLOB->offset = OFFSET;
	safe_endReturnValue(BLOB,offset);
};

DKusize dkBlob_resetOffset(DKblob *BLOB)
{
	safe_start(BLOB);
	DKusize offset = BLOB->offset;
	BLOB->offset = 0;
	safe_endReturnValue(BLOB,offset);
};

DKusize dkBlob_getOffset(DKblob *BLOB)
{
	safe_start(BLOB);
	DKusize offset = BLOB->offset;
	safe_endReturnValue(BLOB,offset);
};

DKu8 *dkBlob_getSource(DKblob *BLOB)
{
	safe_start(BLOB);
	DKu8 *source = block_getSource(BLOB->block);
	safe_endReturnValue(BLOB,source);
};

DKusize dkBlob_setLength(DKblob *BLOB,DKusize LENGTH)
{
	DKusize length;
	safe_start(BLOB);
	block_setLength(BLOB->block,DKu8,LENGTH,length);
	safe_endReturnValue(BLOB,length);
};

DKusize dkBlob_getLength(DKblob *BLOB)
{
	safe_start(BLOB);
	DKusize length = block_getLength(BLOB->block);
	safe_endReturnValue(BLOB,length);
};

DKboolean dkBlob_isEmpty(DKblob *BLOB)
{
	safe_start(BLOB);
	DKboolean empty = block_isEmpty(BLOB->block);
	safe_endReturnValue(BLOB,empty);
};

DKboolean dkBlob_isNotEmpty(DKblob *BLOB)
{
	safe_start(BLOB);
	DKboolean empty = block_isNotEmpty(BLOB->block);
	safe_endReturnValue(BLOB,empty);
};

DKboolean dkBlob_setLock(DKblob *BLOB,DKboolean LOCK)
{
	safe_start(BLOB);
	mutex_setLock(BLOB->mutex,LOCK);
	safe_endReturnValue(BLOB,!LOCK);
};

DKboolean dkBlob_getLock(DKblob *BLOB)
{
	safe_start(BLOB);
	DKboolean lock = mutex_getLock(BLOB->mutex);
	safe_endReturnValue(BLOB,lock);
};
