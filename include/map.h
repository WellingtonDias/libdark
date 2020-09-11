// Map
Map *Map_create(UnsignedSize HASH_SIZE);
Map *Map_destroy(Map *MAP);

void Map_clear(Map *MAP);

Boolean Map_compare(Map *MAP1,Map *MAP2);

void Map_insert(Map *MAP,NullString KEY,Undefined VALUE);

UnsignedSize Map_getHashSize(Map *MAP);
UnsignedSize Map_getLength(Map *MAP);
Boolean Map_isEmpty(Map *MAP);
Boolean Map_isNotEmpty(Map *MAP);
Boolean Map_setLock(Map *MAP,Boolean LOCK);
Boolean Map_getLock(Map *MAP);
NullString Map_getException(Map *MAP);
void Map_debug(Map *MAP,NullString MESSAGE);
