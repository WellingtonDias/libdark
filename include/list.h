// List
List *List_create(void);
List *List_destroy(List *LIST);

void List_trim(List *LIST);
void List_clear(List *LIST);

Boolean List_compare(List *LIST1,List *LIST2);

void List_insert(List *LIST,SignedSize INDEX,Undefined VALUE);
void List_prepend(List *LIST,Undefined VALUE);
void List_append(List *LIST,Undefined VALUE);
Undefined List_replace(List *LIST,SignedSize INDEX,Undefined VALUE);
Undefined List_set(List *LIST,SignedSize INDEX,Undefined VALUE);
Undefined List_get(List *LIST,SignedSize INDEX);
Undefined List_getFront(List *LIST);
Undefined List_getRear(List *LIST);
Undefined List_remove(List *LIST,SignedSize INDEX);
Undefined List_dequeue(List *LIST);
Undefined List_pop(List *LIST);

void List_swap(List *LIST,SignedSize INDEX1,SignedSize INDEX2);
void List_shuffle(List *LIST,SignedSize START,SignedSize END);
void List_reverse(List *LIST,SignedSize START,SignedSize END);

void List_map(List *LIST,SignedSize START,SignedSize END,ListMapFunction FUNCTION);
void List_filter(List *LIST,SignedSize START,SignedSize END,ListFilterFunction FUNCTION);
Undefined List_reduce(List *LIST,SignedSize START,SignedSize END,ListReduceFunction FUNCTION);
Boolean List_search(List *LIST,SignedSize START,SignedSize END,Undefined TARGET,ListSearchFunction FUNCTION);

void List_merge(List *TARGET_LIST,SignedSize TARGET_INDEX,List *SOURCE_LIST,SignedSize SOURCE_START,SignedSize SOURCE_END);

Undefined *List_getPointer(List *LIST);
UnsignedSize List_getOffset(List *LIST);
UnsignedSize List_setLength(List *LIST,UnsignedSize LENGTH);
UnsignedSize List_getLength(List *LIST);
Boolean List_isEmpty(List *LIST);
Boolean List_isNotEmpty(List *LIST);
UnsignedSize List_getCapacity(List *LIST);
Boolean List_setLock(List *LIST,Boolean LOCK);
Boolean List_getLock(List *LIST);
NullString List_getException(List *LIST);

void List_debug(List *LIST,NullString MESSAGE);

#define List_enqueue List_append
#define List_push    List_append
#define List_getTop  List_getRear
