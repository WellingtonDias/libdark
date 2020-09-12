typedef struct
{
	Undefined key;
	Undefined value;
} Pair;

block_define(Block_pair,Pair);

struct _Map
{
	UnsignedSize    hashSize;
	MapHashFunction hashFunction;
	MapDiffFunction diffFunction;
	UnsignedSize    length;
	Block_pair*     block;
	Mutex           mutex;
	Exception       exception;
};

#routine key_hash(MAP,KEY,HASH_SIZE,RETURN)
{
	if (!MAP->hashFunction) RETURN = KEY.unsignedSize % HASH_SIZE;
	else RETURN = (*MAP->hashFunction)(KEY,HASH_SIZE);
};

#routine key_diff(MAP,KEY,RETURN1,RETURN2,RETURN3)
{
	key_hash(MAP,KEY,MAP->hashSize,RETURN1);
	for (RETURN2 = 0; RETURN2 < block_getLength(MAP->block[RETURN1]); ++RETURN2)
	{
		if (!MAP->diffFunction)
		{
			if (KEY.unsignedSize == block_getStart(MAP->block[RETURN1])[RETURN2].key.unsignedSize) break;
		}
		else
		{
			if ((*MAP->diffFunction)(KEY,block_getStart(MAP->block[RETURN1])[RETURN2].key)) break;
		};
	};
	RETURN3 = RETURN2 < block_getLength(MAP->block[RETURN1]);
};

#routine pair_insert(MAP,HASH,KEY,VALUE)
{
	Pair pair;
	pair.key = KEY;
	pair.value = VALUE;
	stream_insertAtEnd(MAP->exception,Pair,MAP->block[HASH],pair);
};

Map *Map_create(UnsignedSize HASH_SIZE,MapHashFunction HASH_FUNCTION,MapDiffFunction DIFF_FUNCTION)
{
	Map *map;
	if (HASH_SIZE == 0) exception_globalThrowReturnCast("invalid HASH_SIZE",Map*);
	struct_allocate(Map,map);
	exception_globalBypassReturnCast(Map*);
	if (!(map->block = malloc(HASH_SIZE * sizeof(Block_pair)))) exception_globalThrowReturnCast("MEMORY: malloc",Map*);
	for (UnsignedSize hash = 0; hash < HASH_SIZE; ++hash)
	{
		block_create(Pair,map->block[hash]);
		exception_globalBypassReturnCast(Map*);
	};
	map->hashSize = HASH_SIZE;
	map->hashFunction = HASH_FUNCTION;
	map->diffFunction = DIFF_FUNCTION;
	map->length = 0;
	return map;
};

Map *Map_destroy(Map *MAP)
{
	mutex_lock(MAP->mutex);
	for (UnsignedSize hash = 0; hash < MAP->hashSize; ++hash) block_destroy(MAP->block[hash]);
	mutex_destroy(MAP->mutex);
	exception_destroy(MAP->exception);
	free(MAP);
	return NULL;
};

void Map_trim(Map *MAP)
{
	mutex_lock(MAP->mutex);
	for (UnsignedSize hash = 0; hash < MAP->hashSize; ++hash) block_trim(MAP->exception,Pair,MAP->block[hash]);
	mutex_unlock(MAP->mutex);
};

void Map_clear(Map *MAP)
{
	mutex_lock(MAP->mutex);
	for (UnsignedSize hash = 0; hash < MAP->hashSize; ++hash) block_clear(MAP->exception,Pair,MAP->block[hash]);
	MAP->length = 0;
	mutex_unlock(MAP->mutex);
};

Boolean Map_compare(Map *MAP1,Map *MAP2)
{
	Boolean comparison = false;
	mutex_lock(MAP1->mutex);
	mutex_lock(MAP2->mutex);
	if ((MAP1->hashSize == MAP2->hashSize) && (MAP1->length == MAP2->length))
	{
		for (UnsignedSize hash = 0; hash < MAP1->hashSize; ++hash)
		{
			comparison = block_compare(Block_pair,MAP1->block[hash],MAP2->block[hash]);
			if (!comparison) break;
		};
	};
	mutex_unlock(MAP2->mutex);
	mutex_unlock(MAP2->mutex);
	return comparison;
};

void Map_insert(Map *MAP,Undefined KEY,Undefined VALUE)
{
	Boolean found;
	UnsignedSize hash;
	UnsignedSize index;
	mutex_lock(MAP->mutex);
	key_diff(MAP,KEY,hash,index,found);
	if (found) exception_structThrowExit(MAP,"invalid KEY");
	pair_insert(MAP,hash,KEY,VALUE);
	exception_structBypassExit(MAP);
	++MAP->length;
	mutex_unlock(MAP->mutex);
};

Undefined Map_replace(Map *MAP,Undefined KEY,Undefined VALUE)
{
	Boolean found;
	UnsignedSize hash;
	UnsignedSize index;
	mutex_lock(MAP->mutex);
	key_diff(MAP,KEY,hash,index,found);
	if (!found) exception_structThrowReturnCast(MAP,"invalid KEY",Undefined);
	Undefined value = block_getStart(MAP->block[hash])[index].value;
	block_getStart(MAP->block[hash])[index].value = VALUE;
	mutex_unlock(MAP->mutex);
	return value;
};

Undefined Map_set(Map *MAP,Undefined KEY,Undefined VALUE)
{
	Undefined value;
	Boolean found;
	UnsignedSize hash;
	UnsignedSize index;
	mutex_lock(MAP->mutex);
	key_diff(MAP,KEY,hash,index,found);
	if (found)
	{
		value = block_getStart(MAP->block[hash])[index].value;
		block_getStart(MAP->block[hash])[index].value = VALUE;
	}
	else
	{
		pair_insert(MAP,hash,KEY,VALUE);
		exception_structBypassReturnCast(MAP,Undefined);
		++MAP->length;
		value = (Undefined) 0;
	};
	mutex_unlock(MAP->mutex);
	return value;
};

Undefined Map_get(Map *MAP,Undefined KEY)
{
	Boolean found;
	UnsignedSize hash;
	UnsignedSize index;
	mutex_lock(MAP->mutex);
	key_diff(MAP,KEY,hash,index,found);
	if (!found) exception_structThrowReturnCast(MAP,"invalid KEY",Undefined);
	Undefined value = block_getStart(MAP->block[hash])[index].value;
	mutex_unlock(MAP->mutex);
	return value;
};

Undefined Map_remove(Map *MAP,Undefined KEY)
{
	Pair value;
	Boolean found;
	UnsignedSize hash;
	UnsignedSize index;
	mutex_lock(MAP->mutex);
	key_diff(MAP,KEY,hash,index,found);
	if (!found) exception_structThrowReturnCast(MAP,"invalid KEY",Undefined);
	stream_unsafeRemove(MAP->exception,Pair,MAP->block[hash],index,value);
	--MAP->length;
	mutex_unlock(MAP->mutex);
	return value.value;
};

UnsignedSize Map_getHashSize(Map *MAP)
{
	mutex_lock(MAP->mutex);
	UnsignedSize size = MAP->hashSize;
	mutex_unlock(MAP->mutex);
	return size;
};

UnsignedSize Map_getLength(Map *MAP)
{
	mutex_lock(MAP->mutex);
	UnsignedSize length = MAP->length;
	mutex_unlock(MAP->mutex);
	return length;
};

Boolean Map_isEmpty(Map *MAP)
{
	mutex_lock(MAP->mutex);
	Boolean empty = MAP->length == 0;
	mutex_unlock(MAP->mutex);
	return empty;
};

Boolean Map_isNotEmpty(Map *MAP)
{
	mutex_lock(MAP->mutex);
	Boolean empty = MAP->length != 0;
	mutex_unlock(MAP->mutex);
	return empty;
};

Boolean Map_setLock(Map *MAP,Boolean LOCK)
{
	mutex_lock(MAP->mutex);
	mutex_setLock(MAP->exception,MAP->mutex,LOCK);
	exception_structBypassReturn(MAP);
	mutex_unlock(MAP->mutex);
	return !LOCK;
};

Boolean Map_getLock(Map *MAP)
{
	mutex_lock(MAP->mutex);
	Boolean lock = mutex_getLock(MAP->mutex);
	mutex_unlock(MAP->mutex);
	return lock;
};

NullString Map_getException(Map *MAP)
{
	NullString message;
	mutex_lock(MAP->mutex);
	exception_catch(MAP->exception,message);
	mutex_unlock(MAP->mutex);
	return message;
};

void Map_debug(Map *MAP,NullString MESSAGE)
{
	mutex_lock(MAP->mutex);
	printf("MAP { hashSize: %lli, length: %lli, { ",MAP->hashSize,MAP->length);
	if (MAP->length > 0)
	{
		for (UnsignedSize hash = 0; hash < MAP->hashSize; ++hash)
		{
			for (UnsignedSize index = 0; index < block_getLength(MAP->block[hash]); ++index) printf("%lli=%lli ",block_getStart(MAP->block[hash])[index].key.unsignedSize,block_getStart(MAP->block[hash])[index].value.unsignedSize);
		};
	};
	printf("} } #%s\n",MESSAGE);
	mutex_unlock(MAP->mutex);
};
