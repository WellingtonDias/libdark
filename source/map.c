#routine map_adjustCapacity(EXCEPTION,DATA,LENGTH)
{
	data_adjustCapacity(EXCEPTION,DATA,LENGTH,MapPair);
};

#routine key_hash(MAP,KEY,RETURN)
{
	if (MAP->hashFunction == NULL) RETURN = KEY.unsignedSize % MAP->hashSize;
	else RETURN = (*MAP->hashFunction)(KEY,MAP->hashSize);
};

#routine key_search(MAP,KEY,RETURN1,RETURN2,RETURN3)
{
	key_hash(MAP,KEY,RETURN1);
	for (RETURN2 = 0; RETURN2 < MAP->data[RETURN1].length; ++RETURN2)
	{
		if (MAP->compareFunction == NULL)
		{
			if (KEY.unsignedSize == MAP->data[RETURN1].pointer[RETURN2].key.unsignedSize) break;
		}
		else
		{
			if ((*MAP->compareFunction)(KEY,MAP->data[RETURN1].pointer[RETURN2].key)) break;
		};
	};
	RETURN3 = RETURN2 < MAP->data[RETURN1].length;
};

#routine map_insert(MAP,HASH,KEY,VALUE)
{
	map_adjustCapacity(MAP->exception,MAP->data[HASH],MAP->data[HASH].length + 1);
	exception_routineBypass(MAP->exception);
	MAP->data[HASH].pointer[MAP->data[HASH].length].key = KEY;
	MAP->data[HASH].pointer[MAP->data[HASH].length].value = VALUE;
	++MAP->data[HASH].length;
	++MAP->length;
};

Map *Map_create(UnsignedSize HASH_SIZE,HashFunction HASH_FUNCTION,CompareFunction COMPARE_FUNCTION)
{
	Map *map;
	if (HASH_SIZE == 0) exception_globalThrowReturn("invalid HASH_SIZE");
	if ((map = calloc(1,sizeof(Map))) == NULL) exception_globalThrowReturn("MEMORY: calloc");
	map->hashFunction = HASH_FUNCTION;
	map->compareFunction = COMPARE_FUNCTION;
	map->hashSize = HASH_SIZE;
	if ((map->data = malloc(HASH_SIZE * sizeof(MapData))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	for (UnsignedSize hash = 0; hash < HASH_SIZE; ++hash)
	{
		if ((map->data[hash].pointer = malloc(sizeof(MapPair))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
		map->data[hash].length = 0;
		map->data[hash].capacity = 1;
	};
	return map;
};

Map *Map_clone(Map *MAP)
{
	Map *map;
	if ((map = calloc(1,sizeof(Map))) == NULL) exception_globalThrowReturn("MEMORY: calloc");
	map->hashFunction = MAP->hashFunction;
	map->compareFunction = MAP->compareFunction;
	map->hashSize = MAP->hashSize;
	map->length = MAP->length;
	if ((map->data = malloc(MAP->hashSize * sizeof(MapData))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	for (UnsignedSize hash = 0; hash < MAP->hashSize; ++hash)
	{
		if ((map->data[hash].pointer = malloc(MAP->data[hash].length * sizeof(MapPair))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
		memcpy(map->data[hash].pointer,MAP->data[hash].pointer,MAP->data[hash].length * sizeof(MapPair));
		map->data[hash].length = MAP->data[hash].length;
		map->data[hash].capacity = MAP->data[hash].capacity;
	};
	return map;
};

Map *Map_destroy(Map *MAP)
{
	mutex_lock(MAP);
	MAP->hashFunction = NULL;
	MAP->compareFunction = NULL;
	for (UnsignedSize hash = 0; hash < MAP->hashSize; ++hash)
	{
		free(MAP->data[hash].pointer);
		MAP->data[hash].pointer = NULL;
		MAP->data[hash].length = 0;
		MAP->data[hash].capacity = 0;
	}
	MAP->hashSize = 0;
	MAP->length = 0;
	free(MAP->data);
	MAP->data = NULL;
	mutex_destroy(MAP);
	exception_destroy(MAP);
	free(MAP);
	return NULL;
};

Boolean Map_compare(Map *MAP1,Map *MAP2)
{
	Boolean comparison = false;
	mutex_lock(MAP1);
	mutex_lock(MAP2);
	if (MAP1->length == MAP2->length)
	{
		Boolean found;
		UnsignedSize hash2,index2;
		for (UnsignedSize hash1 = 0; hash1 < MAP1->hashSize; ++hash1)
		{
			for (UnsignedSize index1 = 0; index1 < MAP1->data[hash1].length; ++index1)
			{
				key_search(MAP2,MAP1->data[hash1].pointer[index1].key,hash2,index2,found);
				if (MAP1->compareFunction == NULL) comparison = found && (MAP1->data[hash1].pointer[index1].value.unsignedSize == MAP2->data[hash2].pointer[index2].value.unsignedSize);
				else comparison = found && ((*MAP1->compareFunction)(MAP1->data[hash1].pointer[index1].value,MAP2->data[hash2].pointer[index2].value));
				if (!comparison) break;
			};
		};
	};
	mutex_unlock(MAP2);
	mutex_unlock(MAP1);
	return comparison;
};

void Map_merge(Map *TARGET,Map *SOURCE)
{
	mutex_lock(TARGET);
	mutex_lock(SOURCE);
	if (SOURCE->length > 0)
	{
		Boolean found;
		UnsignedSize hash2,index2;
		for (UnsignedSize hash1 = 0; hash1 < SOURCE->hashSize; ++hash1)
		{
			for (UnsignedSize index1 = 0; index1 < SOURCE->data[hash1].length; ++index1)
			{
				key_search(TARGET,SOURCE->data[hash1].pointer[index1].key,hash2,index2,found);
				if (found) TARGET->data[hash2].pointer[index2].value = SOURCE->data[hash1].pointer[index1].value;
				else map_insert(TARGET,hash2,SOURCE->data[hash1].pointer[index1].key,SOURCE->data[hash1].pointer[index1].value);
			};
		};
	};
	mutex_unlock(SOURCE);
	mutex_unlock(TARGET);
};

void Map_clear(Map *MAP)
{
	mutex_lock(MAP);
	if (MAP->length > 0)
	{
		for (UnsignedSize hash = 0; hash < MAP->hashSize; ++hash) data_clear(MAP->exception,MAP->data[hash],MapPair);
		MAP->length = 0;
	};
	mutex_unlock(MAP);
};

void Map_setHashFunction(Map *MAP,HashFunction HASH_FUNCTION)
{
	mutex_lock(MAP);
	MAP->hashFunction = HASH_FUNCTION;
	mutex_unlock(MAP);
};

HashFunction Map_getHashFunction(Map *MAP)
{
	mutex_lock(MAP);
	HashFunction hashFunction = MAP->hashFunction;
	mutex_unlock(MAP);
	return hashFunction;
};

void Map_setCompareFunction(Map *MAP,CompareFunction COMPARE_FUNCTION)
{
	mutex_lock(MAP);
	MAP->compareFunction = COMPARE_FUNCTION;
	mutex_unlock(MAP);
};

CompareFunction Map_getCompareFunction(Map *MAP)
{
	mutex_lock(MAP);
	CompareFunction compareFunction = MAP->compareFunction;
	mutex_unlock(MAP);
	return compareFunction;
};

void Map_setHashSize(Map *MAP,UnsignedSize HASH_SIZE)
{
	UnsignedSize hash1 = 0;
	UnsignedSize hash2;
	mutex_lock(MAP);
	if ((HASH_SIZE == 0) || (HASH_SIZE == MAP->hashSize)) exception_structThrowExit(MAP,"invalid HASH_SIZE");
	MapData *data = MAP->data;
	MAP->length = 0;
	if ((MAP->data = malloc(HASH_SIZE * sizeof(MapData))) == NULL) exception_structThrowExit(MAP,"MEMORY: malloc");
	for (; hash1 < HASH_SIZE; ++hash1)
	{
		if ((MAP->data[hash1].pointer = malloc(sizeof(MapPair))) == NULL) exception_structThrowExit(MAP,"MEMORY: malloc");
		MAP->data[hash1].length = 0;
		MAP->data[hash1].capacity = 1;
	};
	for (hash1 = 0; hash1 < MAP->hashSize; ++hash1)
	{
		for (UnsignedSize index = 0; index < data[hash1].length; ++index)
		{
			key_hash(MAP,data[hash1].pointer[index].key,hash2);
			map_insert(MAP,hash2,data[hash1].pointer[index].key,data[hash1].pointer[index].value);
		};
		free(data[hash1].pointer);
		data[hash1].pointer = NULL;
		data[hash1].length = 0;
		data[hash1].capacity = 0;
	};
	free(data);
	MAP->hashSize = HASH_SIZE;
	mutex_unlock(MAP);
};

UnsignedSize Map_getHashSize(Map *MAP)
{
	mutex_lock(MAP);
	UnsignedSize hashSize = MAP->hashSize;
	mutex_unlock(MAP);
	return hashSize;
};

UnsignedSize Map_getLength(Map *MAP)
{
	mutex_lock(MAP);
	UnsignedSize length = MAP->length;
	mutex_unlock(MAP);
	return length;
};

Boolean Map_isEmpty(Map *MAP)
{
	mutex_lock(MAP);
	Boolean empty = MAP->length == 0;
	mutex_unlock(MAP);
	return empty;
};

Boolean Map_isNotEmpty(Map *MAP)
{
	mutex_lock(MAP);
	Boolean empty = MAP->length != 0;
	mutex_unlock(MAP);
	return empty;
};

void Map_setMutex(Map *MAP,Boolean LOCK)
{
	mutex_lock(MAP);
	mutex_setLock(MAP,LOCK);
	mutex_unlock(MAP);
};

Boolean Map_getMutex(Map *MAP)
{
	Boolean lock;
	mutex_lock(MAP);
	mutex_getLock(MAP,lock);
	mutex_unlock(MAP);
	return lock;
};

NullString Map_getException(Map *MAP)
{
	NullString message;
	mutex_lock(MAP);
	exception_getMessage(MAP,message);
	mutex_unlock(MAP);
	return message;
};

void Map_debug(Map *MAP,NullString MESSAGE)
{
	mutex_lock(MAP);
	printf("MAP: { hashSize: %lli, length: %lli, { ",MAP->hashSize,MAP->length);
	if (MAP->length > 0)
	{
		for (UnsignedSize hash = 0; hash < MAP->hashSize; ++hash)
		{
			for (UnsignedSize index = 0; index < MAP->data[hash].length; ++index) printf("%lli=%lli ",MAP->data[hash].pointer[index].key.unsignedSize,MAP->data[hash].pointer[index].value.unsignedSize);
		};
	};
	printf("} } #%s\n",MESSAGE);
	mutex_unlock(MAP);
};
