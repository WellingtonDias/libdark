block_define(Block_undefined,Undefined);

struct _List
{
	Block_undefined block;
	Mutex           mutex;
	Exception       exception;
};

List *List_create(void)
{
	List *list;
	struct_create(List,Undefined,list);
	return list;
};

List *List_createFromContainer(Container *CONTAINER)
{
	List *list;
	struct_createFromContainer(List,Undefined,CONTAINER,list);
	return list;
};

List *List_createFromMemory(Container *CONTAINER,SignedSize START,SignedSize END)
{
	List *list;
	struct_createFromMemory(List,Undefined,CONTAINER,START,END,list);
	return list;
};

List *List_createFromCopy(List *LIST,SignedSize START,SignedSize END)
{
	List *list;
	mutex_lock(LIST->mutex);
	struct_createFromCopy(List,Undefined,LIST,START,END,list);
	mutex_unlock(LIST->mutex);
	return list;
};

List *List_destroy(List *LIST,Boolean SOURCE)
{
	mutex_lock(LIST->mutex);
	struct_destroy(LIST,SOURCE);
	return NULL;
};

void List_trim(List *LIST)
{
	mutex_lock(LIST->mutex);
	block_trim(LIST->exception,Undefined,LIST->block);
	mutex_unlock(LIST->mutex);
};

void List_clear(List *LIST)
{
	mutex_lock(LIST->mutex);
	block_clear(LIST->exception,Undefined,LIST->block);
	mutex_unlock(LIST->mutex);
};

Boolean List_compare(List *LIST1,List *LIST2)
{
	Boolean comparison;
	mutex_lock(LIST1->mutex);
	mutex_lock(LIST2->mutex);
	block_compare(Undefined,LIST1->block,LIST2->block,comparison);
	mutex_unlock(LIST2->mutex);
	mutex_unlock(LIST1->mutex);
	return comparison;
};

void List_insert(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	mutex_lock(LIST->mutex);
	stream_insert(LIST->exception,Undefined,LIST->block,INDEX,VALUE);
	mutex_unlock(LIST->mutex);
};

void List_prepend(List *LIST,Undefined VALUE)
{
	mutex_lock(LIST->mutex);
	stream_insertAtStart(LIST->exception,Undefined,LIST->block,VALUE);
	mutex_unlock(LIST->mutex);
};

void List_append(List *LIST,Undefined VALUE)
{
	mutex_lock(LIST->mutex);
	stream_insertAtEnd(LIST->exception,Undefined,LIST->block,VALUE);
	mutex_unlock(LIST->mutex);
};

Undefined List_replace(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_replace(LIST->exception,Undefined,LIST->block,INDEX,VALUE,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined List_set(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_set(LIST->exception,Undefined,LIST->block,INDEX,VALUE,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined List_get(List *LIST,SignedSize INDEX)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_get(LIST->exception,Undefined,LIST->block,INDEX,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined List_getFront(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_getAtStart(LIST->exception,Undefined,LIST->block,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined List_getRear(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_getAtEnd(LIST->exception,Undefined,LIST->block,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined List_remove(List *LIST,SignedSize INDEX)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_remove(LIST->exception,Undefined,LIST->block,INDEX,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined List_dequeue(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_removeAtStart(LIST->exception,Undefined,LIST->block,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Undefined List_pop(List *LIST)
{
	Undefined value;
	mutex_lock(LIST->mutex);
	stream_removeAtEnd(LIST->exception,Undefined,LIST->block,value);
	mutex_unlock(LIST->mutex);
	return value;
};

void List_swap(List *LIST,SignedSize INDEX1,SignedSize INDEX2)
{
	mutex_lock(LIST->mutex);
	stream_swap(LIST->exception,Undefined,LIST->block,INDEX1,INDEX2);
	mutex_unlock(LIST->mutex);
};

void List_shuffle(List *LIST,SignedSize START,SignedSize END)
{
	mutex_lock(LIST->mutex);
	stream_shuffle(LIST->exception,Undefined,LIST->block,START,END);
	mutex_unlock(LIST->mutex);
};

void List_reverse(List *LIST,SignedSize START,SignedSize END)
{
	mutex_lock(LIST->mutex);
	stream_reverse(LIST->exception,Undefined,LIST->block,START,END);
	mutex_unlock(LIST->mutex);
};

void List_map(List *LIST,SignedSize START,SignedSize END,Undefined (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE))
{
	mutex_lock(LIST->mutex);
	stream_map(LIST->exception,Undefined,LIST->block,START,END,CALLBACK,LIST);
	mutex_unlock(LIST->mutex);
};

void List_filter(List *LIST,SignedSize START,SignedSize END,Boolean (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE))
{
	mutex_lock(LIST->mutex);
	stream_filter(LIST->exception,Undefined,LIST->block,START,END,CALLBACK,LIST);
	mutex_unlock(LIST->mutex);
};

Undefined List_reduce(List *LIST,SignedSize START,SignedSize END,Undefined (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined ACCUMULATOR))
{
	Undefined value = (Undefined) 0;
	mutex_lock(LIST->mutex);
	stream_reduce(LIST->exception,Undefined,LIST->block,START,END,CALLBACK,LIST,value);
	mutex_unlock(LIST->mutex);
	return value;
};

Boolean List_search(List *LIST,SignedSize START,SignedSize END,Undefined TARGET,Boolean (*CALLBACK)(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined TARGET))
{
	Boolean found = false;
	mutex_lock(LIST->mutex);
	stream_search(LIST->exception,Undefined,LIST->block,START,END,CALLBACK,LIST,TARGET,found);
	mutex_unlock(LIST->mutex);
	return found;
};

void List_merge(List *TARGET_LIST,SignedSize TARGET_INDEX,List *SOURCE_LIST,SignedSize SOURCE_START,SignedSize SOURCE_END)
{
	mutex_lock(TARGET_LIST->mutex);
	mutex_lock(SOURCE_LIST->mutex);
	block_merge(TARGET_LIST->exception,Undefined,TARGET_LIST->block,TARGET_INDEX,SOURCE_LIST->block,SOURCE_START,SOURCE_END);
	mutex_unlock(SOURCE_LIST->mutex);
	mutex_unlock(TARGET_LIST->mutex);
};

Undefined *List_getSource(List *LIST)
{
	mutex_lock(LIST->mutex);
	Undefined *source = block_getSource(LIST->block);
	mutex_unlock(LIST->mutex);
	return source;
};

UnsignedSize List_getOffset(List *LIST)
{
	mutex_lock(LIST->mutex);
	UnsignedSize offset = block_getOffset(LIST->block);
	mutex_unlock(LIST->mutex);
	return offset;
};

UnsignedSize List_setSize(List *LIST,UnsignedSize SIZE)
{
	UnsignedSize size;
	mutex_lock(LIST->mutex);
	block_setSize(LIST->exception,Undefined,LIST->block,SIZE,size);
	mutex_unlock(LIST->mutex);
	return size;
};

UnsignedSize List_getSize(List *LIST)
{
	mutex_lock(LIST->mutex);
	UnsignedSize size = block_getSize(LIST->block);
	mutex_unlock(LIST->mutex);
	return size;
};

Boolean List_isEmpty(List *LIST)
{
	mutex_lock(LIST->mutex);
	Boolean empty = block_isEmpty(LIST->block);
	mutex_unlock(LIST->mutex);
	return empty;
};

Boolean List_isNotEmpty(List *LIST)
{
	mutex_lock(LIST->mutex);
	Boolean empty = block_isNotEmpty(LIST->block);
	mutex_unlock(LIST->mutex);
	return empty;
};

UnsignedSize List_getCapacity(List *LIST)
{
	mutex_lock(LIST->mutex);
	UnsignedSize capacity = block_getCapacity(LIST->block);
	mutex_unlock(LIST->mutex);
	return capacity;
};

Boolean List_setLock(List *LIST,Boolean LOCK)
{
	mutex_lock(LIST->mutex);
	mutex_setLock(LIST->exception,LIST->mutex,LOCK);
	mutex_unlock(LIST->mutex);
	return !LOCK;
};

Boolean List_getLock(List *LIST)
{
	mutex_lock(LIST->mutex);
	Boolean lock = mutex_getLock(LIST->mutex);
	mutex_unlock(LIST->mutex);
	return lock;
};

NullString List_getException(List *LIST)
{
	NullString message;
	mutex_lock(LIST->mutex);
	exception_catch(LIST->exception,message);
	mutex_unlock(LIST->mutex);
	return message;
};

void List_debug(List *LIST,NullString LABEL)
{
	mutex_lock(LIST->mutex);
	printf("LIST { offset: %lli, size: %lli, capacity: %lli, source: [ ",block_getOffset(LIST->block),block_getSize(LIST->block),block_getCapacity(LIST->block));
	for (UnsignedSize index = 0; index < block_getSize(LIST->block); ++index) printf("%lli ",block_getStart(LIST->block)[index].unsignedSize);
	printf("] } #%s\n",LABEL);
	mutex_unlock(LIST->mutex);
};
