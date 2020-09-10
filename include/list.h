// List
List *List_create(void);
List *List_createFromContainer(Container *CONTAINER);
List *List_createFromMemory(Container *CONTAINER,SignedSize START,SignedSize END);
List *List_createFromCopy(List *LIST,SignedSize START,SignedSize END);
List *List_destroy(List *LIST,Boolean SOURCE);

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

void List_map(List *LIST,SignedSize START,SignedSize END,Undefined (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE));
void List_filter(List *LIST,SignedSize START,SignedSize END,Boolean (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE));
Undefined List_reduce(List *LIST,SignedSize START,SignedSize END,Undefined (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined ACCUMULATOR));
Boolean List_search(List *LIST,SignedSize START,SignedSize END,Undefined TARGET,Boolean (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined TARGET));

void List_merge(List *TARGET_LIST,SignedSize TARGET_INDEX,List *SOURCE_LIST,SignedSize SOURCE_START,SignedSize SOURCE_END);

Undefined *List_getSource(List *LIST);
UnsignedSize List_getOffset(List *LIST);
UnsignedSize List_setSize(List *LIST,UnsignedSize SIZE);
UnsignedSize List_getSize(List *LIST);
Boolean List_isEmpty(List *LIST);
Boolean List_isNotEmpty(List *LIST);
UnsignedSize List_getCapacity(List *LIST);
Boolean List_setLock(List *LIST,Boolean LOCK);
Boolean List_getLock(List *LIST);
NullString List_getException(List *LIST);

void List_debug(List *LIST,NullString LABEL);

#define List_enqueue List_append
#define List_push    List_append
#define List_getTop  List_getRear
