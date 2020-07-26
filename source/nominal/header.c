typedef struct
{
	DKnullString key;
	DKvalue value;
} DKpair;

block_define(DKblock_pair,DKpair);

struct _nominal
{
	DKusize hashSize;
	DKusize length;
	DKblock_pair *block;
	DKmutex mutex;
};

void dkNominal_debug(DKnominal *NOMINAL,DKnullString LABEL)
{
	safe_start(NOMINAL);
	printf("NOMINAL { hashSize: %lli, length: %lli, source: { ",(DKusize) NOMINAL->hashSize,NOMINAL->length);
	if (NOMINAL->length > 0)
	{
		for (DKusize hash = 0; hash < NOMINAL->hashSize; ++hash)
		{
			for (DKusize index = 0; index < block_getLength(NOMINAL->block[hash]); ++index) printf("%s=%lli ",block_getSource(NOMINAL->block[hash])[index].key,block_getSource(NOMINAL->block[hash])[index].value.usize);
		};
	};
	printf("} } #%s\n",LABEL);
	safe_endExit(NOMINAL);
};
