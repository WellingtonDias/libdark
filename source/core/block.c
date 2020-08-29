#template block_define(NAME,TYPE)
{
	typedef struct
	{
		TYPE    *source;
		TYPE    *start;
		DKusize offset;
		DKusize size;
		DKusize capacity;
	} NAME;
};

#macro block_validateIndex(OUTPUT_INDEX,START_INDEX,SIZE)
{
	(OUTPUT_INDEX >= (DKssize) START_INDEX) && (OUTPUT_INDEX < (DKssize) SIZE)
};

#routine block_calculateIndex(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	OUTPUT_INDEX = INPUT_INDEX;
	if (OUTPUT_INDEX < 0) OUTPUT_INDEX += SIZE;
};

#routine block_calculateUnsafeIndex(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	#local DKssize index;
	block_calculateIndex(INPUT_INDEX,SIZE,index);
	if (index < 0) error_throwBreak("invalid INDEX");
	OUTPUT_INDEX = index;
};

#routine block_calculateSafeIndex(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	#local DKssize index;
	block_calculateIndex(INPUT_INDEX,SIZE,index);
	if (!block_validateIndex(index,0,SIZE)) error_throwBreak("invalid INDEX");
	OUTPUT_INDEX = index;
};

#routine block_calculateRange(INPUT_START,INPUT_END,INPUT_SIZE,OUTPUT_START,OUTPUT_END)
{
	#local DKssize start;
	#local DKssize end;
	block_calculateIndex(START_INDEX,INPUT_SIZE,start);
	if (!block_validateIndex(start,0,INPUT_SIZE)) error_throwBreak("invalid RANGE");
	block_calculateIndex(END_INDEX,INPUT_SIZE,end);
	if (!block_validateIndex(end,start,INPUT_SIZE)) error_throwBreak("invalid RANGE");
	OUTPUT_START = start;
	OUTPUT_END = end;
};

#macro block_calculateEnd(INDEX,SIZE)
{
	INDEX + SIZE - 1;
};

#macro block_calculateSize(START_INDEX,END_INDEX)
{
	END_INDEX - START_INDEX + 1;
};

#routine block_calculateCapacity(SIZE,CAPACITY)
{
	CAPACITY = 1;
	while (CAPACITY < SIZE) CAPACITY *= 2;
};

#routine block_adjustCapacity(#TYPE,BLOCK,SIZE)
{
	#local DKusize capacity;
	block_calculateCapacity(BLOCK.offset + SIZE,capacity);
	if (capacity != BLOCK.capacity)
	{
		#local TYPE *source;
		if (!(source = realloc(BLOCK.source,capacity * sizeof(TYPE)))) error_throwBreak("MEMORY: realloc");
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
	#local TYPE *source;
	if (!(source = malloc(sizeof(TYPE)))) error_throwBreak("MEMORY: malloc");
	block_update(BLOCK,source,0,1);
};

#routine block_createFromPointer(#TYPE,BLOCK,ADDRESS,SIZE)
{
	if (ADDRESS == NULL) error_throwBreak("invalid ADDRESS");
	if (SIZE == 0) error_throwBreak("invalid SIZE");
	block_update(BLOCK,ADDRESS,SIZE,SIZE);
};

// #routine block_createFromMemory(#TYPE,BLOCK,ADDRESS,SIZE,START,END)
// {
// 	#local TYPE *source;
// 	#local DKusize index;
// 	#local DKusize size;
// 	if (ADDRESS == NULL) error_throwBreak("invalid ADDRESS");
// 	if (SIZE == 0) error_throwBreak("invalid SIZE");
// 	block_calculateRange(START,END,SIZE,index,size);
// 	size = block_calculateSize(index,size);
// 	if (!(source = malloc(size * sizeof(TYPE)))) error_throwBreak("MEMORY: malloc");
// 	memcpy(source,ADDRESS + index,size * sizeof(TYPE));
// 	block_update(BLOCK,source,size,size);
// };

#routine block_destroy(BLOCK)
{
	free(BLOCK.source);
};

// #routine block_merge(#TYPE,TARGET_BLOCK,TARGET_INDEX,SOURCE_BLOCK,SOURCE_INDEX,SOURCE_SIZE)
// {
// 	block_adjustCapacity(TYPE,TARGET_BLOCK,TARGET_BLOCK.size + SOURCE_SIZE);
// 	if (TARGET_INDEX < TARGET_BLOCK.size) memmove(TARGET_BLOCK.start + TARGET_INDEX + SOURCE_SIZE,TARGET_BLOCK.start + TARGET_INDEX,(TARGET_BLOCK.size - TARGET_INDEX) * sizeof(TYPE));
// 	memcpy(TARGET_BLOCK.start + TARGET_INDEX,SOURCE_BLOCK.start + sourceIndex,SOURCE_SIZE * sizeof(TYPE));
// 	TARGET_BLOCK.size += SOURCE_SIZE;
// };

// #routine block_mergeAtIndex(#TYPE,TARGET_BLOCK,TARGET_INDEX,SOURCE_BLOCK,SOURCE_INDEX,SOURCE_SIZE)
// {
// 	#local DKusize targetIndex;
// 	#local DKusize sourceIndex;
// 	#local DKusize size;
// 	block_calculateSafeIndex(TARGET_INDEX,TARGET_BLOCK.size + 1,targetIndex);
// 	if (SOURCE_SIZE > SOURCE_BLOCK.size) error_throwBreak("invalid SOURCE_SIZE");
// 	block_calculateSafeIndex(SOURCE_INDEX,SOURCE_BLOCK.size,sourceIndex);
// 	if (sourceIndex > SOURCE_BLOCK.size - SIZE) error_throwBreak("invalid SOURCE_INDEX");
// };

// #routine block_mergeAtRange(#TYPE,TARGET_BLOCK,TARGET_INDEX,SOURCE_BLOCK,SOURCE_START,SOURCE_END)
// {
// 	#local DKusize targetIndex;
// 	#local DKusize sourceIndex;
// 	#local DKusize size;
// 	block_calculateSafeIndex(TARGET_INDEX,TARGET_BLOCK.size + 1,targetIndex);
// 	block_calculateRange(SOURCE_START,SOURCE_END,SOURCE_BLOCK.size,sourceIndex,size);
// 	size = block_calculateSize(sourceIndex,size);
// };

#routine block_trim(#TYPE,BLOCK)
{
	if (BLOCK.capacity > BLOCK.size)
	{
		#local TYPE *source;
		if (BLOCK.offset > 0)
		{
			memcpy(BLOCK.source,BLOCK.start,BLOCK.size * sizeof(TYPE));
			BLOCK.offset = 0;
		};
		if (!(source = realloc(BLOCK.source,BLOCK.size * sizeof(TYPE)))) error_throwBreak("MEMORY: realloc");
		BLOCK.source = source;
		BLOCK.start = source;
		BLOCK.capacity = BLOCK.size;
	};
};

#routine block_clear(#TYPE,BLOCK)
{
	if (BLOCK.size > 0)
	{
		#local TYPE *source;
		if (!(source = realloc(BLOCK.source,sizeof(TYPE)))) error_throwBreak("MEMORY: realloc");
		block_update(BLOCK,source,0,1);
	};
};

#macro block_compare(#TYPE,BLOCK1,BLOCK2)
{
	(BLOCK1.size == BLOCK2.size) && (memcmp(BLOCK1.start,BLOCK2.start,BLOCK1.size * sizeof(TYPE)) == 0)
};

#routine block_insertElement(#TYPE,BLOCK,INDEX,VALUE)
{
	#local DKusize index;
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
	#local DKusize index;
	block_calculateSafeIndex(INDEX,BLOCK.size,index);
	OLD_ELEMENT = BLOCK.start[index];
	BLOCK.start[index] = NEW_ELEMENT;
};

#routine block_setElement(#TYPE,BLOCK,INDEX,NEW_ELEMENT,OLD_ELEMENT)
{
	#local DKusize index;
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
	#local DKusize index;
	block_calculateSafeIndex(INDEX,BLOCK.size,index);
	VALUE = BLOCK.start[index];
};

#routine block_getElementAtStart(#TYPE,BLOCK,VALUE)
{
	if (BLOCK.size == 0) error_throwBreak("BLOCK: empty");
	VALUE = BLOCK.start[0];
};

#routine block_getElementAtEnd(#TYPE,BLOCK,VALUE)
{
	if (BLOCK.size == 0) error_throwBreak("BLOCK: empty");
	VALUE = BLOCK.start[BLOCK.size - 1];
};

#routine block_eraseElement(#TYPE,BLOCK,INDEX,VALUE)
{
	#local DKusize index;
	block_calculateSafeIndex(INDEX,BLOCK.size,index);
	VALUE = BLOCK.start[index];
	BLOCK.start[index] = (TYPE) 0;
};

#routine block_removeElement(#TYPE,BLOCK,INDEX,VALUE)
{
	#local DKusize index;
	block_calculateSafeIndex(INDEX,BLOCK.size,index);
	--BLOCK.size;
	VALUE = BLOCK.start[index];
	if (index < BLOCK.size) memcpy(BLOCK.start + index,BLOCK.start + index + 1,(BLOCK.size - index) * sizeof(TYPE));
	block_adjustCapacity(TYPE,BLOCK,BLOCK.size);
};

#routine block_removeElementAtStart(#TYPE,BLOCK,VALUE)
{
	if (BLOCK.size == 0) error_throwBreak("BLOCK: empty");
	--BLOCK.size;
	VALUE = BLOCK.start[0];
	++BLOCK.start;
	++BLOCK.offset;
};

#routine block_removeElementAtEnd(#TYPE,BLOCK,VALUE)
{
	if (BLOCK.size == 0) error_throwBreak("BLOCK: empty");
	--BLOCK.size;
	VALUE = BLOCK.start[BLOCK.size];
	block_adjustCapacity(TYPE,BLOCK,BLOCK.size);
};

#routine block_swapElements(#TYPE,BLOCK,INDEX1,INDEX2)
{
	#local TYPE value;
	#local DKusize index1;
	#local DKusize index2;
	block_calculateSafeIndex(INDEX,BLOCK.size,index1);
	block_calculateSafeIndex(INDEX,BLOCK.size,index2);
	value = BLOCK.start[index1];
	BLOCK.start[index1] = BLOCK.start[index2];
	BLOCK.start[index2] = value;
};

#routine block_reverseElements(#TYPE,BLOCK,START,END)
{
	#local TYPE value;
	#local DKusize start;
	#local DKusize end;
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

#routine block_reverseSliceAtInterval(#TYPE,BLOCK,INDEX,SIZE)
{
	#local DKusize start;
	#local DKusize end;
	if (SIZE > BLOCK.size) error_throwBreak("invalid SIZE");
	block_calculateSafeIndex(INDEX,BLOCK.size,start);
	if (start > BLOCK.size - SIZE) error_throwBreak("invalid INDEX");
	end = block_calculateEnd(INDEX,SIZE);
	block_reverseSlice(TYPE,BLOCK,start,end);
};

#routine block_reverseSliceAtRange(#TYPE,BLOCK,START,END)
{
	#local DKusize start;
	#local DKusize end;
	block_calculateRange(START,END,BLOCK.size,start,end);
	block_reverseSlice(TYPE,BLOCK,start,end);
};

#routine block_shuffleElements(#TYPE,BLOCK,START,END)
{
	#local TYPE value;
	#local DKusize index;
	#local DKusize random;
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
	#local DKusize start;
	#local DKusize end;
	if (SIZE > BLOCK.size) error_throwBreak("invalid SIZE");
	block_calculateSafeIndex(INDEX,BLOCK.size,start);
	if (start > BLOCK.size - SIZE) error_throwBreak("invalid INDEX");
	end = block_calculateEnd(INDEX,SIZE);
	block_shuffleElements(TYPE,BLOCK,start,end);
};

#routine block_shuffleElementsAtRange(#TYPE,BLOCK,START,END)
{
	#local DKusize start;
	#local DKusize end;
	block_calculateRange(START,END,BLOCK.size,start,end);
	block_shuffleElements(TYPE,BLOCK,start,end);
};

#routine block_map(#TYPE,BLOCK,#CALLBACK,STRUCT)
{
	for (#local DKusize index; index < BLOCK.size; ++index) BLOCK.start[index] = (*CALLBACK)(STRUCT,index,BLOCK.start[index]);
};

#routine block_filter(#TYPE,BLOCK,#CALLBACK,STRUCT)
{
	for (#local DKusize index; index < BLOCK.size; ++index)
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
	for (#local DKusize index; index < BLOCK.size; ++index) ACCUMULATOR = (*CALLBACK)(STRUCT,index,BLOCK.start[index],ACCUMULATOR);
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
