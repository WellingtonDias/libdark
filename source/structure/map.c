typedef struct
{
	Undefined key;
	Undefined value;
} MapPair;

typedef struct
{
	MapPair*     pointer;
	UnsignedSize length;
	UnsignedSize capacity;
} MapData;

struct _Map
{
	HashFunction    hashFunction;
	CompareFunction compareFunction;
	UnsignedSize    length;
	UnsignedSize    hashSize;
	MapData*        data;
	Mutex           mutex;
	Exception       exception;
};

#routine key_hash(MAP,KEY,RETURN)
{
	if (!MAP->hashFunction) RETURN = KEY.unsignedSize % MAP->hashSize;
	else RETURN = (*MAP->hashFunction)(KEY,MAP->hashSize);
};

#routine key_search(MAP,KEY,RETURN1,RETURN2,RETURN3)
{
	key_hash(MAP,KEY,RETURN1);
	for (RETURN2 = 0; RETURN2 < MAP->data[RETURN1].length; ++RETURN2)
	{
		if (!MAP->compareFunction)
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

#routine mapData_adjustCapacity(EXCEPTION,DATA,LENGTH)
{
	#local UnsignedSize capacity;
	capacity = 1;
	while (capacity < LENGTH) capacity *= 2;
	if (capacity != DATA.capacity)
	{
		#local MapPair* pointer;
		if (!(pointer = realloc(DATA.pointer,capacity * sizeof(MapPair)))) exception_routineThrow(EXCEPTION,"MEMORY: realloc");
		DATA.pointer = pointer;
		DATA.capacity = capacity;
	};
};

#routine map_insert(MAP,HASH,KEY,VALUE)
{
	mapData_adjustCapacity(MAP->exception,MAP->data[HASH],MAP->data[HASH].length + 1);
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
	if (!(map = calloc(1,sizeof(Map)))) exception_globalThrowReturn("MEMORY: calloc");
	map->hashFunction = HASH_FUNCTION;
	map->compareFunction = COMPARE_FUNCTION;
	map->length = 0;
	map->hashSize = HASH_SIZE;
	if (!(map->data = malloc(HASH_SIZE * sizeof(MapData)))) exception_globalThrowReturn("MEMORY: malloc");
	for (UnsignedSize hash = 0; hash < HASH_SIZE; ++hash)
	{
		if (!(map->data[hash].pointer = malloc(sizeof(MapPair)))) exception_globalThrowReturn("MEMORY: malloc");
		map->data[hash].length = 0;
		map->data[hash].capacity = 1;
	};
	return map;
};

Map *Map_clone(Map *MAP)
{
	Map *map;
	if (!(map = calloc(1,sizeof(Map)))) exception_globalThrowReturn("MEMORY: calloc");
	map->hashFunction = MAP->hashFunction;
	map->compareFunction = MAP->compareFunction;
	map->length = MAP->length;
	map->hashSize = MAP->hashSize;
	if (!(map->data = malloc(MAP->hashSize * sizeof(MapData)))) exception_globalThrowReturn("MEMORY: malloc");
	for (UnsignedSize hash = 0; hash < MAP->hashSize; ++hash)
	{
		if (!(map->data[hash].pointer = malloc(MAP->data[hash].length * sizeof(MapPair)))) exception_globalThrowReturn("MEMORY: malloc");
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
	MAP->length = 0;
	for (UnsignedSize hash = 0; hash < MAP->hashSize; ++hash)
	{
		free(MAP->data[hash].pointer);
		MAP->data[hash].pointer = NULL;
		MAP->data[hash].length = 0;
		MAP->data[hash].capacity = 0;
	}
	MAP->hashSize = 0;
	free(MAP->data);
	MAP->data = NULL;
	mutex_destroy(MAP);
	exception_destroy(MAP);
	free(MAP);
	return NULL;
};

void Map_merge(Map *TARGET,Map *SOURCE)
{
	mutex_lock(TARGET);
	mutex_lock(SOURCE);
	if (SOURCE->length > 0)
	{
		Boolean found;
		UnsignedSize hash2,index2;
		for (UnsignedSize hash = 0; hash < SOURCE->hashSize; ++hash)
		{
			for (UnsignedSize index = 0; index < SOURCE->data[hash].length; ++index)
			{
				key_search(TARGET,SOURCE->data[hash].pointer[index].key,hash2,index2,found);
				if (found) TARGET->data[hash2].pointer[index2].value = SOURCE->data[hash].pointer[index].value;
				else {map_insert(TARGET,hash2,SOURCE->data[hash].pointer[index].key,SOURCE->data[hash].pointer[index].value)};
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
		for (UnsignedSize hash = 0; hash < MAP->hashSize; ++hash)
		{
			if (MAP->data[hash].length > 0)
			{
				MapPair *pointer;
				if (!(pointer = realloc(MAP->data[hash].pointer,sizeof(MapPair)))) exception_structThrowExit(MAP,"MEMORY: realloc");
				MAP->data[hash].pointer = pointer;
				MAP->data[hash].length = 0;
				MAP->data[hash].capacity = 1;
			};
		};
		MAP->length = 0;
	};
	mutex_unlock(MAP);
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
		for (UnsignedSize hash = 0; hash < MAP1->hashSize; ++hash)
		{
			for (UnsignedSize index = 0; index < MAP1->data[hash].length; ++index)
			{
				key_search(MAP2,MAP1->data[hash].pointer[index].key,hash2,index2,found);
				if (!MAP1->compareFunction) comparison = found && (MAP1->data[hash].pointer[index].value.unsignedSize == MAP2->data[hash2].pointer[index2].value.unsignedSize);
				else comparison = found && ((*MAP1->compareFunction)(MAP1->data[hash].pointer[index].value,MAP2->data[hash2].pointer[index2].value));
				if (!comparison) break;
			};
		};
	};
	mutex_unlock(MAP2);
	mutex_unlock(MAP1);
	return comparison;
};

void Map_insert(Map *MAP,Undefined KEY,Undefined VALUE)
{
	Boolean found;
	UnsignedSize hash,index;
	mutex_lock(MAP);
	key_search(MAP,KEY,hash,index,found);
	if (found) exception_structThrowExit(MAP,"invalid KEY");
	map_insert(MAP,hash,KEY,VALUE);
	mutex_unlock(MAP);
};

#routine map_replace(MAP,HASH,INDEX,VALUE,RETURN)
{
	RETURN = MAP->data[HASH].pointer[INDEX].value;
	MAP->data[HASH].pointer[INDEX].value = VALUE;
};

Undefined Map_replace(Map *MAP,Undefined KEY,Undefined VALUE)
{
	Undefined value;
	Boolean found;
	UnsignedSize hash,index;
	mutex_lock(MAP);
	key_search(MAP,KEY,hash,index,found);
	if (!found) exception_structThrowReturnCast(MAP,"invalid KEY",Undefined);
	map_replace(MAP,hash,index,VALUE,value);
	mutex_unlock(MAP);
	return value;
};

Undefined Map_set(Map *MAP,Undefined KEY,Undefined VALUE)
{
	Undefined value = (Undefined) 0;
	Boolean found;
	UnsignedSize hash,index;
	mutex_lock(MAP);
	key_search(MAP,KEY,hash,index,found);
	if (found) {map_replace(MAP,hash,index,VALUE,value)}
	else {map_insert(MAP,hash,KEY,VALUE)};
	mutex_unlock(MAP);
	return value;
};

Boolean Map_searchKey(Map *MAP,Undefined KEY)
{
	Boolean found;
	UnsignedSize hash;
	UnsignedSize index ;
	mutex_lock(MAP);
	key_search(MAP,KEY,hash,index,found);
	mutex_unlock(MAP);
	return found;
};

Boolean Map_searchValue(Map *MAP,Undefined VALUE)
{
	UnsignedSize hash = 0;
	mutex_lock(MAP);
	for (; hash < MAP->hashSize; ++hash)
	{
		for (UnsignedSize index = 0; index < MAP->data[hash].length; ++index)
		{
			if (!MAP->compareFunction)
			{
				if (VALUE.unsignedSize == MAP->data[hash].pointer[index].value.unsignedSize) goto found;
			}
			else
			{
				if ((*MAP->compareFunction)(VALUE,MAP->data[hash].pointer[index].value)) goto found;
			};
		};
	};
	found: ;
	Boolean found = hash < MAP->hashSize;
	mutex_unlock(MAP);
	return found;
};

Undefined Map_getKey(Map *MAP,Undefined VALUE)
{
	UnsignedSize hash = 0;
	UnsignedSize index = 0;
	mutex_lock(MAP);
	if (MAP->length == 0) exception_structThrowReturnCast(MAP,"MAP: empty",Undefined);
	for (; hash < MAP->hashSize; ++hash)
	{
		for (index = 0; index < MAP->data[hash].length; ++index)
		{
			if (!MAP->compareFunction)
			{
				if (VALUE.unsignedSize == MAP->data[hash].pointer[index].value.unsignedSize) goto found;
			}
			else
			{
				if ((*MAP->compareFunction)(VALUE,MAP->data[hash].pointer[index].value)) goto found;
			};
		};
	};
	found: ;
	if (hash == MAP->hashSize) exception_structThrowReturnCast(MAP,"invalid VALUE",Undefined);
	Undefined key = MAP->data[hash].pointer[index].key;
	mutex_unlock(MAP);
	return key;
};

Undefined Map_getValue(Map *MAP,Undefined KEY)
{
	Boolean found;
	UnsignedSize hash,index;
	mutex_lock(MAP);
	key_search(MAP,KEY,hash,index,found);
	if (!found) exception_structThrowReturnCast(MAP,"invalid KEY",Undefined);
	Undefined value = MAP->data[hash].pointer[index].value;
	mutex_unlock(MAP);
	return value;
};

Undefined Map_remove(Map *MAP,Undefined KEY)
{
	Boolean found;
	UnsignedSize hash,index;
	mutex_lock(MAP);
	key_search(MAP,KEY,hash,index,found);
	if (!found) exception_structThrowReturnCast(MAP,"invalid KEY",Undefined);
	--MAP->data[hash].length;
	Undefined value = MAP->data[hash].pointer[index].value;
	if (index < MAP->data[hash].length) memcpy(MAP->data[hash].pointer + index,MAP->data[hash].pointer + index + 1,(MAP->data[hash].length - index) * sizeof(MapPair));
	mapData_adjustCapacity(MAP->exception,MAP->data[hash],MAP->data[hash].length);
	exception_structBypassReturnCast(MAP,Undefined);
	--MAP->length;
	mutex_unlock(MAP);
	return value;
};

void Map_swap(Map *MAP,Undefined KEY1,Undefined KEY2)
{
	Boolean found1,found2;
	UnsignedSize hash,hash2;
	UnsignedSize index = 0;
	UnsignedSize index2 = 0;
	mutex_lock(MAP);
	key_search(MAP,KEY1,hash,index,found1);
	key_search(MAP,KEY2,hash2,index2,found2);
	if (!found1 || !found2) exception_structBypassExit(MAP);
	Undefined value = MAP->data[hash].pointer[index].value;
	MAP->data[hash].pointer[index].value = MAP->data[hash2].pointer[index2].value;
	MAP->data[hash2].pointer[index2].value = value;
	mutex_unlock(MAP);
// };

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

void Map_setHashSize(Map *MAP,UnsignedSize HASH_SIZE)
{
	UnsignedSize hash1 = 0;
	UnsignedSize hash2;
	mutex_lock(MAP);
	if ((HASH_SIZE == 0) || (HASH_SIZE == MAP->hashSize)) exception_structThrowExit(MAP,"invalid HASH_SIZE");
	MapData *data = MAP->data;
	MAP->length = 0;
	if (!(MAP->data = malloc(HASH_SIZE * sizeof(MapData)))) exception_structThrowExit(MAP,"MEMORY: malloc");
	for (; hash1 < HASH_SIZE; ++hash1)
	{
		if (!(MAP->data[hash1].pointer = malloc(sizeof(MapPair)))) exception_structThrowExit(MAP,"MEMORY: malloc");
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
	printf("MAP { length: %lli, hashSize: %lli, { ",MAP->length,MAP->hashSize);
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
