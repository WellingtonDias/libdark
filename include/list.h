// List
List *list_create(void);
List *list_createFromPointer(Pointer *POINTER);
List *list_createFromMemoryAtInterval(Pointer *POINTER,SignedSize INDEX,UnsignedSize SIZE);
List *list_createFromMemoryAtRange(Pointer *POINTER,SignedSize START,SignedSize END);
List *list_createFromCopyAtInterval(List *LIST,SignedSize INDEX,UnsignedSize SIZE);
List *list_createFromCopyAtRange(List *LIST,SignedSize START,SignedSize END);
List *list_destroy(List *LIST,Boolean SOURCE);

void list_trim(List *LIST);
void list_clear(List *LIST);

Boolean list_compare(List *LIST1,List *LIST2);
void list_map(List *LIST,Undefined (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE));
void list_filter(List *LIST,Boolean (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE));
Undefined list_reduce(List *LIST,Undefined (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined ACCUMULATOR));
Boolean list_search(List *LIST,Undefined TARGET,Boolean (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined TARGET));

void list_insert(List *LIST,SignedSize INDEX,Undefined VALUE);
void list_prepend(List *LIST,Undefined VALUE);
void list_append(List *LIST,Undefined VALUE);
Undefined list_replace(List *LIST,SignedSize INDEX,Undefined VALUE);
Undefined list_set(List *LIST,SignedSize INDEX,Undefined VALUE);
Undefined list_get(List *LIST,SignedSize INDEX);
Undefined list_getFront(List *LIST);
Undefined list_getRear(List *LIST);
void list_swap(List *LIST,SignedSize INDEX1,SignedSize INDEX2);
Undefined list_remove(List *LIST,SignedSize INDEX);
Undefined list_dequeue(List *LIST);
Undefined list_pop(List *LIST);

void list_reverseAtInterval(List *LIST,SignedSize INDEX,UnsignedSize SIZE);
void list_reverseAtRange(List *LIST,SignedSize START,SignedSize END);
void list_shuffleAtInterval(List *LIST,SignedSize INDEX,UnsignedSize SIZE);
void list_shuffleAtRange(List *LIST,SignedSize START,SignedSize END);

void list_mergeFromInterval(List *TARGET_LIST,SignedSize TARGET_INDEX,List *SOURCE_LIST,SignedSize SOURCE_INDEX,UnsignedSize SOURCE_SIZE);
void list_mergeFromRange(List *TARGET_LIST,SignedSize TARGET_INDEX,List *SOURCE_LIST,SignedSize SOURCE_START,SignedSize SOURCE_END);

Undefined *list_getSource(List *LIST);
UnsignedSize list_getOffset(List *LIST);
UnsignedSize list_setSize(List *LIST,UnsignedSize SIZE);
UnsignedSize list_getSize(List *LIST);
Boolean list_isEmpty(List *LIST);
Boolean list_isNotEmpty(List *LIST);
UnsignedSize list_getCapacity(List *LIST);
Boolean list_setLock(List *LIST,Boolean LOCK);
Boolean list_getLock(List *LIST);

void list_debug(List *LIST,NullString LABEL);

#define list_enqueue list_append
#define list_push    list_append
#define list_getTop  list_getRear
