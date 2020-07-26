block_define(DKblock_u8,DKu8);

struct _blob
{
	DKu8 endian;
	DKusize offset;
	DKblock_u8 block;
	DKmutex mutex;
};

DKu8 blob_typeToLength[28] = {1,1,1,2,2,2,2,2,2,4,4,4,4,4,4,8,8,8,8,8,8,4,4,4,8,8,8,1};
DKnullString blob_endianToString[3] = {"UNDEFINED","LITTLE","BIG"};

#macro blob_calculateEndian(INPUT_ENDIAN,OUTPUT_ENDIAN)
{
	switch (INPUT_ENDIAN)
	{
		case DARK_BLOB_UNDEFINED_ENDIAN:
		case DARK_BLOB_LITTLE_ENDIAN:
		case DARK_BLOB_BIG_ENDIAN: OUTPUT_ENDIAN = INPUT_ENDIAN; break;
		case DARK_BLOB_SYSTEM_ENDIAN: OUTPUT_ENDIAN = DARK_SYSTEM_ENDIAN; break;
		default: error_throwReturn("invalid ENDIAN");
	};
};

void dkBlob_debug(DKblob *BLOB,DKnullString LABEL)
{
	safe_start(BLOB);
	printf("BLOB { endian: %s, offset: %lli, length: %lli, source: ",blob_endianToString[BLOB->endian],BLOB->offset,block_getLength(BLOB->block));
	for (DKusize i = 0; i < block_getLength(BLOB->block); ++i) printf("%lli ",(DKusize) block_getSource(BLOB->block)[i]);
	printf("} #%s\n",LABEL);
	safe_endExit(BLOB);
};
