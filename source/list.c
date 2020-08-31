block_define(Block_undefined,Undefined);

struct _List
{
	Block_undefined block;
	Mutex           mutex;
};

void list_debug(List *LIST,NullString LABEL)
{
	mutex_lock(LIST->mutex);
	printf("LIST { offset: %lli, size: %lli, capacity: %lli, source: [ ",block_getOffset(LIST->block),block_getSize(LIST->block),block_getCapacity(LIST->block));
	for (UnsignedSize index = 0; index < block_getSize(LIST->block); ++index) printf("%lli ",block_getStart(LIST->block)[index].usize);
	printf("] } #%s\n",LABEL);
	mutex_unlock(LIST->mutex);
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

List *list_createFromMemoryAtInterval(Pointer *POINTER,SignedSize INDEX,UnsignedSize SIZE)
{
	List *list;
	struct_createFromMemoryAtInterval(List,Undefined,POINTER,INDEX,SIZE,list);
	return list;
};

List *list_createFromMemoryAtRange(Pointer *POINTER,SignedSize START,SignedSize END)
{
	List *list;
	struct_createFromMemoryAtRange(List,Undefined,POINTER,START,END,list);
	return list;
};

List *list_createFromCopyAtInterval(List *LIST,SignedSize INDEX,UnsignedSize SIZE)
{
	List *list;
	mutex_lock(LIST->mutex);
	struct_createFromCopyAtInterval(List,Undefined,LIST,INDEX,SIZE,list);
	mutex_unlock(LIST->mutex);
	return list;
};

List *list_createFromCopyAtRange(List *LIST,SignedSize START,SignedSize END)
{
	List *list;
	mutex_lock(LIST->mutex);
	struct_createFromCopyAtRange(List,Undefined,LIST,START,END,list);
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
	block_trim(Undefined,LIST->block);
	mutex_unlock(LIST->mutex);
};

void list_clear(List *LIST)
{
	mutex_lock(LIST->mutex);
	block_clear(Undefined,LIST->block);
	mutex_unlock(LIST->mutex);
};

Boolean list_compare(List *LIST1,List *LIST2)
{
	mutex_lock(LIST1->mutex);
	mutex_lock(LIST2->mutex);
	Boolean comparison = block_compare(Undefined,LIST1->block,LIST2->block);
	mutex_unlock(LIST2->mutex);
	mutex_unlock(LIST1->mutex);
	return comparison;
};

void list_map(List *LIST,Undefined (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE))
{
	mutex_lock(LIST->mutex);
	block_map(Undefined,LIST->block,CALLBACK,LIST);
	mutex_unlock(LIST->mutex);
};

void list_filter(List *LIST,Boolean (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE))
{
	mutex_lock(LIST->mutex);
	block_filter(Undefined,LIST->block,CALLBACK,LIST);
	mutex_unlock(LIST->mutex);
};

Undefined list_reduce(List *LIST,Undefined (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined ACCUMULATOR))
{
	Undefined value = (Undefined) 0;
	mutex_lock(LIST->mutex);
	block_reduce(Undefined,LIST->block,CALLBACK,LIST,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Boolean list_search(List *LIST,Undefined TARGET,Boolean (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined TARGET))
{
	Boolean found;
	mutex_lock(LIST->mutex);
	block_search(Undefined,LIST->block,CALLBACK,LIST,TARGET,found);
	mutex_unlock(LIST->mutex);
	return found;
};

void list_insert(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	mutex_lock(LIST->mutex);
	block_insertElement(Undefined,LIST->block,INDEX,VALUE);
	mutex_unlock(LIST->mutex);
};

void list_prepend(List *LIST,Undefined VALUE)
{
	mutex_lock(LIST->mutex);
	block_insertElementAtStart(Undefined,LIST->block,VALUE);
	mutex_unlock(LIST->mutex);
};

void list_append(List *LIST,Undefined VALUE)
{
	mutex_lock(LIST->mutex);
	block_insertElementAtEnd(Undefined,LIST->block,VALUE);
	mutex_unlock(LIST->mutex);
};

Undefined list_replace(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	block_replaceElement(Undefined,LIST->block,INDEX,VALUE,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_set(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	block_setElement(Undefined,LIST->block,INDEX,VALUE,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_get(List *LIST,SignedSize INDEX)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	block_getElement(Undefined,LIST->block,INDEX,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_getFront(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	block_getElementAtStart(Undefined,LIST->block,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_getRear(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	block_getElementAtEnd(Undefined,LIST->block,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_remove(List *LIST,SignedSize INDEX)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	block_removeElement(Undefined,LIST->block,INDEX,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_dequeue(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	block_removeElementAtStart(Undefined,LIST->block,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined list_pop(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	block_removeElementAtEnd(Undefined,LIST->block,value);
	mutex_unlock(LIST->mutex);
	return value;
};

void list_swap(List *LIST,SignedSize INDEX1,SignedSize INDEX2)
{
	mutex_lock(LIST->mutex);
	block_swapElements(Undefined,LIST->block,INDEX1,INDEX2);
	mutex_unlock(LIST->mutex);
};

void list_reverseAtInterval(List *LIST,SignedSize INDEX,UnsignedSize SIZE)
{
	mutex_lock(LIST->mutex);
	block_reverseElementsAtInterval(Undefined,LIST->block,INDEX,SIZE);
	mutex_unlock(LIST->mutex);
};

void list_reverseAtRange(List *LIST,SignedSize START,SignedSize END)
{
	mutex_lock(LIST->mutex);
	block_reverseElementsAtRange(Undefined,LIST->block,START,END);
	mutex_unlock(LIST->mutex);
};

void list_shuffleAtInterval(List *LIST,SignedSize INDEX,UnsignedSize SIZE)
{
	mutex_lock(LIST->mutex);
	block_shuffleElementsAtInterval(Undefined,LIST->block,INDEX,SIZE);
	mutex_unlock(LIST->mutex);
};

void list_shuffleAtRange(List *LIST,SignedSize START,SignedSize END)
{
	mutex_lock(LIST->mutex);
	block_shuffleElementsAtRange(Undefined,LIST->block,START,END);
	mutex_unlock(LIST->mutex);
};

void list_mergeFromInterval(List *TARGET_LIST,SignedSize TARGET_INDEX,List *SOURCE_LIST,SignedSize SOURCE_INDEX,UnsignedSize SOURCE_SIZE)
{
	mutex_lock(TARGET_LIST->mutex);
	mutex_lock(SOURCE_LIST->mutex);
	block_mergeFromInterval(Undefined,TARGET_LIST->block,TARGET_INDEX,SOURCE_LIST->block,SOURCE_INDEX,SOURCE_SIZE);
	mutex_unlock(SOURCE_LIST->mutex);
	mutex_unlock(TARGET_LIST->mutex);
};

void list_mergeFromRange(List *TARGET_LIST,SignedSize TARGET_INDEX,List *SOURCE_LIST,SignedSize SOURCE_START,SignedSize SOURCE_END)
{
	mutex_lock(TARGET_LIST->mutex);
	mutex_lock(SOURCE_LIST->mutex);
	block_mergeFromRange(Undefined,TARGET_LIST->block,TARGET_INDEX,SOURCE_LIST->block,SOURCE_START,SOURCE_END);
	mutex_unlock(SOURCE_LIST->mutex);
	mutex_unlock(TARGET_LIST->mutex);
};

Undefined *list_getSource(List *LIST)
{
	mutex_lock(LIST->mutex);
	Undefined *source = block_getSource(LIST->block);
	mutex_unlock(LIST->mutex);
	return source;
};

UnsignedSize list_getOffset(List *LIST)
{
	mutex_lock(LIST->mutex);
	UnsignedSize offset = block_getOffset(LIST->block);
	mutex_unlock(LIST->mutex);
	return offset;
};

UnsignedSize list_setSize(List *LIST,UnsignedSize SIZE)
{
	UnsignedSize size;
	mutex_lock(LIST->mutex);
	block_setSize(Undefined,LIST->block,SIZE,size);
	mutex_unlock(LIST->mutex);
	return size;
};

UnsignedSize list_getSize(List *LIST)
{
	mutex_lock(LIST->mutex);
	UnsignedSize size = block_getSize(LIST->block);
	mutex_unlock(LIST->mutex);
	return size;
};

Boolean list_isEmpty(List *LIST)
{
	mutex_lock(LIST->mutex);
	Boolean empty = block_isEmpty(LIST->block);
	mutex_unlock(LIST->mutex);
	return empty;
};

Boolean list_isNotEmpty(List *LIST)
{
	mutex_lock(LIST->mutex);
	Boolean empty = block_isNotEmpty(LIST->block);
	mutex_unlock(LIST->mutex);
	return empty;
};

UnsignedSize list_getCapacity(List *LIST)
{
	mutex_lock(LIST->mutex);
	UnsignedSize capacity = block_getCapacity(LIST->block);
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
