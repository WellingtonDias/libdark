// Map
Map *Map_create(UnsignedSize HASH_SIZE,HashFunction HASH_FUNCTION,CompareFunction COMPARE_FUNCTION);
Map *Map_clone(Map *MAP);
Map *Map_destroy(Map *MAP);

Boolean Map_compare(Map *MAP1,Map *MAP2);
void Map_merge(Map *TARGET,Map *SOURCE);
void Map_clear(Map *MAP);

// void Map_insert(Map *MAP,Undefined KEY,Undefined VALUE);
// Undefined Map_replace(Map *MAP,Undefined KEY,Undefined VALUE);
// Undefined Map_set(Map *MAP,Undefined KEY,Undefined VALUE);
// Boolean Map_searchKey(Map *MAP,Undefined KEY);
// Boolean Map_searchValue(Map *MAP,Undefined VALUE);
// Undefined Map_getKey(Map *MAP,Undefined VALUE);
// Undefined Map_getValue(Map *MAP,Undefined KEY);
// Undefined Map_remove(Map *MAP,Undefined KEY);
// void Map_swap(Map *MAP,Undefined KEY1,Undefined KEY2);

void Map_setHashFunction(Map *MAP,HashFunction HASH_FUNCTION);
HashFunction Map_getHashFunction(Map *MAP);
void Map_setCompareFunction(Map *MAP,CompareFunction COMPARE_FUNCTION);
CompareFunction Map_getCompareFunction(Map *MAP);
void Map_setHashSize(Map *MAP,UnsignedSize HASH_SIZE);
UnsignedSize Map_getHashSize(Map *MAP);
UnsignedSize Map_getLength(Map *MAP);
Boolean Map_isEmpty(Map *MAP);
Boolean Map_isNotEmpty(Map *MAP);
void Map_setMutex(Map *MAP,Boolean LOCK);
Boolean Map_getMutex(Map *MAP);
NullString Map_getException(Map *MAP);

void Map_debug(Map *MAP,NullString MESSAGE);
