box_define(Box_undefined,Undefined);

struct _List
{
	Box_undefined box;
	Mutex         mutex;
};

List *list_create(void)
{
	List *list;
	struct_create(List,Undefined,list);
	return list;
};

List *list_createFromPointer(Pointer *POINTER)
{
	List *list;
	struct_createFromPointer(List,Undefined,POINTER,list);
	return list;
};

List *list_createFromMemory(Pointer *POINTER,SignedSize START,SignedSize END)
{
	List *list;
	struct_createFromMemory(List,Undefined,POINTER,START,END,list);
	return list;
};

List *list_createFromCopy(List *LIST,SignedSize START,SignedSize END)
{
	List *list;
	mutex_lock(LIST->mutex);
	struct_createFromCopy(List,Undefined,LIST,START,END,list);
	mutex_unlock(LIST->mutex);
	return list;
};

List *list_destroy(List *LIST,Boolean SOURCE)
{
	mutex_lock(LIST->mutex);
	struct_destroy(LIST,SOURCE);
	return NULL;
};

void list_trim(List *LIST)
{
	mutex_lock(LIST->mutex);
	box_trim(Undefined,LIST->box);
	mutex_unlock(LIST->mutex);
};

void list_clear(List *LIST)
{
	mutex_lock(LIST->mutex);
	box_clear(Undefined,LIST->box);
	mutex_unlock(LIST->mutex);
};

Boolean list_compare(List *LIST1,List *LIST2)
{
	mutex_lock(LIST1->mutex);
	mutex_lock(LIST2->mutex);
	Boolean comparison = box_compare(Undefined,LIST1->box,LIST2->box);
	mutex_unlock(LIST2->mutex);
	mutex_unlock(LIST1->mutex);
	return comparison;
};

void list_insert(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	mutex_lock(LIST->mutex);
	stream_insert(Undefined,LIST->box,INDEX,VALUE);
	mutex_unlock(LIST->mutex);
};

void list_prepend(List *LIST,Undefined VALUE)
{
	mutex_lock(LIST->mutex);
	stream_insertAtStart(Undefined,LIST->box,VALUE);
	mutex_unlock(LIST->mutex);
};

void list_append(List *LIST,Undefined VALUE)
{
	mutex_lock(LIST->mutex);
	stream_insertAtEnd(Undefined,LIST->box,VALUE);
	mutex_unlock(LIST->mutex);
};

Undefined list_replace(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_replace(Undefined,LIST->box,INDEX,VALUE,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_set(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_set(Undefined,LIST->box,INDEX,VALUE,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_get(List *LIST,SignedSize INDEX)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_get(Undefined,LIST->box,INDEX,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_getFront(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_getAtStart(Undefined,LIST->box,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_getRear(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_getAtEnd(Undefined,LIST->box,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_remove(List *LIST,SignedSize INDEX)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_remove(Undefined,LIST->box,INDEX,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_dequeue(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_removeAtStart(Undefined,LIST->box,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_pop(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_removeAtEnd(Undefined,LIST->box,value);
	mutex_unlock(LIST->mutex);
	return value;
};

void list_swap(List *LIST,SignedSize INDEX1,SignedSize INDEX2)
{
	mutex_lock(LIST->mutex);
	stream_swap(Undefined,LIST->box,INDEX1,INDEX2);
	mutex_unlock(LIST->mutex);
};

void list_shuffle(List *LIST,SignedSize START,SignedSize END)
{
	mutex_lock(LIST->mutex);
	stream_shuffle(Undefined,LIST->box,START,END);
	mutex_unlock(LIST->mutex);
};

void list_reverse(List *LIST,SignedSize START,SignedSize END)
{
	mutex_lock(LIST->mutex);
	stream_reverse(Undefined,LIST->box,START,END);
	mutex_unlock(LIST->mutex);
};

void list_map(List *LIST,SignedSize START,SignedSize END,Undefined (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE))
{
	mutex_lock(LIST->mutex);
	stream_map(Undefined,LIST->box,START,END,CALLBACK,LIST);
	mutex_unlock(LIST->mutex);
};

void list_filter(List *LIST,SignedSize START,SignedSize END,Boolean (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE))
{
	mutex_lock(LIST->mutex);
	stream_filter(Undefined,LIST->box,START,END,CALLBACK,LIST);
	mutex_unlock(LIST->mutex);
};

Undefined list_reduce(List *LIST,SignedSize START,SignedSize END,Undefined (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined ACCUMULATOR))
{
	Undefined value = (Undefined) 0;
	mutex_lock(LIST->mutex);
	stream_reduce(Undefined,LIST->box,START,END,CALLBACK,LIST,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Boolean list_search(List *LIST,SignedSize START,SignedSize END,Undefined TARGET,Boolean (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined TARGET))
{
	Boolean found;
	mutex_lock(LIST->mutex);
	stream_search(Undefined,LIST->box,START,END,CALLBACK,LIST,TARGET,found);
	mutex_unlock(LIST->mutex);
	return found;
};

void list_merge(List *TARGET_LIST,SignedSize TARGET_INDEX,List *SOURCE_LIST,SignedSize SOURCE_START,SignedSize SOURCE_END)
{
	mutex_lock(TARGET_LIST->mutex);
	mutex_lock(SOURCE_LIST->mutex);
	box_merge(Undefined,TARGET_LIST->box,TARGET_INDEX,SOURCE_LIST->box,SOURCE_START,SOURCE_END);
	mutex_unlock(SOURCE_LIST->mutex);
	mutex_unlock(TARGET_LIST->mutex);
};

Undefined *list_getSource(List *LIST)
{
	mutex_lock(LIST->mutex);
	Undefined *source = box_getSource(LIST->box);
	mutex_unlock(LIST->mutex);
	return source;
};

UnsignedSize list_getOffset(List *LIST)
{
	mutex_lock(LIST->mutex);
	UnsignedSize offset = box_getOffset(LIST->box);
	mutex_unlock(LIST->mutex);
	return offset;
};

UnsignedSize list_setSize(List *LIST,UnsignedSize SIZE)
{
	UnsignedSize size;
	mutex_lock(LIST->mutex);
	box_setSize(Undefined,LIST->box,SIZE,size);
	mutex_unlock(LIST->mutex);
	return size;
};

UnsignedSize list_getSize(List *LIST)
{
	mutex_lock(LIST->mutex);
	UnsignedSize size = box_getSize(LIST->box);
	mutex_unlock(LIST->mutex);
	return size;
};

Boolean list_isEmpty(List *LIST)
{
	mutex_lock(LIST->mutex);
	Boolean empty = box_isEmpty(LIST->box);
	mutex_unlock(LIST->mutex);
	return empty;
};

Boolean list_isNotEmpty(List *LIST)
{
	mutex_lock(LIST->mutex);
	Boolean empty = box_isNotEmpty(LIST->box);
	mutex_unlock(LIST->mutex);
	return empty;
};

UnsignedSize list_getCapacity(List *LIST)
{
	mutex_lock(LIST->mutex);
	UnsignedSize capacity = box_getCapacity(LIST->box);
	mutex_unlock(LIST->mutex);
	return capacity;
};

Boolean list_setLock(List *LIST,Boolean LOCK)
{
	mutex_lock(LIST->mutex);
	mutex_setLock(LIST->mutex,LOCK);
	mutex_unlock(LIST->mutex);
	return !LOCK;
};

Boolean list_getLock(List *LIST)
{
	mutex_lock(LIST->mutex);
	Boolean lock = mutex_getLock(LIST->mutex);
	mutex_unlock(LIST->mutex);
	return lock;
};

void list_debug(List *LIST,NullString LABEL)
{
	mutex_lock(LIST->mutex);
	printf("LIST { offset: %lli, size: %lli, capacity: %lli, source: [ ",box_getOffset(LIST->box),box_getSize(LIST->box),box_getCapacity(LIST->box));
	for (UnsignedSize index = 0; index < box_getSize(LIST->box); ++index) printf("%lli ",box_getStart(LIST->box)[index].usize);
	printf("] } #%s\n",LABEL);
	mutex_unlock(LIST->mutex);
};
