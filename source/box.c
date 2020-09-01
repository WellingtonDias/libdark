#template box_define(NAME,TYPE)
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

#routine box_calculateIndex(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	OUTPUT_INDEX = INPUT_INDEX;
	if (OUTPUT_INDEX < 0) OUTPUT_INDEX += SIZE;
};

#macro box_validateIndex(INDEX,START,SIZE)
{
	(INDEX >= (SignedSize) START) && (INDEX < (SignedSize) SIZE)
};

#routine box_calculateSize(START,END,SIZE)
{
	SIZE = END - START + 1;
};

#routine box_calculateEnd(INDEX,SIZE,END)
{
	END = INDEX + SIZE - 1;
};

#routine box_calculateUnsafeIndex(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	#local SignedSize index;
	box_calculateIndex(INPUT_INDEX,SIZE,index);
	if (index < 0) exception_throwBreak("invalid INDEX");
	OUTPUT_INDEX = index;
};

#routine box_calculateSafeIndex(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	#local SignedSize index;
	box_calculateIndex(INPUT_INDEX,SIZE,index);
	if (!box_validateIndex(index,0,SIZE)) exception_throwBreak("invalid INDEX");
	OUTPUT_INDEX = index;
};

#routine box_calculateInterval(INPUT_INDEX,INPUT_SIZE,SIZE,OUTPUT_INDEX)
{
	#local SignedSize index;
	box_calculateIndex(INPUT_INDEX,SIZE,index);
	if (!box_validateIndex(index,0,SIZE)) exception_throwBreak("invalid INTERVAL");
	if (INPUT_SIZE > SIZE) exception_throwBreak("invalid INTERVAL");
	if (index > (SignedSize) SIZE - (SignedSize) INPUT_SIZE) exception_throwBreak("invalid INTERVAL");
	OUTPUT_INDEX = index;
};

#routine box_calculateRange(INPUT_START,INPUT_END,SIZE,OUTPUT_START,OUTPUT_END)
{
	#local SignedSize start;
	#local SignedSize end;
	box_calculateIndex(INPUT_START,SIZE,start);
	if (!box_validateIndex(start,0,SIZE)) exception_throwBreak("invalid RANGE");
	box_calculateIndex(INPUT_END,SIZE,end);
	if (!box_validateIndex(end,start,SIZE)) exception_throwBreak("invalid RANGE");
	OUTPUT_START = start;
	OUTPUT_END = end;
};

#routine box_adjustCapacity(#TYPE,BOX,SIZE)
{
	#local UnsignedSize capacity;
	capacity = 1;
	while (capacity < SIZE) capacity *= 2;
	if (capacity != BOX.capacity)
	{
		#local TYPE* source;
		if (!(source = realloc(BOX.source,capacity * sizeof(TYPE)))) exception_throwBreak("MEMORY: realloc");
		BOX.source = source;
		BOX.start = source + BOX.offset;
		BOX.capacity = capacity;
	};
};

#routine box_update(BOX,SOURCE,SIZE,CAPACITY)
{
	BOX.source = SOURCE;
	BOX.start = SOURCE;
	BOX.offset = 0;
	BOX.size = SIZE;
	BOX.capacity = CAPACITY;
};

#routine box_create(#TYPE,BOX)
{
	#local TYPE* source;
	if (!(source = malloc(sizeof(TYPE)))) exception_throwBreak("MEMORY: malloc");
	box_update(BOX,source,0,1);
};

#routine box_createFromPointer(#TYPE,BOX,POINTER)
{
	box_update(BOX,pointer_getSource(POINTER),pointer_getSize(POINTER),pointer_getSize(POINTER));
};

#routine box_createFromMemory(#TYPE,BOX,RAW_POINTER,SIZE)
{
	#local TYPE* source;
	if (!(source = malloc(SIZE * sizeof(TYPE)))) exception_throwBreak("MEMORY: malloc");
	memcpy(source,RAW_POINTER,SIZE * sizeof(TYPE));
	box_update(BOX,source,SIZE,SIZE);
};

#routine box_createFromMemoryInInterval(#TYPE,BOX,POINTER,INDEX,SIZE)
{
	#local UnsignedSize index;
	box_calculateInterval(INDEX,SIZE,pointer_getSize(POINTER),index);
	box_createFromMemory(TYPE,BOX,pointer_getSource(POINTER) + index,SIZE);
};

#routine box_createFromMemoryInRange(#TYPE,BOX,POINTER,START,END)
{
	#local UnsignedSize index;
	#local UnsignedSize size;
	box_calculateRange(START,END,pointer_getSize(POINTER),index,size)
	box_calculateSize(index,size,size);
	box_createFromMemory(TYPE,BOX,pointer_getSource(POINTER) + index,size);
};

#routine box_createFromCopyInInterval(#TYPE,BOX,SOURCE,INDEX,SIZE)
{
	#local UnsignedSize index;
	box_calculateInterval(INDEX,SIZE,SOURCE.size,index);
	box_createFromMemory(TYPE,BOX,SOURCE.start + index,SIZE);
};

#routine box_createFromCopyInRange(#TYPE,BOX,SOURCE,START,END)
{
	#local UnsignedSize index;
	#local UnsignedSize size;
	box_calculateRange(START,END,SOURCE.size,index,size)
	box_calculateSize(index,size,size);
	box_createFromMemory(TYPE,BOX,SOURCE.start + index,size);
};

#routine box_destroy(BOX)
{
	free(BOX.source);
};

#routine box_trim(#TYPE,BOX)
{
	if (BOX.capacity > BOX.size)
	{
		#local TYPE* source;
		if (BOX.offset > 0)
		{
			memcpy(BOX.source,BOX.start,BOX.size * sizeof(TYPE));
			BOX.offset = 0;
		};
		if (!(source = realloc(BOX.source,BOX.size * sizeof(TYPE)))) exception_throwBreak("MEMORY: realloc");
		BOX.source = source;
		BOX.start = source;
		BOX.capacity = BOX.size;
	};
};

#routine box_clear(#TYPE,BOX)
{
	if (BOX.size > 0)
	{
		#local TYPE* source;
		if (!(source = realloc(BOX.source,sizeof(TYPE)))) exception_throwBreak("MEMORY: realloc");
		box_update(BOX,source,0,1);
	};
};

#macro box_compare(#TYPE,BOX1,BOX2)
{
	(BOX1.size == BOX2.size) && (memcmp(BOX1.start,BOX2.start,BOX1.size * sizeof(TYPE)) == 0)
};

#routine box_map(#TYPE,BOX,#CALLBACK,STRUCT)
{
	for (#local UnsignedSize index; index < BOX.size; ++index) BOX.start[index] = (*CALLBACK)(STRUCT,index,BOX.start[index]);
};

#routine box_filter(#TYPE,BOX,#CALLBACK,STRUCT)
{
	for (#local UnsignedSize index; index < BOX.size; ++index)
	{
		if (!(*CALLBACK)(STRUCT,index,BOX.start[index]))
		{
			--BOX.size;
			if (index < BOX.size) memcpy(BOX.start + index,BOX.start + index + 1,(BOX.size - index) * sizeof(TYPE));
			--index;
		};
	};
	box_adjustCapacity(TYPE,BOX,BOX.size);
};

#routine box_reduce(#TYPE,BOX,#CALLBACK,STRUCT,ACCUMULATOR)
{
	for (#local UnsignedSize index; index < BOX.size; ++index) ACCUMULATOR = (*CALLBACK)(STRUCT,index,BOX.start[index],ACCUMULATOR);
};

#routine box_search(#TYPE,BOX,#CALLBACK,STRUCT,TARGET,FOUND)
{
	#local UnsignedSize index;
	for (; index < BOX.size; ++index)
	{
		if ((*CALLBACK)(STRUCT,index,BOX.start[index],TARGET)) break;
	};
	FOUND = index < BOX.size;
};

#routine box_insertElement(#TYPE,BOX,INDEX,VALUE)
{
	#local UnsignedSize index;
	box_calculateSafeIndex(INDEX,BOX.size + 1,index);
	box_adjustCapacity(TYPE,BOX,BOX.size + 1);
	if (index < BOX.size) memmove(BOX.start + index + 1,BOX.start + index,(BOX.size - index) * sizeof(TYPE));
	BOX.start[index] = VALUE;
	++BOX.size;
};

#routine box_insertElementAtStart(#TYPE,BOX,VALUE)
{
	if (BOX.offset > 0)
	{
		--BOX.start;
		--BOX.offset;
	}
	else
	{
		box_adjustCapacity(TYPE,BOX,BOX.size + 1);
		if (BOX.size > 0) memmove(BOX.start + 1,BOX.start,BOX.size * sizeof(TYPE));
	};
	BOX.start[0] = VALUE;
	++BOX.size;
};

#routine box_insertElementAtEnd(#TYPE,BOX,VALUE)
{
	box_adjustCapacity(TYPE,BOX,BOX.size + 1);
	BOX.start[BOX.size] = VALUE;
	++BOX.size;
};

#routine box_replaceElement(#TYPE,BOX,INDEX,NEW_ELEMENT,OLD_ELEMENT)
{
	#local UnsignedSize index;
	box_calculateSafeIndex(INDEX,BOX.size,index);
	OLD_ELEMENT = BOX.start[index];
	BOX.start[index] = NEW_ELEMENT;
};

#routine box_setElement(#TYPE,BOX,INDEX,NEW_ELEMENT,OLD_ELEMENT)
{
	#local UnsignedSize index;
	box_calculateUnsafeIndex(INDEX,BOX.size,index);
	if (index >= BOX.size)
	{
		box_adjustCapacity(TYPE,BOX,index + 1);
		if (index > BOX.size) memset(BOX.start + BOX.size,0,(index - BOX.size) * sizeof(TYPE));
		BOX.size = index + 1;
		OLD_ELEMENT = (TYPE) 0;
	}
	else OLD_ELEMENT = BOX.start[index];
	BOX.start[index] = NEW_ELEMENT;
};

#routine box_getElement(#TYPE,BOX,INDEX,VALUE)
{
	#local UnsignedSize index;
	box_calculateSafeIndex(INDEX,BOX.size,index);
	VALUE = BOX.start[index];
};

#routine box_getElementAtStart(#TYPE,BOX,VALUE)
{
	if (BOX.size == 0) exception_throwBreak("BOX: empty");
	VALUE = BOX.start[0];
};

#routine box_getElementAtEnd(#TYPE,BOX,VALUE)
{
	if (BOX.size == 0) exception_throwBreak("BOX: empty");
	VALUE = BOX.start[BOX.size - 1];
};

#routine box_eraseElement(#TYPE,BOX,INDEX,VALUE)
{
	#local UnsignedSize index;
	box_calculateSafeIndex(INDEX,BOX.size,index);
	VALUE = BOX.start[index];
	BOX.start[index] = (TYPE) 0;
};

#routine box_removeElement(#TYPE,BOX,INDEX,VALUE)
{
	#local UnsignedSize index;
	box_calculateSafeIndex(INDEX,BOX.size,index);
	--BOX.size;
	VALUE = BOX.start[index];
	if (index < BOX.size) memcpy(BOX.start + index,BOX.start + index + 1,(BOX.size - index) * sizeof(TYPE));
	box_adjustCapacity(TYPE,BOX,BOX.size);
};

#routine box_removeElementAtStart(#TYPE,BOX,VALUE)
{
	if (BOX.size == 0) exception_throwBreak("BOX: empty");
	--BOX.size;
	VALUE = BOX.start[0];
	++BOX.start;
	++BOX.offset;
};

#routine box_removeElementAtEnd(#TYPE,BOX,VALUE)
{
	if (BOX.size == 0) exception_throwBreak("BOX: empty");
	--BOX.size;
	VALUE = BOX.start[BOX.size];
	box_adjustCapacity(TYPE,BOX,BOX.size);
};

#routine box_swapElements(#TYPE,BOX,INDEX1,INDEX2)
{
	#local TYPE value;
	#local UnsignedSize index1;
	#local UnsignedSize index2;
	box_calculateSafeIndex(INDEX1,BOX.size,index1);
	box_calculateSafeIndex(INDEX2,BOX.size,index2);
	value = BOX.start[index1];
	BOX.start[index1] = BOX.start[index2];
	BOX.start[index2] = value;
};

#routine box_reverseElements(#TYPE,BOX,START,END)
{
	#local TYPE value;
	#local UnsignedSize start;
	#local UnsignedSize end;
	start = START;
	end = END;
	while (start < end)
	{
		value = BOX.start[start];
		BOX.start[start] = BOX.start[end];
		BOX.start[end] = value;
		++start;
		--end;
	};
};

#routine box_reverseElementsInInterval(#TYPE,BOX,INDEX,SIZE)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	box_calculateInterval(INDEX,SIZE,BOX.size,start);
	box_calculateEnd(start,SIZE,end);
	box_reverseElements(TYPE,BOX,start,end);
};

#routine box_reverseElementsInRange(#TYPE,BOX,START,END)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	box_calculateRange(START,END,BOX.size,start,end);
	box_reverseElements(TYPE,BOX,start,end);
};

#routine box_shuffleElements(#TYPE,BOX,START,END)
{
	#local TYPE value;
	#local UnsignedSize index;
	#local UnsignedSize random;
	srand(time(NULL));
	for (index = END; index > START; --index)
	{
		random = START + (rand() % (index + 1));
		value = BOX.start[START + index];
		BOX.start[START + index] = BOX.start[random];
		BOX.start[random] = value;
	};
};

#routine box_shuffleElementsInInterval(#TYPE,BOX,INDEX,SIZE)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	box_calculateInterval(INDEX,SIZE,BOX.size,start);
	box_calculateEnd(start,SIZE,end);
	box_shuffleElements(TYPE,BOX,start,end);
};

#routine box_shuffleElementsInRange(#TYPE,BOX,START,END)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	box_calculateRange(START,END,BOX.size,start,end);
	box_shuffleElements(TYPE,BOX,start,end);
};

#routine box_merge(#TYPE,TARGET_BOX,TARGET_INDEX,SOURCE_BOX,SOURCE_INDEX,SOURCE_SIZE)
{
	box_adjustCapacity(TYPE,TARGET_BOX,TARGET_BOX.size + SOURCE_SIZE);
	if (TARGET_INDEX < TARGET_BOX.size) memmove(TARGET_BOX.start + TARGET_INDEX + SOURCE_SIZE,TARGET_BOX.start + TARGET_INDEX,(TARGET_BOX.size - TARGET_INDEX) * sizeof(TYPE));
	memcpy(TARGET_BOX.start + TARGET_INDEX,SOURCE_BOX.start + SOURCE_INDEX,SOURCE_SIZE * sizeof(TYPE));
	TARGET_BOX.size += SOURCE_SIZE;
};

#routine box_mergeFromInterval(#TYPE,TARGET_BOX,TARGET_INDEX,SOURCE_BOX,SOURCE_INDEX,SOURCE_SIZE)
{
	#local UnsignedSize targetIndex;
	#local UnsignedSize sourceIndex;
	box_calculateSafeIndex(TARGET_INDEX,TARGET_BOX.size + 1,targetIndex);
	box_calculateInterval(SOURCE_INDEX,SOURCE_SIZE,SOURCE_BOX.size,sourceIndex);
	box_merge(TYPE,TARGET_BOX,targetIndex,SOURCE_BOX,sourceIndex,SOURCE_SIZE);
};

#routine box_mergeFromRange(#TYPE,TARGET_BOX,TARGET_INDEX,SOURCE_BOX,SOURCE_START,SOURCE_END)
{
	#local UnsignedSize targetIndex;
	#local UnsignedSize sourceIndex;
	#local UnsignedSize size;
	box_calculateSafeIndex(TARGET_INDEX,TARGET_BOX.size + 1,targetIndex);
	box_calculateRange(SOURCE_START,SOURCE_END,SOURCE_BOX.size,sourceIndex,size);
	box_calculateSize(sourceIndex,size,size);
	box_merge(TYPE,TARGET_BOX,targetIndex,SOURCE_BOX,sourceIndex,size);
};

#macro box_getSource(BOX)
{
	BOX.source
};

#macro box_getStart(BOX)
{
	BOX.start
};

#macro box_getOffset(BOX)
{
	BOX.offset
};

#routine box_setSize(#TYPE,BOX,NEW_SIZE,OLD_SIZE)
{
	OLD_SIZE = BOX.size;
	if (NEW_SIZE != BOX.size)
	{
		box_adjustCapacity(TYPE,BOX,NEW_SIZE);
		if (NEW_SIZE > BOX.size) memset(BOX.start + BOX.size,0,(NEW_SIZE - BOX.size) * sizeof(TYPE));
		BOX.size = NEW_SIZE;
	};
};

#macro box_getSize(BOX)
{
	BOX.size
};

#macro box_isEmpty(BOX)
{
	BOX.size == 0
};

#macro box_isNotEmpty(BOX)
{
	BOX.size != 0
};

#macro box_getCapacity(BOX)
{
	BOX.capacity
};
