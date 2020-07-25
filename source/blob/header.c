block_define(DKblock_u8,DKu8);

struct _blob
{
	DKu8 endian;
	DKusize offset;
	DKblock_u8 block;
	DKmutex mutex;
};

DKu8 BlobSize[28] = {1,1,1,2,2,2,2,2,2,4,4,4,4,4,4,8,8,8,8,8,8,4,4,4,8,8,8,1};
DKnullString BlobNominalEndian[3] = {"UNDEFINED","LITTLE","BIG"};
DKboolean BlobUndefinedEndian[28] = {true,true,true,true,true,false,true,true,false,true,true,false,true,true,false,true,true,false,true,true,false,true,true,false,true,true,false,true};
DKboolean BlobDefinedEndian[28] = {true,true,true,false,false,true,false,false,true,false,false,true,false,false,true,false,false,true,false,false,true,false,false,true,false,false,true,true};

#macro blob_calculateEndian(INPUT_ENDIAN,OUTPUT_ENDIAN)
{
	switch (INPUT_ENDIAN)
	{
		case DARK_BLOB_UNDEFINED_ENDIAN:
		case DARK_BLOB_LITTLE_ENDIAN:
		case DARK_BLOB_BIG_ENDIAN: OUTPUT_ENDIAN = INPUT_ENDIAN; break;
		case DARK_BLOB_SYSTEM_ENDIAN: OUTPUT_ENDIAN = DARK_ENDIAN; break;
		default: error_set("invalid ENDIAN");
	};
};

void dkBlob_debug(DKblob *BLOB,DKnullString LABEL)
{
	safe_start(BLOB);
	printf("BLOB { endian: %s,offset: %lli,size: %lli,capacity: %lli,source: ",BlobNominalEndian[BLOB->endian],BLOB->offset,(BLOB->block).size,(BLOB->block).capacity);
	for (DKusize i = 0; i < (BLOB->block).size; ++i) printf("%lli ",(DKusize) (BLOB->block).start[i]);
	printf("} #%s\n",LABEL);
	safe_end(BLOB);
};
