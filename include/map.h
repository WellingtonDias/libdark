// Map
Map *Map_create(UnsignedSize HASH_SIZE,MapHashFunction HASH_FUNCTION,MapDiffFunction DIFF_FUNCTION);
Map *Map_destroy(Map *MAP);

void Map_trim(Map *MAP);
void Map_clear(Map *MAP);

Boolean Map_compare(Map *MAP1,Map *MAP2);

void Map_insert(Map *MAP,Undefined KEY,Undefined VALUE);
Undefined Map_replace(Map *MAP,Undefined KEY,Undefined VALUE);
Undefined Map_set(Map *MAP,Undefined KEY,Undefined VALUE);
Undefined Map_get(Map *MAP,Undefined KEY);
Undefined Map_remove(Map *MAP,Undefined KEY);

UnsignedSize Map_getHashSize(Map *MAP);
UnsignedSize Map_getLength(Map *MAP);
Boolean Map_isEmpty(Map *MAP);
Boolean Map_isNotEmpty(Map *MAP);
Boolean Map_setLock(Map *MAP,Boolean LOCK);
Boolean Map_getLock(Map *MAP);
NullString Map_getException(Map *MAP);
void Map_debug(Map *MAP,NullString MESSAGE);
