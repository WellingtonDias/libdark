DKnominal *dkNominal_create(DKusize HASH_SIZE)
{
	DKnominal *nominal;
	unsafe_start();
	// if ((HASH_SIZE < 1) || (HASH_SIZE > 256)) error_throwReturn("invalid HASH_SIZE");
	struct_create(DKnominal,nominal);
	if (!(nominal->block = malloc(HASH_SIZE * sizeof(DKblock_pair)))) error_throwReturn("MEMORY: malloc");
	for (DKusize hash = 0; hash < HASH_SIZE; ++hash) block_createFromNothing(nominal->block[hash],DKpair);
	nominal->hashSize = HASH_SIZE;
	nominal->length = 0;
	return nominal;
};

DKnominal *dkNominal_destroy(DKnominal *NOMINAL)
{
	safe_start(NOMINAL);
	for (DKusize hash = 0; hash < NOMINAL->hashSize; ++hash) block_destroy(NOMINAL->block[hash]);
	mutex_destroy(NOMINAL->mutex);
	free(NOMINAL);
	return NULL;
};

// DKnominal *_nominal_create(DARKdictionary *SOURCE,DKusize HASH_SIZE,DKusize SIZE)
// {
// 	DKnominal *nominal;
// 	if (!(nominal = malloc(sizeof(DKnominal)))) _error_throwReturn("MEMORY: malloc",NULL);
// 	nominal->hashSize = HASH_SIZE;
// 	nominal->length = SIZE;
// 	nominal->source = SOURCE;
// 	if (!(nominal->lock = malloc(sizeof(mtx_t)))) _error_throwReturn("MEMORY: malloc",NULL);
// 	if (mtx_init(nominal->lock,mtx_plain) == thrd_error) _error_throwReturn("MUTEX: init",NULL);
// 	return nominal;
// };

// DKnominal *dkNominal_createFromCopy(DKnominal *NOMINAL)
// {
// 	DKdictionary *source;
// 	if (!(source = malloc(NOMINAL->hashSize * sizeof(DKdictionary)))) _error_throwReturn("MEMORY: malloc",NULL);
// 	for (DKusize hash = 0; hash < NOMINAL->hashSize; ++hash)
// 	{
// 		source[hash].length = NOMINAL->source[hash].length;
// 		source[hash].capacity = NOMINAL->source[hash].capacity;
// 		if (!(source[hash].source = malloc(source[hash].capacity * sizeof(DKpair)))) _error_throwReturn("MEMORY: malloc",NULL);
// 		memcpy(source[hash].source,NOMINAL->source[hash].source,source[hash].length * sizeof(DKpair));
// 	};
// 	return _nominal_create(source,NOMINAL->hashSize,NOMINAL->length);
// };

// {
// 		source[hash].length = 0;
// 		source[hash].capacity = 1;
// 		if (!(source[hash].source = malloc(sizeof(DKpair)))) _error_throwReturn("MEMORY: malloc",NULL);
// };
// 	return _nominal_create(source,hashSize,0);
