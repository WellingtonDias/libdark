typedef struct
{
	Undefined*   pointer;
	Undefined*   start;
	UnsignedSize offset;
	UnsignedSize length;
	UnsignedSize capacity;
} ListBucket;

struct _List
{
	CompareFunction function;
	ListBucket      bucket;
	Mutex           mutex;
	Exception       exception;
};

#routine listBucket_adjustCapacity(EXCEPTION,BUCKET,LENGTH)
{
	#local UnsignedSize capacity;
	capacity = 1;
	while (capacity < BUCKET.offset + LENGTH) capacity *= 2;
	if (capacity != BUCKET.capacity)
	{
		#local Undefined* pointer;
		if (!(pointer = realloc(BUCKET.pointer,capacity * sizeof(Undefined)))) exception_routineThrow(EXCEPTION,"MEMORY: realloc");
		BUCKET.pointer = pointer;
		BUCKET.start = pointer + BUCKET.offset;
		BUCKET.capacity = capacity;
	};
};

List *List_create(CompareFunction COMPARE_FUNCTION)
{
	List *list;
	if (!(list = calloc(1,sizeof(List)))) exception_globalThrowReturn("MEMORY: calloc");
	list->function = COMPARE_FUNCTION;
	if (!(list->bucket.pointer = malloc(sizeof(Undefined)))) exception_globalThrowReturn("MEMORY: malloc");
	list->bucket.start = list->bucket.pointer;
	list->bucket.offset = 0;
	list->bucket.length = 0;
	list->bucket.capacity = 1;
	return list;
};

List *List_clone(List *LIST)
{
	List *list;
	if (!(list = calloc(1,sizeof(List)))) exception_globalThrowReturn("MEMORY: calloc");
	list->function = LIST->function;
	if (!(list->bucket.pointer = malloc(LIST->bucket.length * sizeof(Undefined)))) exception_globalThrowReturn("MEMORY: malloc");
	memcpy(list->bucket.pointer,LIST->bucket.start,LIST->bucket.length * sizeof(Undefined));
	list->bucket.start = list->bucket.pointer;
	list->bucket.offset = 0;
	list->bucket.length = LIST->bucket.length;
	list->bucket.capacity = LIST->bucket.length;
	return list;
};

List *List_destroy(List *LIST)
{
	mutex_lock(LIST);
	LIST->function = NULL;
	free(LIST->bucket.pointer);
	LIST->bucket.pointer = NULL;
	LIST->bucket.start = NULL;
	LIST->bucket.offset = 0;
	LIST->bucket.length = 0;
	LIST->bucket.capacity = 0;
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
	bucket_calculateSafeIndex(TARGET,INDEX,TARGET->bucket.length + 1,index);
	exception_structBypassExit(TARGET);
	listBucket_adjustCapacity(TARGET->exception,TARGET->bucket,TARGET->bucket.length + SOURCE->bucket.length);
	exception_structBypassExit(TARGET);
	if (index < TARGET->bucket.length) memmove(TARGET->bucket.start + index + SOURCE->bucket.length,TARGET->bucket.start + index,(TARGET->bucket.length - index) * sizeof(Undefined));
	memcpy(TARGET->bucket.start + index,SOURCE->bucket.start,SOURCE->bucket.length * sizeof(Undefined));
	TARGET->bucket.length += SOURCE->bucket.length;
	mutex_unlock(SOURCE);
	mutex_unlock(TARGET);
};

void List_trim(List *LIST)
{
	mutex_lock(LIST);
	if (LIST->bucket.capacity > LIST->bucket.length)
	{
		Undefined *pointer;
		if (LIST->bucket.offset > 0)
		{
			memcpy(LIST->bucket.pointer,LIST->bucket.start,LIST->bucket.length * sizeof(Undefined));
			LIST->bucket.offset = 0;
		};
		if (!(pointer = realloc(LIST->bucket.pointer,LIST->bucket.length * sizeof(Undefined)))) exception_structThrowExit(LIST,"MEMORY: realloc");
		LIST->bucket.pointer = pointer;
		LIST->bucket.start = pointer;
		LIST->bucket.capacity = LIST->bucket.length;
	};
	mutex_unlock(LIST);
};

void List_clip(List *LIST,SignedSize START,SignedSize END)
{
	UnsignedSize start;
	UnsignedSize end;
	mutex_lock(LIST);
	bucket_calculateRange(LIST,START,END,LIST->bucket.length,start,end);
	exception_structBypassExit(LIST);
	LIST->bucket.length = end - start + 1;
	memcpy(LIST->bucket.pointer,LIST->bucket.start + start,LIST->bucket.length * sizeof(Undefined));
	LIST->bucket.start = LIST->bucket.pointer;
	LIST->bucket.offset = 0;
	listBucket_adjustCapacity(LIST->exception,LIST->bucket,LIST->bucket.length);
	exception_structBypassExit(LIST);
	mutex_unlock(LIST);
};

void List_clear(List *LIST)
{
	mutex_lock(LIST);
	if ((LIST->bucket.length > 0) || (LIST->bucket.capacity > 1))
	{
		Undefined *pointer;
		if (!(pointer = realloc(LIST->bucket.pointer,sizeof(Undefined)))) exception_structThrowExit(LIST,"MEMORY: realloc");
		LIST->bucket.pointer = pointer;
		LIST->bucket.start = pointer;
		LIST->bucket.offset = 0;
		LIST->bucket.length = 0;
		LIST->bucket.capacity = 1;
	};
	mutex_unlock(LIST);
};

Boolean List_compare(List *LIST1,List *LIST2)
{
	mutex_lock(LIST1);
	mutex_lock(LIST2);
	Boolean comparison = (LIST1->bucket.length == LIST2->bucket.length) && (memcmp(LIST1->bucket.start,LIST2->bucket.start,LIST1->bucket.length * sizeof(Undefined)) == 0);
	mutex_unlock(LIST2);
	mutex_unlock(LIST1);
	return comparison;
};

void List_insert(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	UnsignedSize index;
	mutex_lock(LIST);
	bucket_calculateSafeIndex(LIST,INDEX,LIST->bucket.length + 1,index);
	exception_structBypassExit(LIST);
	listBucket_adjustCapacity(LIST->exception,LIST->bucket,LIST->bucket.length + 1);
	exception_structBypassExit(LIST);
	if (index < LIST->bucket.length) memmove(LIST->bucket.start + index + 1,LIST->bucket.start + index,(LIST->bucket.length - index) * sizeof(Undefined));
	LIST->bucket.start[index] = VALUE;
	++LIST->bucket.length;
	mutex_unlock(LIST);
};

void List_prepend(List *LIST,Undefined VALUE)
{
	mutex_lock(LIST);
	if (LIST->bucket.offset > 0)
	{
		--LIST->bucket.start;
		--LIST->bucket.offset;
	}
	else
	{
		listBucket_adjustCapacity(LIST->exception,LIST->bucket,LIST->bucket.length + 1);
		exception_structBypassExit(LIST);
		if (LIST->bucket.length > 0) memmove(LIST->bucket.start + 1,LIST->bucket.start,LIST->bucket.length * sizeof(Undefined));
	};
	LIST->bucket.start[0] = VALUE;
	++LIST->bucket.length;
	mutex_unlock(LIST);
};

void List_append(List *LIST,Undefined VALUE)
{
	mutex_lock(LIST);
	listBucket_adjustCapacity(LIST->exception,LIST->bucket,LIST->bucket.length + 1);
	exception_structBypassExit(LIST);
	LIST->bucket.start[LIST->bucket.length] = VALUE;
	++LIST->bucket.length;
	mutex_unlock(LIST);
};

Undefined List_replace(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	UnsignedSize index;
	mutex_lock(LIST);
	bucket_calculateSafeIndex(LIST,INDEX,LIST->bucket.length,index);
	exception_structBypassReturnCast(LIST,Undefined);
	Undefined value = LIST->bucket.start[index];
	LIST->bucket.start[index] = VALUE;
	mutex_unlock(LIST);
	return value;
};

Undefined List_set(List *LIST,SignedSize INDEX,Undefined VALUE)
{
	Undefined value = (Undefined) 0;
	UnsignedSize index;
	mutex_lock(LIST);
	bucket_calculateUnsafeIndex(LIST,INDEX,LIST->bucket.length,index);
	exception_structBypassReturnCast(LIST,Undefined);
	if (index >= LIST->bucket.length)
	{
		listBucket_adjustCapacity(LIST->exception,LIST->bucket,index + 1);
		exception_structBypassReturnCast(LIST,Undefined);
		if (index > LIST->bucket.length) memset(LIST->bucket.start + LIST->bucket.length,0,(index - LIST->bucket.length) * sizeof(Undefined));
		LIST->bucket.length = index + 1;
	}
	else value = LIST->bucket.start[index];
	LIST->bucket.start[index] = VALUE;
	mutex_unlock(LIST);
	return value;
};

SignedSize List_getIndex(List *LIST,Undefined VALUE)
{
	UnsignedSize i = 0;
	mutex_lock(LIST);
	for (; i < LIST->bucket.length; ++i)
	{
		if (!LIST->function)
		{
			if (VALUE.unsignedSize == LIST->bucket.start[i].unsignedSize) break;
		}
		else
		{
			if ((*LIST->function)(VALUE,LIST->bucket.start[i])) break;
		};
	};
	SignedSize index = (i < LIST->bucket.length)? (SignedSize) i : -1;
	mutex_unlock(LIST);
	return index;
};

Undefined List_getValue(List *LIST,SignedSize INDEX)
{
	UnsignedSize index;
	mutex_lock(LIST);
	bucket_calculateSafeIndex(LIST,INDEX,LIST->bucket.length,index);
	exception_structBypassReturnCast(LIST,Undefined);
	Undefined value = LIST->bucket.start[index];
	mutex_unlock(LIST);
	return value;
};

Undefined List_getFront(List *LIST)
{
	mutex_lock(LIST);
	if (LIST->bucket.length == 0) exception_structThrowReturnCast(LIST,"LIST: empty",Undefined);
	Undefined value =  LIST->bucket.start[0];
	mutex_unlock(LIST);
	return value;
};

Undefined List_getRear(List *LIST)
{
	mutex_lock(LIST);
	if (LIST->bucket.length == 0) exception_structThrowReturnCast(LIST,"LIST: empty",Undefined);
	Undefined value = LIST->bucket.start[LIST->bucket.length - 1];
	mutex_unlock(LIST);
	return value;
};

Undefined List_remove(List *LIST,SignedSize INDEX)
{
	UnsignedSize index;
	mutex_lock(LIST);
	bucket_calculateSafeIndex(LIST,INDEX,LIST->bucket.length,index);
	exception_structBypassReturnCast(LIST,Undefined);
	--LIST->bucket.length;
	Undefined value = LIST->bucket.start[index];
	if (index < LIST->bucket.length) memcpy(LIST->bucket.start + index,LIST->bucket.start + index + 1,(LIST->bucket.length - index) * sizeof(Undefined));
	listBucket_adjustCapacity(LIST->exception,LIST->bucket,LIST->bucket.length);
	exception_structBypassReturnCast(LIST,Undefined);
	mutex_unlock(LIST);
	return value;
};

Undefined List_dequeue(List *LIST)
{
	mutex_lock(LIST);
	if (LIST->bucket.length == 0) exception_structThrowReturnCast(LIST,"LIST: empty",Undefined);
	--LIST->bucket.length;
	Undefined value = LIST->bucket.start[0];
	++LIST->bucket.start;
	++LIST->bucket.offset;
	mutex_unlock(LIST);
	return value;
};

Undefined List_pop(List *LIST)
{
	mutex_lock(LIST);
	if (LIST->bucket.length == 0) exception_structThrowReturnCast(LIST,"LIST: empty",Undefined);
	--LIST->bucket.length;
	Undefined value = LIST->bucket.start[LIST->bucket.length];
	listBucket_adjustCapacity(LIST->exception,LIST->bucket,LIST->bucket.length);
	exception_structBypassReturnCast(LIST,Undefined);
	mutex_unlock(LIST);
	return value;
};

void List_swap(List *LIST,SignedSize INDEX1,SignedSize INDEX2)
{
	UnsignedSize index1 = 0;
	UnsignedSize index2;
	mutex_lock(LIST);
	bucket_calculateSafeIndex(LIST,INDEX1,LIST->bucket.length,index1);
	bucket_calculateSafeIndex(LIST,INDEX2,LIST->bucket.length,index2);
	exception_structBypassExit(LIST);
	Undefined value = LIST->bucket.start[index1];
	LIST->bucket.start[index1] = LIST->bucket.start[index2];
	LIST->bucket.start[index2] = value;
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
	if (LENGTH == LIST->bucket.length) exception_structThrowExit(LIST,"invalid LENGTH");
	listBucket_adjustCapacity(LIST->exception,LIST->bucket,LENGTH);
	exception_structBypassExit(LIST);
	if (LENGTH > LIST->bucket.length) memset(LIST->bucket.start + LIST->bucket.length,0,(LENGTH - LIST->bucket.length) * sizeof(Undefined));
	LIST->bucket.length = LENGTH;
	mutex_unlock(LIST);
};

UnsignedSize List_getLength(List *LIST)
{
	mutex_lock(LIST);
	UnsignedSize length = LIST->bucket.length;
	mutex_unlock(LIST);
	return length;
};

Boolean List_isEmpty(List *LIST)
{
	mutex_lock(LIST);
	Boolean empty = LIST->bucket.length == 0;
	mutex_unlock(LIST);
	return empty;
};

Boolean List_isNotEmpty(List *LIST)
{
	mutex_lock(LIST);
	Boolean empty = LIST->bucket.length != 0;
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
	printf("LIST { offset: %lli, length: %lli, capacity: %lli, [ ",LIST->bucket.offset,LIST->bucket.length,LIST->bucket.capacity);
	for (UnsignedSize index = 0; index < LIST->bucket.length; ++index) printf("%lli ",LIST->bucket.start[index].unsignedSize);
	printf("] } #%s\n",MESSAGE);
	mutex_unlock(LIST);
};
