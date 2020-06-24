#template block_define(NAME,TYPE)
{
	typedef struct
	{
		TYPE *source;
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
	BLOCK.size = SIZE;
	BLOCK.capacity = CAPACITY;
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
	block_insert(BLOCK,TYPE,destinationIndex,SOURCE.source + sourceIndex,size);
};

#macro block_clear(BLOCK,#TYPE)
{
	#local TYPE *source;
	if (!(source = realloc(BLOCK.source,sizeof(TYPE)))) error_throw("MEMORY: realloc");
	block_update(BLOCK,source,0,1);
};

#alias block_compare(BLOCK1,BLOCK2,#TYPE)
{
	(BLOCK1.size == BLOCK2.size) && (memcmp(BLOCK1.source,BLOCK2.source,BLOCK1.size * sizeof(TYPE)) == 0)
};

#macro block_increase(BLOCK,#TYPE,SIZE)
{
	if (SIZE > BLOCK.capacity)
	{
		#local TYPE *source;
		#local DKusize capacity;
		block_increaseCapacity(BLOCK.capacity,SIZE,capacity);
		if (!(source = realloc(BLOCK.source,capacity * sizeof(TYPE)))) error_throw("MEMORY: realloc");
		BLOCK.source = source;
		BLOCK.capacity = capacity;
	};
};

#macro block_insert(BLOCK,#TYPE,INDEX,SOURCE,SIZE)
{
	#local DKusize size;
	size = ((INDEX > BLOCK.size)? INDEX : BLOCK.size) + SIZE;
	block_increase(BLOCK,TYPE,size);
	if (INDEX > BLOCK.size) memset(BLOCK.source + BLOCK.size,0,(INDEX - BLOCK.size) * sizeof(TYPE));
	else memmove(BLOCK.source + INDEX + SIZE,BLOCK.source + INDEX,(BLOCK.size - INDEX) * sizeof(TYPE));
	memcpy(BLOCK.source + INDEX,SOURCE,SIZE * sizeof(TYPE));
	BLOCK.size = size;
};

#macro block_write(BLOCK,#TYPE,INDEX,SOURCE,SIZE)
{
	if (INDEX + SIZE > BLOCK.size)
	{
		block_increase(BLOCK,TYPE,INDEX + SIZE);
		if (INDEX > BLOCK.size) memset(BLOCK.source + BLOCK.size,0,(INDEX - BLOCK.size) * sizeof(TYPE));
		BLOCK.size = INDEX + SIZE;
	};
	memcpy(BLOCK.source + INDEX,SOURCE,SIZE * sizeof(TYPE));
};

#macro block_erase(BLOCK,#TYPE,INDEX,SIZE)
{
	if (SIZE > BLOCK.size) error_throw("invalid SIZE");
	if ((DKssize) INDEX > (DKssize) BLOCK.size - (DKssize) SIZE) error_throw("invalid INDEX");
	memset(BLOCK.source + INDEX,0,SIZE * sizeof(TYPE));
};

#macro block_decrease(BLOCK,#TYPE,SIZE)
{
	#local DKusize capacity;
	block_decreaseCapacity(BLOCK.capacity,SIZE,capacity);
	if (capacity < BLOCK.capacity)
	{
		#local TYPE *source;
		if ((source = realloc(BLOCK.source,capacity * sizeof(TYPE))))
		{
			BLOCK.source = source;
			BLOCK.capacity = capacity;
		};
	};
};

#macro block_remove(BLOCK,#TYPE,INDEX,SIZE)
{
	if (SIZE > BLOCK.size) error_throw("invalid SIZE");
	if ((DKssize) INDEX > (DKssize) BLOCK.size - (DKssize) SIZE) error_throw("invalid INDEX");
	memcpy(BLOCK.source + INDEX,BLOCK.source + INDEX + SIZE,(BLOCK.size - SIZE - INDEX) * sizeof(TYPE));
	BLOCK.size -= SIZE;
	block_decrease(BLOCK,TYPE,BLOCK.size);
};

#alias block_getSource(BLOCK)
{
	BLOCK.source
};

#macro block_setSize(BLOCK,#TYPE,SIZE)
{
	#local TYPE *source;
	#local DKusize capacity;
	block_calculateCapacity(SIZE,capacity);
	if (!(source = realloc(BLOCK.source,capacity * sizeof(TYPE)))) error_throwReturn("MEMORY: realloc");
	if (SIZE > BLOCK.size) memset(BLOCK.source + BLOCK.size,0,(SIZE - BLOCK.size) * sizeof(TYPE));
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
