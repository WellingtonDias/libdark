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

#routine block_calculateIndex(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	OUTPUT_INDEX = INPUT_INDEX;
	if (OUTPUT_INDEX < 0) OUTPUT_INDEX += SIZE;
};

#macro block_validateIndex(INDEX,START,SIZE)
{
	(INDEX >= (SignedSize) START) && (INDEX < (SignedSize) SIZE)
};

#routine block_calculateSize(START,END,SIZE)
{
	SIZE = END - START + 1;
};

#routine block_calculateEnd(INDEX,SIZE,END)
{
	END = INDEX + SIZE - 1;
};

#routine block_calculateUnsafeIndex(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	#local SignedSize index;
	block_calculateIndex(INPUT_INDEX,SIZE,index);
	if (index < 0) exception_throwBreak("invalid INDEX");
	OUTPUT_INDEX = index;
};

#routine block_calculateSafeIndex(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	#local SignedSize index;
	block_calculateIndex(INPUT_INDEX,SIZE,index);
	if (!block_validateIndex(index,0,SIZE)) exception_throwBreak("invalid INDEX");
	OUTPUT_INDEX = index;
};

#routine block_calculateInterval(INPUT_INDEX,INPUT_SIZE,SIZE,OUTPUT_INDEX)
{
	#local SignedSize index;
	block_calculateIndex(INPUT_INDEX,SIZE,index);
	if (!block_validateIndex(index,0,SIZE)) exception_throwBreak("invalid INTERVAL");
	if (INPUT_SIZE > SIZE) exception_throwBreak("invalid INTERVAL");
	if (index > (SignedSize) SIZE - (SignedSize) INPUT_SIZE) exception_throwBreak("invalid INTERVAL");
	OUTPUT_INDEX = index;
};

#routine block_calculateRange(INPUT_START,INPUT_END,SIZE,OUTPUT_START,OUTPUT_END)
{
	#local SignedSize start;
	#local SignedSize end;
	block_calculateIndex(INPUT_START,SIZE,start);
	if (!block_validateIndex(start,0,SIZE)) exception_throwBreak("invalid RANGE");
	block_calculateIndex(INPUT_END,SIZE,end);
	if (!block_validateIndex(end,start,SIZE)) exception_throwBreak("invalid RANGE");
	OUTPUT_START = start;
	OUTPUT_END = end;
};

#routine block_calculateCapacity(SIZE,CAPACITY)
{
	CAPACITY = 1;
	while (CAPACITY < SIZE) CAPACITY *= 2;
};

#routine block_adjustCapacity(#TYPE,BLOCK,SIZE)
{
	#local UnsignedSize capacity;
	block_calculateCapacity(BLOCK.offset + SIZE,capacity);
	if (capacity != BLOCK.capacity)
	{
		#local TYPE* source;
		if (!(source = realloc(BLOCK.source,capacity * sizeof(TYPE)))) exception_throwBreak("MEMORY: realloc");
		BLOCK.source = source;
		BLOCK.start = source + BLOCK.offset;
		BLOCK.capacity = capacity;
	};
};

#routine block_update(BLOCK,SOURCE,SIZE,CAPACITY)
{
	BLOCK.source = SOURCE;
	BLOCK.start = SOURCE;
	BLOCK.offset = 0;
	BLOCK.size = SIZE;
	BLOCK.capacity = CAPACITY;
};

#routine block_create(#TYPE,BLOCK)
{
	#local TYPE* source;
	if (!(source = malloc(sizeof(TYPE)))) exception_throwBreak("MEMORY: malloc");
	block_update(BLOCK,source,0,1);
};

#routine block_createFromPointer(#TYPE,BLOCK,POINTER)
{
	if ((pointer_getSource(POINTER) == NULL) || (pointer_getSize(POINTER) == 0)) exception_throwBreak("invalid POINTER");
	block_update(BLOCK,pointer_getSource(POINTER),pointer_getSize(POINTER),pointer_getSize(POINTER));
};

#routine block_createFromMemory(#TYPE,BLOCK,RAW_POINTER,SIZE)
{
	#local TYPE* source;
	if (!(source = malloc(SIZE * sizeof(TYPE)))) exception_throwBreak("MEMORY: malloc");
	memcpy(source,RAW_POINTER,SIZE * sizeof(TYPE));
	block_update(BLOCK,source,SIZE,SIZE);
};

#routine block_createFromMemoryAtInterval(#TYPE,BLOCK,POINTER,INDEX,SIZE)
{
	#local UnsignedSize index;
	if ((pointer_getSource(POINTER) == NULL) || (pointer_getSize(POINTER) == 0)) exception_throwBreak("invalid POINTER");
	block_calculateInterval(INDEX,SIZE,pointer_getSize(POINTER),index);
	block_createFromMemory(TYPE,BLOCK,pointer_getSource(POINTER) + index,SIZE);
};

#routine block_createFromMemoryAtRange(#TYPE,BLOCK,POINTER,START,END)
{
	#local UnsignedSize index;
	#local UnsignedSize size;
	if ((pointer_getSource(POINTER) == NULL) || (pointer_getSize(POINTER) == 0)) exception_throwBreak("invalid POINTER");
	block_calculateRange(START,END,pointer_getSize(POINTER),index,size)
	block_calculateSize(index,size,size);
	block_createFromMemory(TYPE,BLOCK,pointer_getSource(POINTER) + index,size);
};

#routine block_createFromCopyAtInterval(#TYPE,BLOCK,SOURCE,INDEX,SIZE)
{
	#local UnsignedSize index;
	block_calculateInterval(INDEX,SIZE,SOURCE.size,index);
	block_createFromMemory(TYPE,BLOCK,SOURCE.start + index,SIZE);
};

#routine block_createFromCopyAtRange(#TYPE,BLOCK,SOURCE,START,END)
{
	#local UnsignedSize index;
	#local UnsignedSize size;
	block_calculateRange(START,END,SOURCE.size,index,size)
	block_calculateSize(index,size,size);
	block_createFromMemory(TYPE,BLOCK,SOURCE.start + index,size);
};

#routine block_trim(#TYPE,BLOCK)
{
	if (BLOCK.capacity > BLOCK.size)
	{
		#local TYPE* source;
		if (BLOCK.offset > 0)
		{
			memcpy(BLOCK.source,BLOCK.start,BLOCK.size * sizeof(TYPE));
			BLOCK.offset = 0;
		};
		if (!(source = realloc(BLOCK.source,BLOCK.size * sizeof(TYPE)))) exception_throwBreak("MEMORY: realloc");
		BLOCK.source = source;
		BLOCK.start = source;
		BLOCK.capacity = BLOCK.size;
	};
};

#routine block_clear(#TYPE,BLOCK)
{
	if (BLOCK.size > 0)
	{
		#local TYPE* source;
		if (!(source = realloc(BLOCK.source,sizeof(TYPE)))) exception_throwBreak("MEMORY: realloc");
		block_update(BLOCK,source,0,1);
	};
};

#routine block_destroy(BLOCK)
{
	free(BLOCK.source);
};

#macro block_compare(#TYPE,BLOCK1,BLOCK2)
{
	(BLOCK1.size == BLOCK2.size) && (memcmp(BLOCK1.start,BLOCK2.start,BLOCK1.size * sizeof(TYPE)) == 0)
};

#routine block_map(#TYPE,BLOCK,#CALLBACK,STRUCT)
{
	for (#local UnsignedSize index; index < BLOCK.size; ++index) BLOCK.start[index] = (*CALLBACK)(STRUCT,index,BLOCK.start[index]);
};

#routine block_filter(#TYPE,BLOCK,#CALLBACK,STRUCT)
{
	for (#local UnsignedSize index; index < BLOCK.size; ++index)
	{
		if (!(*CALLBACK)(STRUCT,index,BLOCK.start[index]))
		{
			--BLOCK.size;
			if (index < BLOCK.size) memcpy(BLOCK.start + index,BLOCK.start + index + 1,(BLOCK.size - index) * sizeof(TYPE));
			--index;
		};
	};
	block_adjustCapacity(TYPE,BLOCK,BLOCK.size);
};

#routine block_reduce(#TYPE,BLOCK,#CALLBACK,STRUCT,ACCUMULATOR)
{
	for (#local UnsignedSize index; index < BLOCK.size; ++index) ACCUMULATOR = (*CALLBACK)(STRUCT,index,BLOCK.start[index],ACCUMULATOR);
};

#routine block_search(#TYPE,BLOCK,#CALLBACK,STRUCT,TARGET,FOUND)
{
	#local UnsignedSize index;
	for (; index < BLOCK.size; ++index)
	{
		if ((*CALLBACK)(STRUCT,index,BLOCK.start[index],TARGET)) break;
	};
	FOUND = index < BLOCK.size;
};

#routine block_insertElement(#TYPE,BLOCK,INDEX,VALUE)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(INDEX,BLOCK.size + 1,index);
	block_adjustCapacity(TYPE,BLOCK,BLOCK.size + 1);
	if (index < BLOCK.size) memmove(BLOCK.start + index + 1,BLOCK.start + index,(BLOCK.size - index) * sizeof(TYPE));
	BLOCK.start[index] = VALUE;
	++BLOCK.size;
};

#routine block_insertElementAtStart(#TYPE,BLOCK,VALUE)
{
	if (BLOCK.offset > 0)
	{
		--BLOCK.start;
		--BLOCK.offset;
	}
	else
	{
		block_adjustCapacity(TYPE,BLOCK,BLOCK.size + 1);
		if (BLOCK.size > 0) memmove(BLOCK.start + 1,BLOCK.start,BLOCK.size * sizeof(TYPE));
	};
	BLOCK.start[0] = VALUE;
	++BLOCK.size;
};

#routine block_insertElementAtEnd(#TYPE,BLOCK,VALUE)
{
	block_adjustCapacity(TYPE,BLOCK,BLOCK.size + 1);
	BLOCK.start[BLOCK.size] = VALUE;
	++BLOCK.size;
};

#routine block_replaceElement(#TYPE,BLOCK,INDEX,NEW_ELEMENT,OLD_ELEMENT)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(INDEX,BLOCK.size,index);
	OLD_ELEMENT = BLOCK.start[index];
	BLOCK.start[index] = NEW_ELEMENT;
};

#routine block_setElement(#TYPE,BLOCK,INDEX,NEW_ELEMENT,OLD_ELEMENT)
{
	#local UnsignedSize index;
	block_calculateUnsafeIndex(INDEX,BLOCK.size,index);
	if (index >= BLOCK.size)
	{
		block_adjustCapacity(TYPE,BLOCK,index + 1);
		if (index > BLOCK.size) memset(BLOCK.start + BLOCK.size,0,(index - BLOCK.size) * sizeof(TYPE));
		BLOCK.size = index + 1;
		OLD_ELEMENT = (TYPE) 0;
	}
	else OLD_ELEMENT = BLOCK.start[index];
	BLOCK.start[index] = NEW_ELEMENT;
};

#routine block_getElement(#TYPE,BLOCK,INDEX,VALUE)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(INDEX,BLOCK.size,index);
	VALUE = BLOCK.start[index];
};

#routine block_getElementAtStart(#TYPE,BLOCK,VALUE)
{
	if (BLOCK.size == 0) exception_throwBreak("BLOCK: empty");
	VALUE = BLOCK.start[0];
};

#routine block_getElementAtEnd(#TYPE,BLOCK,VALUE)
{
	if (BLOCK.size == 0) exception_throwBreak("BLOCK: empty");
	VALUE = BLOCK.start[BLOCK.size - 1];
};

#routine block_eraseElement(#TYPE,BLOCK,INDEX,VALUE)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(INDEX,BLOCK.size,index);
	VALUE = BLOCK.start[index];
	BLOCK.start[index] = (TYPE) 0;
};

#routine block_removeElement(#TYPE,BLOCK,INDEX,VALUE)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(INDEX,BLOCK.size,index);
	--BLOCK.size;
	VALUE = BLOCK.start[index];
	if (index < BLOCK.size) memcpy(BLOCK.start + index,BLOCK.start + index + 1,(BLOCK.size - index) * sizeof(TYPE));
	block_adjustCapacity(TYPE,BLOCK,BLOCK.size);
};

#routine block_removeElementAtStart(#TYPE,BLOCK,VALUE)
{
	if (BLOCK.size == 0) exception_throwBreak("BLOCK: empty");
	--BLOCK.size;
	VALUE = BLOCK.start[0];
	++BLOCK.start;
	++BLOCK.offset;
};

#routine block_removeElementAtEnd(#TYPE,BLOCK,VALUE)
{
	if (BLOCK.size == 0) exception_throwBreak("BLOCK: empty");
	--BLOCK.size;
	VALUE = BLOCK.start[BLOCK.size];
	block_adjustCapacity(TYPE,BLOCK,BLOCK.size);
};

#routine block_swapElements(#TYPE,BLOCK,INDEX1,INDEX2)
{
	#local TYPE value;
	#local UnsignedSize index1;
	#local UnsignedSize index2;
	block_calculateSafeIndex(INDEX1,BLOCK.size,index1);
	block_calculateSafeIndex(INDEX2,BLOCK.size,index2);
	value = BLOCK.start[index1];
	BLOCK.start[index1] = BLOCK.start[index2];
	BLOCK.start[index2] = value;
};

#routine block_reverseElements(#TYPE,BLOCK,START,END)
{
	#local TYPE value;
	#local UnsignedSize start;
	#local UnsignedSize end;
	start = START;
	end = END;
	while (start < end)
	{
		value = BLOCK.start[start];
		BLOCK.start[start] = BLOCK.start[end];
		BLOCK.start[end] = value;
		++start;
		--end;
	};
};

#routine block_reverseElementsAtInterval(#TYPE,BLOCK,INDEX,SIZE)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateInterval(INDEX,SIZE,BLOCK.size,start);
	block_calculateEnd(start,SIZE,end);
	block_reverseElements(TYPE,BLOCK,start,end);
};

#routine block_reverseElementsAtRange(#TYPE,BLOCK,START,END)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(START,END,BLOCK.size,start,end);
	block_reverseElements(TYPE,BLOCK,start,end);
};

#routine block_shuffleElements(#TYPE,BLOCK,START,END)
{
	#local TYPE value;
	#local UnsignedSize index;
	#local UnsignedSize random;
	srand(time(NULL));
	for (index = END; index > START; --index)
	{
		random = START + (rand() % (index + 1));
		value = BLOCK.start[START + index];
		BLOCK.start[START + index] = BLOCK.start[random];
		BLOCK.start[random] = value;
	};
};

#routine block_shuffleElementsAtInterval(#TYPE,BLOCK,INDEX,SIZE)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateInterval(INDEX,SIZE,BLOCK.size,start);
	block_calculateEnd(start,SIZE,end);
	block_shuffleElements(TYPE,BLOCK,start,end);
};

#routine block_shuffleElementsAtRange(#TYPE,BLOCK,START,END)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(START,END,BLOCK.size,start,end);
	block_shuffleElements(TYPE,BLOCK,start,end);
};

#routine block_merge(#TYPE,TARGET_BLOCK,TARGET_INDEX,SOURCE_BLOCK,SOURCE_INDEX,SOURCE_SIZE)
{
	block_adjustCapacity(TYPE,TARGET_BLOCK,TARGET_BLOCK.size + SOURCE_SIZE);
	if (TARGET_INDEX < TARGET_BLOCK.size) memmove(TARGET_BLOCK.start + TARGET_INDEX + SOURCE_SIZE,TARGET_BLOCK.start + TARGET_INDEX,(TARGET_BLOCK.size - TARGET_INDEX) * sizeof(TYPE));
	memcpy(TARGET_BLOCK.start + TARGET_INDEX,SOURCE_BLOCK.start + SOURCE_INDEX,SOURCE_SIZE * sizeof(TYPE));
	TARGET_BLOCK.size += SOURCE_SIZE;
};

#routine block_mergeFromInterval(#TYPE,TARGET_BLOCK,TARGET_INDEX,SOURCE_BLOCK,SOURCE_INDEX,SOURCE_SIZE)
{
	#local UnsignedSize targetIndex;
	#local UnsignedSize sourceIndex;
	block_calculateSafeIndex(TARGET_INDEX,TARGET_BLOCK.size + 1,targetIndex);
	block_calculateInterval(SOURCE_INDEX,SOURCE_SIZE,SOURCE_BLOCK.size,sourceIndex);
	block_merge(TYPE,TARGET_BLOCK,targetIndex,SOURCE_BLOCK,sourceIndex,SOURCE_SIZE);
};

#routine block_mergeFromRange(#TYPE,TARGET_BLOCK,TARGET_INDEX,SOURCE_BLOCK,SOURCE_START,SOURCE_END)
{
	#local UnsignedSize targetIndex;
	#local UnsignedSize sourceIndex;
	#local UnsignedSize size;
	block_calculateSafeIndex(TARGET_INDEX,TARGET_BLOCK.size + 1,targetIndex);
	block_calculateRange(SOURCE_START,SOURCE_END,SOURCE_BLOCK.size,sourceIndex,size);
	block_calculateSize(sourceIndex,size,size);
	block_merge(TYPE,TARGET_BLOCK,targetIndex,SOURCE_BLOCK,sourceIndex,size);
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

#routine block_setSize(#TYPE,BLOCK,NEW_SIZE,OLD_SIZE)
{
	OLD_SIZE = BLOCK.size;
	if (NEW_SIZE != BLOCK.size)
	{
		block_adjustCapacity(TYPE,BLOCK,NEW_SIZE);
		if (NEW_SIZE > BLOCK.size) memset(BLOCK.start + BLOCK.size,0,(NEW_SIZE - BLOCK.size) * sizeof(TYPE));
		BLOCK.size = NEW_SIZE;
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
