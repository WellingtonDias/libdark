typedef struct
{
	Undefined*   pointer;
	Undefined*   start;
	UnsignedSize offset;
	UnsignedSize length;
	UnsignedSize capacity;
} ListData;

struct _List
{
	CompareFunction function;
	ListData        data;
	Mutex           mutex;
	Exception       exception;
};

#routine listData_adjustCapacity(EXCEPTION,DATA,LENGTH)
{
	#local UnsignedSize capacity;
	capacity = 1;
	while (capacity < DATA.offset + LENGTH) capacity *= 2;
	if (capacity != DATA.capacity)
	{
		#local Undefined* pointer;
		if (!(pointer = realloc(DATA.pointer,capacity * sizeof(Undefined)))) exception_routineThrow(EXCEPTION,"MEMORY: realloc");
		DATA.pointer = pointer;
		DATA.start = pointer + DATA.offset;
		DATA.capacity = capacity;
	};
};

List *List_create(CompareFunction COMPARE_FUNCTION)
{
	List *list;
	if (!(list = calloc(1,sizeof(List)))) exception_globalThrowReturn("MEMORY: calloc");
	list->function = COMPARE_FUNCTION;
	if (!(list->data.pointer = malloc(sizeof(Undefined)))) exception_globalThrowReturn("MEMORY: malloc");
	list->data.start = list->data.pointer;
	list->data.offset = 0;
	list->data.length = 0;
	list->data.capacity = 1;
	return list;
};

List *List_clone(List *LIST)
{
	List *list;
	if (!(list = calloc(1,sizeof(List)))) exception_globalThrowReturn("MEMORY: calloc");
	list->function = LIST->function;
	if (!(list->data.pointer = malloc(LIST->data.length * sizeof(Undefined)))) exception_globalThrowReturn("MEMORY: malloc");
	memcpy(list->data.pointer,LIST->data.start,LIST->data.length * sizeof(Undefined));
	list->data.start = list->data.pointer;
	list->data.offset = 0;
	list->data.length = LIST->data.length;
	list->data.capacity = LIST->data.length;
	return list;
};

List *List_destroy(List *LIST)
{
	mutex_lock(LIST);
	LIST->function = NULL;
	free(LIST->data.pointer);
	LIST->data.pointer = NULL;
	LIST->data.start = NULL;
	LIST->data.offset = 0;
	LIST->data.length = 0;
	LIST->data.capacity = 0;
	mutex_destroy(LIST);
	exception_destroy(LIST);
	free(LIST);
	return NULL;
};

void List_merge(List *TARGET,SignedSize INDEX,List *SOURCE)
{
	UnsignedSize index;
	mutex_lock(TARGET);
	mutex_lock(SOURCE);
	data_calculateSafeIndex(TARGET,INDEX,TARGET->data.length + 1,index);
	exception_structBypassExit(TARGET);
	listData_adjustCapacity(TARGET->exception,TARGET->data,TARGET->data.length + SOURCE->data.length);
	exception_structBypassExit(TARGET);
	if (index < TARGET->data.length) memmove(TARGET->data.start + index + SOURCE->data.length,TARGET->data.start + index,(TARGET->data.length - index) * sizeof(Undefined));
	memcpy(TARGET->data.start + index,SOURCE->data.start,SOURCE->data.length * sizeof(Undefined));
	TARGET->data.length += SOURCE->data.length;
	mutex_unlock(SOURCE);
	mutex_unlock(TARGET);
};

void List_trim(List *LIST)
{
	mutex_lock(LIST);
	if (LIST->data.capacity > LIST->data.length)
	{
		Undefined *pointer;
		if (LIST->data.offset > 0)
		{
			memcpy(LIST->data.pointer,LIST->data.start,LIST->data.length * sizeof(Undefined));
			LIST->data.offset = 0;
		};
		if (!(pointer = realloc(LIST->data.pointer,LIST->data.length * sizeof(Undefined)))) exception_structThrowExit(LIST,"MEMORY: realloc");
		LIST->data.pointer = pointer;
		LIST->data.start = pointer;
		LIST->data.capacity = LIST->data.length;
	};
	mutex_unlock(LIST);
};

void List_clip(List *LIST,SignedSize START,SignedSize END)
{
	UnsignedSize start;
	UnsignedSize end;
	mutex_lock(LIST);
	data_calculateRange(LIST,START,END,LIST->data.length,start,end);
	exception_structBypassExit(LIST);
	LIST->data.length = end - start + 1;
	memcpy(LIST->data.pointer,LIST->data.start + start,LIST->data.length * sizeof(Undefined));
	LIST->data.start = LIST->data.pointer;
	LIST->data.offset = 0;
	listData_adjustCapacity(LIST->exception,LIST->data,LIST->data.length);
	exception_structBypassExit(LIST);
	mutex_unlock(LIST);
};

void List_clear(List *LIST)
{
	mutex_lock(LIST);
	if ((LIST->data.length > 0) || (LIST->data.capacity > 1))
	{
		Undefined *pointer;
		if (!(pointer = realloc(LIST->data.pointer,sizeof(Undefined)))) exception_structThrowExit(LIST,"MEMORY: realloc");
		LIST->data.pointer = pointer;
		LIST->data.start = pointer;
		LIST->data.offset = 0;
		LIST->data.length = 0;
		LIST->data.capacity = 1;
	};
	mutex_unlock(LIST);
};

Boolean List_compare(List *LIST1,List *LIST2)
{
	mutex_lock(LIST1);
	mutex_lock(LIST2);
	Boolean comparison = (LIST1->data.length == LIST2->data.length) && (memcmp(LIST1->data.start,LIST2->data.start,LIST1->data.length * sizeof(Undefined)) == 0);
	mutex_unlock(LIST2);
	mutex_unlock(LIST1);
	return comparison;
};

void List_insert(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	UnsignedSize index;
	mutex_lock(LIST);
	data_calculateSafeIndex(LIST,INDEX,LIST->data.length + 1,index);
	exception_structBypassExit(LIST);
	listData_adjustCapacity(LIST->exception,LIST->data,LIST->data.length + 1);
	exception_structBypassExit(LIST);
	if (index < LIST->data.length) memmove(LIST->data.start + index + 1,LIST->data.start + index,(LIST->data.length - index) * sizeof(Undefined));
	LIST->data.start[index] = VALUE;
	++LIST->data.length;
	mutex_unlock(LIST);
};

void List_prepend(List *LIST,Undefined VALUE)
{
	mutex_lock(LIST);
	if (LIST->data.offset > 0)
	{
		--LIST->data.start;
		--LIST->data.offset;
	}
	else
	{
		listData_adjustCapacity(LIST->exception,LIST->data,LIST->data.length + 1);
		exception_structBypassExit(LIST);
		if (LIST->data.length > 0) memmove(LIST->data.start + 1,LIST->data.start,LIST->data.length * sizeof(Undefined));
	};
	LIST->data.start[0] = VALUE;
	++LIST->data.length;
	mutex_unlock(LIST);
};

void List_append(List *LIST,Undefined VALUE)
{
	mutex_lock(LIST);
	listData_adjustCapacity(LIST->exception,LIST->data,LIST->data.length + 1);
	exception_structBypassExit(LIST);
	LIST->data.start[LIST->data.length] = VALUE;
	++LIST->data.length;
	mutex_unlock(LIST);
};

Undefined List_replace(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	UnsignedSize index;
	mutex_lock(LIST);
	data_calculateSafeIndex(LIST,INDEX,LIST->data.length,index);
	exception_structBypassReturnCast(LIST,Undefined);
	Undefined value = LIST->data.start[index];
	LIST->data.start[index] = VALUE;
	mutex_unlock(LIST);
	return value;
};

Undefined List_set(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	Undefined value = (Undefined) 0;
	UnsignedSize index;
	mutex_lock(LIST);
	data_calculateUnsafeIndex(LIST,INDEX,LIST->data.length,index);
	exception_structBypassReturnCast(LIST,Undefined);
	if (index >= LIST->data.length)
	{
		listData_adjustCapacity(LIST->exception,LIST->data,index + 1);
		exception_structBypassReturnCast(LIST,Undefined);
		if (index > LIST->data.length) memset(LIST->data.start + LIST->data.length,0,(index - LIST->data.length) * sizeof(Undefined));
		LIST->data.length = index + 1;
	}
	else value = LIST->data.start[index];
	LIST->data.start[index] = VALUE;
	mutex_unlock(LIST);
	return value;
};

SignedSize List_getIndex(List *LIST,Undefined VALUE)
{
	UnsignedSize i = 0;
	mutex_lock(LIST);
	for (; i < LIST->data.length; ++i)
	{
		if (!LIST->function)
		{
			if (VALUE.unsignedSize == LIST->data.start[i].unsignedSize) break;
		}
		else
		{
			if ((*LIST->function)(VALUE,LIST->data.start[i])) break;
		};
	};
	SignedSize index = (i < LIST->data.length)? (SignedSize) i : -1;
	mutex_unlock(LIST);
	return index;
};

Undefined List_getValue(List *LIST,SignedSize INDEX)
{
	UnsignedSize index;
	mutex_lock(LIST);
	data_calculateSafeIndex(LIST,INDEX,LIST->data.length,index);
	exception_structBypassReturnCast(LIST,Undefined);
	Undefined value = LIST->data.start[index];
	mutex_unlock(LIST);
	return value;
};

Undefined List_getFront(List *LIST)
{
	mutex_lock(LIST);
	if (LIST->data.length == 0) exception_structThrowReturnCast(LIST,"LIST: empty",Undefined);
	Undefined value =  LIST->data.start[0];
	mutex_unlock(LIST);
	return value;
};

Undefined List_getRear(List *LIST)
{
	mutex_lock(LIST);
	if (LIST->data.length == 0) exception_structThrowReturnCast(LIST,"LIST: empty",Undefined);
	Undefined value = LIST->data.start[LIST->data.length - 1];
	mutex_unlock(LIST);
	return value;
};

Undefined List_remove(List *LIST,SignedSize INDEX)
{
	UnsignedSize index;
	mutex_lock(LIST);
	data_calculateSafeIndex(LIST,INDEX,LIST->data.length,index);
	exception_structBypassReturnCast(LIST,Undefined);
	--LIST->data.length;
	Undefined value = LIST->data.start[index];
	if (index < LIST->data.length) memcpy(LIST->data.start + index,LIST->data.start + index + 1,(LIST->data.length - index) * sizeof(Undefined));
	listData_adjustCapacity(LIST->exception,LIST->data,LIST->data.length);
	exception_structBypassReturnCast(LIST,Undefined);
	mutex_unlock(LIST);
	return value;
};

Undefined List_dequeue(List *LIST)
{
	mutex_lock(LIST);
	if (LIST->data.length == 0) exception_structThrowReturnCast(LIST,"LIST: empty",Undefined);
	--LIST->data.length;
	Undefined value = LIST->data.start[0];
	++LIST->data.start;
	++LIST->data.offset;
	mutex_unlock(LIST);
	return value;
};

Undefined List_pop(List *LIST)
{
	mutex_lock(LIST);
	if (LIST->data.length == 0) exception_structThrowReturnCast(LIST,"LIST: empty",Undefined);
	--LIST->data.length;
	Undefined value = LIST->data.start[LIST->data.length];
	listData_adjustCapacity(LIST->exception,LIST->data,LIST->data.length);
	exception_structBypassReturnCast(LIST,Undefined);
	mutex_unlock(LIST);
	return value;
};

void List_swap(List *LIST,SignedSize INDEX1,SignedSize INDEX2)
{
	UnsignedSize index1 = 0;
	UnsignedSize index2;
	mutex_lock(LIST);
	data_calculateSafeIndex(LIST,INDEX1,LIST->data.length,index1);
	data_calculateSafeIndex(LIST,INDEX2,LIST->data.length,index2);
	exception_structBypassExit(LIST);
	Undefined value = LIST->data.start[index1];
	LIST->data.start[index1] = LIST->data.start[index2];
	LIST->data.start[index2] = value;
	mutex_unlock(LIST);
};

void List_setCompareFunction(List *LIST,CompareFunction COMPARE_FUNCTION)
{
	mutex_lock(LIST);
	LIST->function = COMPARE_FUNCTION;
	mutex_unlock(LIST);
};

CompareFunction List_getCompareFunction(List *LIST)
{
	mutex_lock(LIST);
	CompareFunction function = LIST->function;
	mutex_unlock(LIST);
	return function;
};

void List_setLength(List *LIST,UnsignedSize LENGTH)
{
	mutex_lock(LIST);
	if (LENGTH == LIST->data.length) exception_structThrowExit(LIST,"invalid LENGTH");
	listData_adjustCapacity(LIST->exception,LIST->data,LENGTH);
	exception_structBypassExit(LIST);
	if (LENGTH > LIST->data.length) memset(LIST->data.start + LIST->data.length,0,(LENGTH - LIST->data.length) * sizeof(Undefined));
	LIST->data.length = LENGTH;
	mutex_unlock(LIST);
};

UnsignedSize List_getLength(List *LIST)
{
	mutex_lock(LIST);
	UnsignedSize length = LIST->data.length;
	mutex_unlock(LIST);
	return length;
};

Boolean List_isEmpty(List *LIST)
{
	mutex_lock(LIST);
	Boolean empty = LIST->data.length == 0;
	mutex_unlock(LIST);
	return empty;
};

Boolean List_isNotEmpty(List *LIST)
{
	mutex_lock(LIST);
	Boolean empty = LIST->data.length != 0;
	mutex_unlock(LIST);
	return empty;
};

void List_setMutex(List *LIST,Boolean LOCK)
{
	mutex_lock(LIST);
	mutex_setLock(LIST,LOCK);
	mutex_unlock(LIST);
};

Boolean List_getMutex(List *LIST)
{
	Boolean lock;
	mutex_lock(LIST);
	mutex_getLock(LIST,lock);
	mutex_unlock(LIST);
	return lock;
};

NullString List_getException(List *LIST)
{
	NullString message;
	mutex_lock(LIST);
	exception_getMessage(LIST,message);
	mutex_unlock(LIST);
	return message;
};

void List_debug(List *LIST,NullString MESSAGE)
{
	mutex_lock(LIST);
	printf("LIST { offset: %lli, length: %lli, capacity: %lli, [ ",LIST->data.offset,LIST->data.length,LIST->data.capacity);
	for (UnsignedSize index = 0; index < LIST->data.length; ++index) printf("%lli ",LIST->data.start[index].unsignedSize);
	printf("] } #%s\n",MESSAGE);
	mutex_unlock(LIST);
};
