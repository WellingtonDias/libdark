#template block_define(NAME,TYPE)
{
	typedef struct
	{
		TYPE *source;
		TYPE *start;
		DKusize offset;
		DKusize size;
		DKusize capacity;
	} NAME;
};

#macro block_calculateIndex(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	OUTPUT_INDEX = INPUT_INDEX;
	if (INPUT_INDEX < 0) OUTPUT_INDEX += SIZE;
};

#alias block_validateIndex(OUTPUT_INDEX,MINIMUM_INDEX,SIZE)
{
	(OUTPUT_INDEX >= (DKssize) MINIMUM_INDEX) && (OUTPUT_INDEX < (DKssize) SIZE)
};

#macro block_calculateUnsafePosition(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	#local DKssize index;
	block_calculateIndex((DKssize) INPUT_INDEX,SIZE,index);
	if (index < 0) error_set("invalid INDEX");
	OUTPUT_INDEX = index;
};

#macro block_calculateSafePosition(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	#local DKssize index;
	block_calculateIndex((DKssize) INPUT_INDEX,SIZE,index);
	if (!block_validateIndex(index,0,SIZE)) error_set("invalid INDEX");
	OUTPUT_INDEX = index;
};

#macro block_calculateRange(START_INDEX,END_INDEX,INPUT_SIZE,OUTPUT_INDEX,OUTPUT_SIZE)
{
	#local DKssize start;
	#local DKssize end;
	block_calculateIndex((DKssize) START_INDEX,INPUT_SIZE,start);
	if (!block_validateIndex(start,0,INPUT_SIZE)) error_set("invalid START");
	block_calculateIndex((DKssize) END_INDEX,INPUT_SIZE,end);
	if (!block_validateIndex(end,start,INPUT_SIZE)) error_set("invalid END");
	OUTPUT_INDEX = start;
	OUTPUT_SIZE = end - start + 1;
};

#macro block_calculateCapacity(SIZE,CAPACITY)
{
	CAPACITY = 1;
	while (CAPACITY < SIZE) CAPACITY *= 2;
};

#macro block_increaseCapacity(INPUT_CAPACITY,SIZE,OUTPUT_CAPACITY)
{
	OUTPUT_CAPACITY = INPUT_CAPACITY;
	while (OUTPUT_CAPACITY < SIZE) OUTPUT_CAPACITY *= 2;
};

#macro block_decreaseCapacity(INPUT_CAPACITY,SIZE,OUTPUT_CAPACITY)
{
	OUTPUT_CAPACITY = INPUT_CAPACITY;
	while ((OUTPUT_CAPACITY > 1) && (OUTPUT_CAPACITY / 2 >= SIZE)) OUTPUT_CAPACITY /= 2;
};

#macro block_update(BLOCK,SOURCE,SIZE,CAPACITY)
{
	BLOCK.source = SOURCE;
	BLOCK.start = SOURCE;
	BLOCK.offset = 0;
	BLOCK.size = SIZE;
	BLOCK.capacity = CAPACITY;
};

#macro block_trim(BLOCK,#TYPE)
{
	if (BLOCK.offset > 0)
	{
		memcpy(BLOCK.source,BLOCK.start,BLOCK.size * sizeof(TYPE));
		BLOCK.start = BLOCK.source;
		BLOCK.offset = 0;
	};
};

#macro block_increase(BLOCK,#TYPE,SIZE)
{
	if (BLOCK.offset + SIZE > BLOCK.capacity)
	{
		#local TYPE *source;
		#local DKusize capacity;
		block_increaseCapacity(BLOCK.capacity,BLOCK.offset + SIZE,capacity);
		if (!(source = realloc(BLOCK.source,capacity * sizeof(TYPE)))) error_set("MEMORY: realloc");
		BLOCK.source = source;
		BLOCK.start = source + BLOCK.offset;
		BLOCK.capacity = capacity;
	};
};

#macro block_decrease(BLOCK,#TYPE,SIZE)
{
	#local DKusize capacity;
	block_trim(BLOCK,TYPE);
	block_decreaseCapacity(BLOCK.capacity,SIZE,capacity);
	if (capacity < BLOCK.capacity)
	{
		#local TYPE *source;
		if ((source = realloc(BLOCK.source,capacity * sizeof(TYPE))))
		{
			BLOCK.source = source;
			BLOCK.start = source;
			BLOCK.capacity = capacity;
		};
	};
};

#macro block_createFromNothing(BLOCK,#TYPE)
{
	#local TYPE *source;
	if (!(source = malloc(sizeof(TYPE)))) error_throwReturn("MEMORY: malloc");
	block_update(BLOCK,source,0,1);
};

#macro block_createFromMemory(BLOCK,#TYPE,SOURCE,SIZE,START,END)
{
	#local TYPE *source;
	#local DKusize index;
	#local DKusize size;
	#local DKusize capacity;
	block_calculateRange(START,END,SIZE,index,size);
	error_bypassReturn();
	block_calculateCapacity(size,capacity);
	if (!(source = malloc(capacity * sizeof(TYPE)))) error_throwReturn("MEMORY: malloc");
	memcpy(source,SOURCE + index,size * sizeof(TYPE));
	block_update(BLOCK,source,size,capacity);
};

#macro block_destroy(BLOCK)
{
	free(BLOCK.source);
};

#macro block_merge(BLOCK,#TYPE,INDEX,SOURCE,START,END)
{
	#local DKusize destinationIndex;
	#local DKusize sourceIndex;
	#local DKusize size;
	block_calculateSafePosition(INDEX,BLOCK.size + 1,destinationIndex);
	error_bypass();
	block_calculateRange(START,END,SOURCE.size,sourceIndex,size);
	error_bypass();
	block_increase(BLOCK,TYPE,BLOCK.size + size);
	error_bypass();
	memmove(BLOCK.start + destinationIndex + size,BLOCK.start + destinationIndex,(BLOCK.size - destinationIndex) * sizeof(TYPE));
	memcpy(BLOCK.start + destinationIndex,SOURCE.start + sourceIndex,size * sizeof(TYPE));
	BLOCK.size += size;
};

#macro block_clear(BLOCK,#TYPE)
{
	#local TYPE *source;
	if (!(source = realloc(BLOCK.source,sizeof(TYPE)))) error_throw("MEMORY: realloc");
	block_update(BLOCK,source,0,1);
};

#alias block_compare(BLOCK1,BLOCK2,#TYPE)
{
	(BLOCK1.size == BLOCK2.size) && (memcmp(BLOCK1.start,BLOCK2.start,BLOCK1.size * sizeof(TYPE)) == 0)
};

#alias block_getSource(BLOCK)
{
	BLOCK.start
};

#macro block_setSize(BLOCK,#TYPE,SIZE)
{
	#local TYPE *source;
	#local DKusize capacity;
	block_trim(BLOCK,TYPE);
	block_calculateCapacity(SIZE,capacity);
	if (!(source = realloc(BLOCK.source,capacity * sizeof(TYPE)))) error_throwReturn("MEMORY: realloc");
	if (SIZE > BLOCK.size) memset(source + BLOCK.size,0,(SIZE - BLOCK.size) * sizeof(TYPE));
	block_update(BLOCK,source,SIZE,capacity);
};

#alias block_getSize(BLOCK)
{
	BLOCK.size
};

#alias block_isEmpty(BLOCK)
{
	BLOCK.size == 0
};
