#template block_define(NAME,TYPE)
{
	typedef struct
	{
		TYPE*        pointer;
		TYPE*        start;
		UnsignedSize offset;
		UnsignedSize length;
		UnsignedSize capacity;
	} NAME;
};

#routine block_update(BLOCK,POINTER,LENGTH,CAPACITY)
{
	BLOCK.pointer = POINTER;
	BLOCK.start = POINTER;
	BLOCK.offset = 0;
	BLOCK.length = LENGTH;
	BLOCK.capacity = CAPACITY;
};

#routine block_calculateIndex(INDEX,LENGTH,RETURN)
{
	RETURN = INDEX;
	if (RETURN < 0) RETURN += LENGTH;
};

#routine block_calculateUnsafeIndex(EXCEPTION,INDEX,LENGTH,RETURN)
{
	#local SignedSize index;
	block_calculateIndex(INDEX,LENGTH,index);
	if (index < 0) exception_routineThrow(EXCEPTION,"invalid INDEX");
	RETURN = index;
};

#routine block_calculateSafeIndex(EXCEPTION,INDEX,LENGTH,RETURN)
{
	#local SignedSize index;
	block_calculateIndex(INDEX,LENGTH,index);
	if ((index < 0) || (index >= (SignedSize) LENGTH)) exception_routineThrow(EXCEPTION,"invalid INDEX");
	RETURN = index;
};

#routine block_calculateRange(EXCEPTION,START,END,LENGTH,RETURN1,RETURN2)
{
	#local SignedSize start;
	#local SignedSize end;
	block_calculateIndex(START,LENGTH,start);
	if (start < 0) exception_routineThrow(EXCEPTION,"invalid RANGE");
	block_calculateIndex(END,LENGTH,end);
	if ((end < start) || (end >= (SignedSize) LENGTH)) exception_routineThrow(EXCEPTION,"invalid RANGE");
	RETURN1 = start;
	RETURN2 = end;
};

#routine block_adjustCapacity(EXCEPTION,#TYPE,BLOCK,LENGTH)
{
	#local UnsignedSize capacity;
	capacity = 1;
	while (capacity < BLOCK.offset + LENGTH) capacity *= 2;
	if (capacity != BLOCK.capacity)
	{
		#local TYPE* pointer;
		if (!(pointer = realloc(BLOCK.pointer,capacity * sizeof(TYPE)))) exception_routineThrow(EXCEPTION,"MEMORY: realloc");
		BLOCK.pointer = pointer;
		BLOCK.start = pointer + BLOCK.offset;
		BLOCK.capacity = capacity;
	};
};

#routine block_create(#TYPE,BLOCK)
{
	#local TYPE* pointer;
	if (!(pointer = malloc(sizeof(TYPE)))) exception_globalThrowBreak("MEMORY: malloc");
	block_update(BLOCK,pointer,0,1);
};

#routine block_destroy(BLOCK)
{
	free(BLOCK.pointer);
	block_update(BLOCK,NULL,0,0);
};

#routine block_trim(EXCEPTION,#TYPE,BLOCK)
{
	if (BLOCK.capacity > BLOCK.length)
	{
		#local TYPE* pointer;
		if (BLOCK.offset > 0)
		{
			memcpy(BLOCK.pointer,BLOCK.start,BLOCK.length * sizeof(TYPE));
			BLOCK.offset = 0;
		};
		if (!(pointer = realloc(BLOCK.pointer,BLOCK.length * sizeof(TYPE)))) exception_routineThrow(EXCEPTION,"MEMORY: realloc");
		BLOCK.pointer = pointer;
		BLOCK.start = pointer;
		BLOCK.capacity = BLOCK.length;
	};
};

#routine block_clear(EXCEPTION,#TYPE,BLOCK)
{
	if (BLOCK.length > 0)
	{
		#local TYPE* pointer;
		if (!(pointer = realloc(BLOCK.pointer,sizeof(TYPE)))) exception_routineThrow(EXCEPTION,"MEMORY: realloc");
		block_update(BLOCK,pointer,0,1);
	};
};

#macro block_compare(#TYPE,BLOCK1,BLOCK2)
{
	(BLOCK1.length == BLOCK2.length) && (memcmp(BLOCK1.start,BLOCK2.start,BLOCK1.length * sizeof(TYPE)) == 0)
};

#routine block_merge(EXCEPTION,#TYPE,TARGET_BLOCK,TARGET_INDEX,SOURCE_BLOCK,SOURCE_START,SOURCE_END)
{
	#local UnsignedSize targetIndex;
	#local UnsignedSize pointerIndex;
	#local UnsignedSize length;
	block_calculateSafeIndex(EXCEPTION,TARGET_INDEX,TARGET_BLOCK.length + 1,targetIndex);
	block_calculateRange(EXCEPTION,SOURCE_START,SOURCE_END,SOURCE_BLOCK.length,pointerIndex,length);
	exception_routineBypass(EXCEPTION);
	length = length - pointerIndex + 1;
	block_adjustCapacity(EXCEPTION,TYPE,TARGET_BLOCK,TARGET_BLOCK.length + length);
	exception_routineBypass(EXCEPTION);
	if (targetIndex < TARGET_BLOCK.length) memmove(TARGET_BLOCK.start + targetIndex + length,TARGET_BLOCK.start + targetIndex,(TARGET_BLOCK.length - targetIndex) * sizeof(TYPE));
	memcpy(TARGET_BLOCK.start + targetIndex,SOURCE_BLOCK.start + pointerIndex,length * sizeof(TYPE));
	TARGET_BLOCK.length += length;
};

#macro block_getPointer(BLOCK)
{
	BLOCK.pointer
};

#macro block_getStart(BLOCK)
{
	BLOCK.start
};

#macro block_getOffset(BLOCK)
{
	BLOCK.offset
};

#routine block_setLength(EXCEPTION,#TYPE,BLOCK,LENGTH,RETURN)
{
	RETURN = BLOCK.length;
	if (LENGTH != BLOCK.length)
	{
		block_adjustCapacity(EXCEPTION,TYPE,BLOCK,LENGTH);
		exception_routineBypass(EXCEPTION);
		if (LENGTH > BLOCK.length) memset(BLOCK.start + BLOCK.length,0,(LENGTH - BLOCK.length) * sizeof(TYPE));
		BLOCK.length = LENGTH;
	};
};

#macro block_getLength(BLOCK)
{
	BLOCK.length
};

#macro block_isEmpty(BLOCK)
{
	BLOCK.length == 0
};

#macro block_isNotEmpty(BLOCK)
{
	BLOCK.length != 0
};

#macro block_getCapacity(BLOCK)
{
	BLOCK.capacity
};
