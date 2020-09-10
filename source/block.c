#template block_define(NAME,TYPE)
{
	typedef struct
	{
		TYPE*        source;
		TYPE*        start;
		UnsignedSize offset;
		UnsignedSize size;
		UnsignedSize capacity;
	} NAME;
};

#routine block_update(BLOCK,SOURCE,SIZE,CAPACITY)
{
	BLOCK.source = SOURCE;
	BLOCK.start = SOURCE;
	BLOCK.offset = 0;
	BLOCK.size = SIZE;
	BLOCK.capacity = CAPACITY;
};

#routine block_calculateIndex(INDEX,SIZE,RETURN)
{
	RETURN = INDEX;
	if (RETURN < 0) RETURN += SIZE;
};

#routine block_calculateUnsafeIndex(EXCEPTION,INDEX,SIZE,RETURN)
{
	#local SignedSize index;
	block_calculateIndex(INDEX,SIZE,index);
	if (index < 0) exception_routineThrow(EXCEPTION,"invalid INDEX");
	RETURN = index;
};

#routine block_calculateSafeIndex(EXCEPTION,INDEX,SIZE,RETURN)
{
	#local SignedSize index;
	block_calculateIndex(INDEX,SIZE,index);
	if ((index < 0) || (index >= (SignedSize) SIZE)) exception_routineThrow(EXCEPTION,"invalid INDEX");
	RETURN = index;
};

#routine block_calculateRange(EXCEPTION,START,END,SIZE,RETURN1,RETURN2)
{
	#local SignedSize start;
	#local SignedSize end;
	block_calculateIndex(START,SIZE,start);
	if (start < 0) exception_routineThrow(EXCEPTION,"invalid RANGE");
	block_calculateIndex(END,SIZE,end);
	if ((end < start) || (end >= (SignedSize) SIZE)) exception_routineThrow(EXCEPTION,"invalid RANGE");
	RETURN1 = start;
	RETURN2 = end;
};

#routine block_adjustCapacity(EXCEPTION,#TYPE,BLOCK,SIZE)
{
	#local UnsignedSize capacity;
	capacity = 1;
	while (capacity < BLOCK.offset + SIZE) capacity *= 2;
	if (capacity != BLOCK.capacity)
	{
		#local TYPE* source;
		if (!(source = realloc(BLOCK.source,capacity * sizeof(TYPE)))) exception_routineThrow(EXCEPTION,"MEMORY: realloc");
		BLOCK.source = source;
		BLOCK.start = source + BLOCK.offset;
		BLOCK.capacity = capacity;
	};
};

#routine block_create(#TYPE,BLOCK)
{
	#local TYPE* source;
	if (!(source = malloc(sizeof(TYPE)))) exception_globalThrowBreak("MEMORY: malloc");
	block_update(BLOCK,source,0,1);
};

#routine block_createFromContainer(#TYPE,BLOCK,CONTAINER)
{
	block_update(BLOCK,container_getPointer(CONTAINER),container_getSize(CONTAINER),container_getSize(CONTAINER));
};

#routine block_createFromPointer(#TYPE,BLOCK,POINTER,SIZE)
{
	#local TYPE* source;
	if (!(source = malloc(SIZE * sizeof(TYPE)))) exception_globalThrowBreak("MEMORY: malloc");
	memcpy(source,POINTER,SIZE * sizeof(TYPE));
	block_update(BLOCK,source,SIZE,SIZE);
};

#routine block_createFromMemory(#TYPE,BLOCK,CONTAINER,START,END)
{
	#local UnsignedSize index;
	#local UnsignedSize size;
	block_calculateRange(ExceptionGlobal,START,END,container_getSize(CONTAINER),index,size);
	exception_globalBypassBreak();
	size = size - index + 1;
	block_createFromPointer(TYPE,BLOCK,container_getPointer(CONTAINER) + index,size);
};

#routine block_createFromCopy(#TYPE,TARGET_BLOCK,SOURCE_BLOCK,START,END)
{
	#local UnsignedSize index;
	#local UnsignedSize size;
	block_calculateRange(ExceptionGlobal,START,END,SOURCE_BLOCK.size,index,size);
	exception_globalBypassBreak();
	size = size - index + 1;
	block_createFromPointer(TYPE,TARGET_BLOCK,SOURCE_BLOCK.start + index,size);
};

#routine block_destroy(BLOCK,DEALLOCATE)
{
	if (DEALLOCATE) free(BLOCK.source);
	block_update(BLOCK,NULL,0,0);
};

#routine block_trim(EXCEPTION,#TYPE,BLOCK)
{
	if (BLOCK.capacity > BLOCK.size)
	{
		#local TYPE* source;
		if (BLOCK.offset > 0)
		{
			memcpy(BLOCK.source,BLOCK.start,BLOCK.size * sizeof(TYPE));
			BLOCK.offset = 0;
		};
		if (!(source = realloc(BLOCK.source,BLOCK.size * sizeof(TYPE)))) exception_routineThrow(EXCEPTION,"MEMORY: realloc");
		BLOCK.source = source;
		BLOCK.start = source;
		BLOCK.capacity = BLOCK.size;
	};
};

#routine block_clear(EXCEPTION,#TYPE,BLOCK)
{
	if (BLOCK.size > 0)
	{
		#local TYPE* source;
		if (!(source = realloc(BLOCK.source,sizeof(TYPE)))) exception_routineThrow(EXCEPTION,"MEMORY: realloc");
		block_update(BLOCK,source,0,1);
	};
};

#routine block_compare(#TYPE,BLOCK1,BLOCK2,RETURN)
{
	RETURN = (BLOCK1.size == BLOCK2.size) && (memcmp(BLOCK1.start,BLOCK2.start,BLOCK1.size * sizeof(TYPE)) == 0);
};

#routine block_merge(EXCEPTION,#TYPE,TARGET_BLOCK,TARGET_INDEX,SOURCE_BLOCK,SOURCE_START,SOURCE_END)
{
	#local UnsignedSize targetIndex;
	#local UnsignedSize sourceIndex;
	#local UnsignedSize size;
	block_calculateSafeIndex(EXCEPTION,TARGET_INDEX,TARGET_BLOCK.size + 1,targetIndex);
	block_calculateRange(EXCEPTION,SOURCE_START,SOURCE_END,SOURCE_BLOCK.size,sourceIndex,size);
	exception_routineBypass(EXCEPTION);
	size = size - sourceIndex + 1;
	block_adjustCapacity(EXCEPTION,TYPE,TARGET_BLOCK,TARGET_BLOCK.size + size);
	exception_routineBypass(EXCEPTION);
	if (targetIndex < TARGET_BLOCK.size) memmove(TARGET_BLOCK.start + targetIndex + size,TARGET_BLOCK.start + targetIndex,(TARGET_BLOCK.size - targetIndex) * sizeof(TYPE));
	memcpy(TARGET_BLOCK.start + targetIndex,SOURCE_BLOCK.start + sourceIndex,size * sizeof(TYPE));
	TARGET_BLOCK.size += size;
};

#macro block_getSource(BLOCK)
{
	BLOCK.source
};

#macro block_getStart(BLOCK)
{
	BLOCK.start
};

#macro block_getOffset(BLOCK)
{
	BLOCK.offset
};

#routine block_setSize(EXCEPTION,#TYPE,BLOCK,SIZE,RETURN)
{
	RETURN = BLOCK.size;
	if (SIZE != BLOCK.size)
	{
		block_adjustCapacity(EXCEPTION,TYPE,BLOCK,SIZE);
		exception_routineBypass(EXCEPTION);
		if (SIZE > BLOCK.size) memset(BLOCK.start + BLOCK.size,0,(SIZE - BLOCK.size) * sizeof(TYPE));
		BLOCK.size = SIZE;
	};
};

#macro block_getSize(BLOCK)
{
	BLOCK.size
};

#macro block_isEmpty(BLOCK)
{
	BLOCK.size == 0
};

#macro block_isNotEmpty(BLOCK)
{
	BLOCK.size != 0
};

#macro block_getCapacity(BLOCK)
{
	BLOCK.capacity
};
