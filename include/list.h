// List
List *List_create(CompareFunction COMPARE_FUNCTION);
List *List_clone(List *LIST);
List *List_destroy(List *LIST);

Boolean List_compare(List *LIST1,List *LIST2);
void List_merge(List *TARGET,SignedSize INDEX,List *SOURCE);
void List_trim(List *LIST);
void List_clear(List *LIST);

// void List_insert(List *LIST,SignedSize INDEX,Undefined VALUE);
// void List_prepend(List *LIST,Undefined VALUE);
// void List_append(List *LIST,Undefined VALUE);
// Undefined List_replace(List *LIST,SignedSize INDEX,Undefined VALUE);
// Undefined List_set(List *LIST,SignedSize INDEX,Undefined VALUE);
// SignedSize List_getIndex(List *LIST,Undefined VALUE);
// Undefined List_getValue(List *LIST,SignedSize INDEX);
// Undefined List_getFront(List *LIST);
// Undefined List_getRear(List *LIST);
// List *List_getSubList(List *LIST,SignedSize START,SignedSize END);
// Undefined List_remove(List *LIST,SignedSize INDEX);
// Undefined List_dequeue(List *LIST);
// Undefined List_pop(List *LIST);
// void List_swap(List *LIST,SignedSize INDEX1,SignedSize INDEX2);

void List_setCompareFunction(List *LIST,CompareFunction COMPARE_FUNCTION);
CompareFunction List_getCompareFunction(List *LIST);
void List_setLength(List *LIST,UnsignedSize LENGTH);
UnsignedSize List_getLength(List *LIST);
Boolean List_isEmpty(List *LIST);
Boolean List_isNotEmpty(List *LIST);
void List_setMutex(List *LIST,Boolean LOCK);
Boolean List_getMutex(List *LIST);
NullString List_getException(List *LIST);

void List_debug(List *LIST,NullString MESSAGE);

// #define List_enqueue List_append
// #define List_push    List_append
// #define List_getTop  List_getRear
