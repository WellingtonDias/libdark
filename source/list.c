#routine list_adjustCapacity(EXCEPTION,DATA,LENGTH)
{
	data_adjustCapacity(EXCEPTION,DATA,DATA.offset + LENGTH,Undefined);
	exception_routineBypass(EXCEPTION);
	DATA.start = DATA.pointer + DATA.offset;
};

List *List_create(CompareFunction COMPARE_FUNCTION)
{
	List *list;
	if ((list = calloc(1,sizeof(List))) == NULL) exception_globalThrowReturn("MEMORY: calloc");
	list->function = COMPARE_FUNCTION;
	if ((list->data.pointer = malloc(sizeof(Undefined))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	list->data.start = list->data.pointer;
	list->data.offset = 0;
	list->data.length = 0;
	list->data.capacity = 1;
	return list;
};

List *List_clone(List *LIST)
{
	List *list;
	if ((list = calloc(1,sizeof(List))) == NULL) exception_globalThrowReturn("MEMORY: calloc");
	list->function = LIST->function;
	if ((list->data.pointer = malloc(LIST->data.length * sizeof(Undefined))) == NULL) exception_globalThrowReturn("MEMORY: malloc");
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

Boolean List_compare(List *LIST1,List *LIST2)
{
	Boolean comparison;
	mutex_lock(LIST1);
	mutex_lock(LIST2);
	data_compare(LIST1->data,LIST2->data,pointer,Undefined,comparison);
	mutex_unlock(LIST2);
	mutex_unlock(LIST1);
	return comparison;
};

void List_merge(List *TARGET,SignedSize INDEX,List *SOURCE)
{
	mutex_lock(TARGET);
	mutex_lock(SOURCE);
	data_merge(TARGET->exception,TARGET->data,INDEX,SOURCE->data,list_adjustCapacity,start,Undefined);
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
		if ((pointer = realloc(LIST->data.pointer,LIST->data.length * sizeof(Undefined))) == NULL) exception_structThrowExit(LIST,"MEMORY: realloc");
		LIST->data.pointer = pointer;
		LIST->data.start = pointer;
		LIST->data.capacity = LIST->data.length;
	};
	mutex_unlock(LIST);
};

void List_clear(List *LIST)
{
	mutex_lock(LIST);
	if ((LIST->data.length > 0) || (LIST->data.capacity > 1))
	{
		Undefined *pointer;
		if ((pointer = realloc(LIST->data.pointer,sizeof(Undefined))) == NULL) exception_structThrowExit(LIST,"MEMORY: realloc");
		LIST->data.pointer = pointer;
		LIST->data.start = pointer;
		LIST->data.offset = 0;
		LIST->data.length = 0;
		LIST->data.capacity = 1;
	};
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
	data_setLength(LIST->exception,LIST->data,LENGTH,list_adjustCapacity,start,Undefined,0);
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
	printf("LIST: { offset: %lli, length: %lli, capacity: %lli, [ ",LIST->data.offset,LIST->data.length,LIST->data.capacity);
	for (UnsignedSize index = 0; index < LIST->data.length; ++index) printf("%lli ",LIST->data.start[index].unsignedSize);
	printf("] } #%s\n",MESSAGE);
	mutex_unlock(LIST);
};
