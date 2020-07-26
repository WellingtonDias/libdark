#template block_define(NAME,TYPE)
{
	typedef struct
	{
		TYPE *source;
		TYPE *start;
		DKusize offset;
		DKusize length;
		DKusize capacity;
	} NAME;
};

#macro block_calculateIndex(INPUT_INDEX,LENGTH,OUTPUT_INDEX)
{
	OUTPUT_INDEX = INPUT_INDEX;
	if (OUTPUT_INDEX < 0) OUTPUT_INDEX += LENGTH;
};

#alias block_validateIndex(OUTPUT_INDEX,MINIMUM_INDEX,LENGTH)
{
	(OUTPUT_INDEX >= (DKssize) MINIMUM_INDEX) && (OUTPUT_INDEX < (DKssize) LENGTH)
};

#macro block_calculateUnsafePosition(INPUT_INDEX,LENGTH,OUTPUT_INDEX)
{
	#local DKssize index;
	block_calculateIndex((DKssize) INPUT_INDEX,LENGTH,index);
	if (index < 0) error_throwBreak("invalid INDEX");
	OUTPUT_INDEX = index;
};

#macro block_calculateSafePosition(INPUT_INDEX,LENGTH,OUTPUT_INDEX)
{
	#local DKssize index;
	block_calculateIndex((DKssize) INPUT_INDEX,LENGTH,index);
	if (!block_validateIndex(index,0,LENGTH)) error_throwBreak("invalid INDEX");
	OUTPUT_INDEX = index;
};

#macro block_calculateRange(START_INDEX,END_INDEX,INPUT_LENGTH,OUTPUT_INDEX,OUTPUT_LENGTH)
{
	#local DKssize start;
	#local DKssize end;
	block_calculateIndex((DKssize) START_INDEX,INPUT_LENGTH,start);
	if (!block_validateIndex(start,0,INPUT_LENGTH)) error_throwBreak("invalid START");
	block_calculateIndex((DKssize) END_INDEX,INPUT_LENGTH,end);
	if (!block_validateIndex(end,start,INPUT_LENGTH)) error_throwBreak("invalid END");
	OUTPUT_INDEX = start;
	OUTPUT_LENGTH = end - start + 1;
};

#macro block_calculateCapacity(LENGTH,CAPACITY)
{
	CAPACITY = 1;
	while (CAPACITY < LENGTH) CAPACITY *= 2;
};

#macro block_increaseCapacity(INPUT_CAPACITY,LENGTH,OUTPUT_CAPACITY)
{
	OUTPUT_CAPACITY = INPUT_CAPACITY;
	while (OUTPUT_CAPACITY < LENGTH) OUTPUT_CAPACITY *= 2;
};

#macro block_decreaseCapacity(INPUT_CAPACITY,LENGTH,OUTPUT_CAPACITY)
{
	OUTPUT_CAPACITY = INPUT_CAPACITY;
	while ((OUTPUT_CAPACITY > 1) && (OUTPUT_CAPACITY / 2 >= LENGTH)) OUTPUT_CAPACITY /= 2;
};

#macro block_update(BLOCK,SOURCE,LENGTH,CAPACITY)
{
	BLOCK.source = SOURCE;
	BLOCK.start = SOURCE;
	BLOCK.offset = 0;
	BLOCK.length = LENGTH;
	BLOCK.capacity = CAPACITY;
};

#macro block_trim(BLOCK,#TYPE)
{
	if (BLOCK.offset > 0)
	{
		memcpy(BLOCK.source,BLOCK.start,BLOCK.length * sizeof(TYPE));
		BLOCK.start = BLOCK.source;
		BLOCK.offset = 0;
	};
};

#macro block_increase(BLOCK,#TYPE,LENGTH)
{
	if (BLOCK.offset + LENGTH > BLOCK.capacity)
	{
		#local TYPE *source;
		#local DKusize capacity;
		block_increaseCapacity(BLOCK.capacity,BLOCK.offset + LENGTH,capacity);
		if (!(source = realloc(BLOCK.source,capacity * sizeof(TYPE)))) error_throwBreak("MEMORY: realloc");
		BLOCK.source = source;
		BLOCK.start = source + BLOCK.offset;
		BLOCK.capacity = capacity;
	};
};

#macro block_decrease(BLOCK,#TYPE,LENGTH)
{
	#local DKusize capacity;
	block_trim(BLOCK,TYPE);
	block_decreaseCapacity(BLOCK.capacity,LENGTH,capacity);
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

#macro block_createFromMemory(BLOCK,#TYPE,SOURCE,LENGTH,START,END)
{
	#local TYPE *source;
	#local DKusize index;
	#local DKusize length;
	#local DKusize capacity;
	block_calculateRange(START,END,LENGTH,index,length);
	error_bypassReturn();
	block_calculateCapacity(length,capacity);
	if (!(source = malloc(capacity * sizeof(TYPE)))) error_throwReturn("MEMORY: malloc");
	memcpy(source,SOURCE + index,length * sizeof(TYPE));
	block_update(BLOCK,source,length,capacity);
};

#macro block_destroy(BLOCK)
{
	free(BLOCK.source);
};

#macro block_merge(BLOCK,#TYPE,INDEX,SOURCE,START,END)
{
	#local DKusize destinationIndex;
	#local DKusize sourceIndex;
	#local DKusize length;
	block_calculateSafePosition(INDEX,BLOCK.length + 1,destinationIndex);
	error_bypassExit();
	block_calculateRange(START,END,SOURCE.length,sourceIndex,length);
	error_bypassExit();
	block_increase(BLOCK,TYPE,BLOCK.length + length);
	error_bypassExit();
	memmove(BLOCK.start + destinationIndex + length,BLOCK.start + destinationIndex,(BLOCK.length - destinationIndex) * sizeof(TYPE));
	memcpy(BLOCK.start + destinationIndex,SOURCE.start + sourceIndex,length * sizeof(TYPE));
	BLOCK.length += length;
};

#macro block_clear(BLOCK,#TYPE)
{
	#local TYPE *source;
	if (!(source = realloc(BLOCK.source,sizeof(TYPE)))) error_throwExit("MEMORY: realloc");
	block_update(BLOCK,source,0,1);
};

#alias block_compare(BLOCK1,BLOCK2,#TYPE)
{
	(BLOCK1.length == BLOCK2.length) && (memcmp(BLOCK1.start,BLOCK2.start,BLOCK1.length * sizeof(TYPE)) == 0)
};

#alias block_getSource(BLOCK)
{
	BLOCK.start
};

#macro block_setLength(BLOCK,#TYPE,NEW_LENGTH,OLD_LENGTH)
{
	#local TYPE *source;
	#local DKusize capacity;
	block_trim(BLOCK,TYPE);
	block_calculateCapacity(NEW_LENGTH,capacity);
	if (!(source = realloc(BLOCK.source,capacity * sizeof(TYPE)))) error_throwReturn("MEMORY: realloc");
	if (NEW_LENGTH > BLOCK.length) memset(source + BLOCK.length,0,(NEW_LENGTH - BLOCK.length) * sizeof(TYPE));
	OLD_LENGTH = BLOCK.length;
	block_update(BLOCK,source,NEW_LENGTH,capacity);
};

#alias block_getLength(BLOCK)
{
	BLOCK.length
};

#alias block_isEmpty(BLOCK)
{
	BLOCK.length == 0
};

#alias block_isNotEmpty(BLOCK)
{
	BLOCK.length != 0
};
