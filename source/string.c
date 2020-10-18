#routine string_adjustCapacity(EXCEPTION,DATA,LENGTH)
{
	data_adjustCapacity(EXCEPTION,DATA,LENGTH,Character);
};

String *String_create()
{
	String *string;
	if ((string = calloc(1,sizeof(String))) == NULL) exception_globalThrowReturn("MEMORY: calloc");
	if ((string->data.pointer = malloc(1)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	string->data.length = 0;
	string->data.capacity = 1;
	return string;
};

String *String_createFromContainer(Container *CONTAINER)
{
	String *string;
	if ((string = calloc(1,sizeof(String))) == NULL) exception_globalThrowReturn("MEMORY: calloc");
	if ((string->data.pointer = malloc(CONTAINER->size)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	memcpy(string->data.pointer,CONTAINER->pointer,CONTAINER->size);
	string->data.length = CONTAINER->size;
	string->data.capacity = CONTAINER->size;
	return string;
};

String *String_clone(String *STRING)
{
	String *string;
	if ((string = calloc(1,sizeof(String))) == NULL) exception_globalThrowReturn("MEMORY: calloc");
	if ((string->data.pointer = malloc(STRING->data.length)) == NULL) exception_globalThrowReturn("MEMORY: malloc");
	memcpy(string->data.pointer,STRING->data.pointer,STRING->data.length);
	string->data.length = STRING->data.length;
	string->data.capacity = STRING->data.length;
	return string;
};

String *String_destroy(String *STRING)
{
	mutex_lock(STRING);
	free(STRING->data.pointer);
	STRING->data.pointer = NULL;
	STRING->data.length = 0;
	STRING->data.capacity = 0;
	mutex_destroy(STRING);
	exception_destroy(STRING);
	free(STRING);
	return NULL;
};

Boolean String_compare(String *STRING1,String *STRING2)
{
	Boolean comparison;
	mutex_lock(STRING1);
	mutex_lock(STRING2);
	data_compare(STRING1->data,STRING2->data,pointer,Character,comparison);
	mutex_unlock(STRING2);
	mutex_unlock(STRING1);
	return comparison;
};

void String_merge(String *TARGET,SignedSize INDEX,String *SOURCE)
{
	mutex_lock(TARGET);
	mutex_lock(SOURCE);
	data_merge(TARGET->exception,TARGET->data,INDEX,SOURCE->data,string_adjustCapacity,pointer,Character);
	mutex_unlock(SOURCE);
	mutex_unlock(TARGET);
};

void String_clear(String *STRING)
{
	mutex_lock(STRING);
	data_clear(STRING->exception,STRING->data,Character);
	mutex_unlock(STRING);
};

void String_setLength(String *STRING,UnsignedSize LENGTH)
{
	mutex_lock(STRING);
	data_setLength(STRING->exception,STRING->data,LENGTH,string_adjustCapacity,pointer,Character,' ');
	mutex_unlock(STRING);
};

UnsignedSize String_getLength(String *STRING)
{
	mutex_lock(STRING);
	UnsignedSize length = STRING->data.length;
	mutex_unlock(STRING);
	return length;
};

Boolean String_isEmpty(String *STRING)
{
	mutex_lock(STRING);
	Boolean empty = STRING->data.length == 0;
	mutex_unlock(STRING);
	return empty;
};

Boolean String_isNotEmpty(String *STRING)
{
	mutex_lock(STRING);
	Boolean empty = STRING->data.length != 0;
	mutex_unlock(STRING);
	return empty;
};

void String_setMutex(String *STRING,Boolean LOCK)
{
	mutex_lock(STRING);
	mutex_setLock(STRING,LOCK);
	mutex_unlock(STRING);
};

Boolean String_getMutex(String *STRING)
{
	Boolean lock;
	mutex_lock(STRING);
	mutex_getLock(STRING,lock);
	mutex_unlock(STRING);
	return lock;
};

NullString String_getException(String *STRING)
{
	NullString message;
	mutex_lock(STRING);
	exception_getMessage(STRING,message);
	mutex_unlock(STRING);
	return message;
};

void String_debug(String *STRING,NullString MESSAGE)
{
	mutex_lock(STRING);
	printf("STRING: { length: %lli, capacity: %lli, \"%.*s\" } #%s\n",STRING->data.length,STRING->data.capacity,(int) STRING->data.length,STRING->data.pointer,MESSAGE);
	mutex_unlock(STRING);
};
