void dkBlob_saveToFile(DKblob *BLOB,DKssize START,DKssize END,DKnullString FILE_NAME)
{
	safe_start(BLOB);
	buffer_saveToFile(BLOB->block,START,END,FILE_NAME,"wb");
	safe_endExit(BLOB);
};

void dkBlob_merge(DKblob *BLOB,DKssize OFFSET,DKblob *SOURCE,DKssize START,DKssize END)
{
	safe_start(BLOB);
	mutex_lock(SOURCE->mutex);
	block_merge(BLOB->block,DKu8,OFFSET,SOURCE->block,START,END)
	mutex_unlock(SOURCE->mutex);
	safe_endExit(BLOB);
};

void dkBlob_clear(DKblob *BLOB)
{
	safe_start(BLOB);
	block_clear(BLOB->block,DKu8);
	safe_endExit(BLOB);
};

DKboolean dkBlob_compare(DKblob *BLOB1,DKblob *BLOB2)
{
	safe_start(BLOB1);
	mutex_lock(BLOB2->mutex);
	DKboolean comparison = block_compare(BLOB1->block,BLOB2->block,DKu8);
	mutex_unlock(BLOB2->mutex);
	safe_endReturnValue(BLOB1,comparison);
};
