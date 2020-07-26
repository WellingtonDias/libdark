#macro key_hash(KEY,LENGTH,SIZE,HASH)
{
	#local DKusize i;
	#local DKusize sum;
	for (i = 0; (i < LENGTH) && (i < 8); ++i) sum += KEY[i];
	HASH = sum % SIZE;
};

#macro pair_insert(STREAM,KEY,LENGTH,VALUE)
{
	DKpair pair;
	DKnullString key;
	if (!(key = malloc(LENGTH + 1))) error_throwExit("MEMORY: malloc");
	memcpy(key,KEY,LENGTH);
	pair.key = key;
	pair.value = VALUE;
	stream_append(STREAM,DKpair,pair);
};

#macro nominal_search(NOMINAL,KEY,LENGTH,HASH,INDEX,FOUND)
{
	#local DKusize index;
	key_hash(KEY,LENGTH,NOMINAL->hashSize,HASH);
	for (index = 0; index < block_getLength(NOMINAL->block[HASH]); ++index)
	{
		if (strcmp(KEY,block_getSource(NOMINAL->block[HASH])[index].key) == 0) break;
	};
	if (index < block_getLength(NOMINAL->block[HASH]))
	{
		INDEX = index;
		FOUND = true;
	}
	else FOUND = false;
};

void dkNominal_insert(DKnominal *NOMINAL,DKnullString KEY,DKvalue VALUE)
{
	DKboolean found;
	DKusize hash,index;
	DKusize length = strlen(KEY);
	nominal_search(NOMINAL,KEY,length,hash,index,found);
	if (found) error_throwExit("invalid KEY");
	pair_insert(NOMINAL->block[hash],KEY,length,VALUE);
	++NOMINAL->length;
};
