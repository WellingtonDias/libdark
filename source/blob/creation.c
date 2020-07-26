DKblob *dkBlob_create(DKu8 ENDIAN)
{
	DKblob *blob;
	unsafe_start();
	struct_createFromNothing(DKblob,DKu8,blob);
	blob_calculateEndian(ENDIAN,blob->endian);
	blob->offset = 0;
	return blob;
};

DKblob *dkBlob_createFromMemory(DKu8 *SOURCE,DKusize LENGTH,DKssize START,DKssize END,DKu8 ENDIAN)
{
	DKblob *blob;
	unsafe_start();
	struct_createFromMemory(DKblob,DKu8,SOURCE,LENGTH,START,END,blob);
	blob_calculateEndian(ENDIAN,blob->endian);
	blob->offset = 0;
	return blob;
};

DKblob *dkBlob_createFromFile(DKnullString FILE_NAME,DKssize START,DKssize END,DKu8 ENDIAN)
{
	DKblob *blob;
	unsafe_start();
	struct_create(DKblob,blob);
	buffer_createFromFile(blob->block,DKu8,FILE_NAME,"rb",START,END);
	blob_calculateEndian(ENDIAN,blob->endian);
	blob->offset = 0;
	return blob;
};

DKblob *dkBlob_createFromCopy(DKblob *BLOB,DKssize START,DKssize END)
{
	DKblob *blob;
	safe_start(BLOB);
	struct_createFromMemory(DKblob,DKu8,block_getSource(BLOB->block),block_getLength(BLOB->block),START,END,blob);
	blob->endian = BLOB->endian;
	blob->offset = 0;
	safe_endReturnValue(BLOB,blob);
};

DKblob *dkBlob_destroy(DKblob *BLOB)
{
	safe_start(BLOB);
	struct_destroy(BLOB);
	return NULL;
};
