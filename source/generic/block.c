#template block_define(NAME,TYPE)
{
	typedef struct
	{
		TYPE *source;
		DKusize size;
		DKusize capacity;
	} NAME;
}

#macro block_update(BLOCK,SOURCE,SIZE,CAPACITY)
{
	BLOCK.source = SOURCE;
	BLOCK.size = SIZE;
	BLOCK.capacity = CAPACITY;
}

#macro block_increase(BLOCK,#TYPE,SIZE)
{
	if (SIZE > BLOCK.capacity)
	{
		#local TYPE *source;
		#local DKusize capacity;
		helper_increaseCapacity(BLOCK.capacity,SIZE,capacity);
		if (!(source = realloc(BLOCK.source,capacity * sizeof(TYPE)))) error_throw("MEMORY: realloc");
		BLOCK.source = source;
		BLOCK.capacity = capacity;
	}
}

#macro block_insert(BLOCK,#TYPE,INDEX,SOURCE,SIZE)
{
	#local DKusize size;
	size = ((INDEX > BLOCK.size)? INDEX : BLOCK.size) + SIZE;
	block_increase(BLOCK,TYPE,size);
	error_bypass();
	if (INDEX > BLOCK.size) memset(BLOCK.source + BLOCK.size,0,(INDEX - BLOCK.size) * sizeof(TYPE));
	else memmove(BLOCK.source + INDEX + SIZE,BLOCK.source + INDEX,(BLOCK.size - INDEX) * sizeof(TYPE));
	memcpy(BLOCK.source + INDEX,SOURCE,SIZE * sizeof(TYPE));
	BLOCK.size = size;
}

#macro block_write(BLOCK,#TYPE,INDEX,SOURCE,SIZE)
{
	if (INDEX + SIZE > BLOCK.size)
	{
		block_increase(BLOCK,TYPE,INDEX + SIZE);
		error_bypass();
		if (INDEX > BLOCK.size) memset(BLOCK.source + BLOCK.size,0,(INDEX - BLOCK.size) * sizeof(TYPE));
		BLOCK.size = INDEX + SIZE;
	}
	memcpy(BLOCK.source + INDEX,SOURCE,SIZE * sizeof(TYPE));
}

#macro block_erase(BLOCK,#TYPE,INDEX,SIZE)
{
	if (SIZE > BLOCK.size) error_throw("invalid SIZE");
	if ((DKssize) INDEX > (DKssize) BLOCK.size - (DKssize) SIZE) error_throw("invalid INDEX");
	memset(BLOCK.source + INDEX,0,SIZE * sizeof(TYPE));
}

#macro block_decrease(BLOCK,#TYPE,SIZE)
{
	#local DKusize capacity;
	helper_decreaseCapacity(BLOCK.capacity,SIZE,capacity);
	if (capacity < BLOCK.capacity)
	{
		#local TYPE *source;
		if ((source = realloc(BLOCK.source,capacity * sizeof(TYPE))))
		{
			BLOCK.source = source;
			BLOCK.capacity = capacity;
		}
	}
}

#macro block_remove(BLOCK,#TYPE,INDEX,SIZE)
{
	if (SIZE > BLOCK.size) error_throw("invalid SIZE");
	if ((DKssize) INDEX > (DKssize) BLOCK.size - (DKssize) SIZE) error_throw("invalid INDEX");
	memcpy(BLOCK.source + INDEX,BLOCK.source + INDEX + SIZE,(BLOCK.size - SIZE - INDEX) * sizeof(TYPE));
	BLOCK.size -= SIZE;
	block_decrease(BLOCK,TYPE,BLOCK.size);
}

#macro block_merge(BLOCK,#TYPE,INDEX,SOURCE,START,END)
{
	#local DKusize destinationIndex;
	#local DKusize sourceIndex;
	#local DKusize size;
	helper_calculateSafePosition(INDEX,BLOCK.size + 1,destinationIndex);
	error_bypass();
	helper_calculateRange(START,END,SOURCE.size,sourceIndex,size);
	error_bypass();
	block_insert(BLOCK,TYPE,destinationIndex,SOURCE.source + sourceIndex,size);
}

#macro block_clear(BLOCK,#TYPE)
{
	#local TYPE *source;
	if (!(source = realloc(BLOCK.source,sizeof(TYPE)))) error_throw("MEMORY: realloc");
	block_update(BLOCK,source,0,1);
}

#macro block_destroy(BLOCK)
{
	free(BLOCK.source);
}

#alias block_getSource(BLOCK)
{
	BLOCK.source
}

#macro block_setSize(BLOCK,#TYPE,KIND,NEW_SIZE,OLD_SIZE)
{
	#local TYPE *source;
	#local DKssize size;
	#local DKusize capacity;
	switch (KIND)
	{
		case DARK_ABSOLUTE: size = NEW_SIZE; break;
		case DARK_RELATIVE: size = BLOCK.size + NEW_SIZE; break;
		default: error_throwReturn("invalid KIND");
	}
	if (size < 0) error_throwReturn("invalid SIZE");
	helper_calculateCapacity((DKusize) size,capacity);
	if (!(source = realloc(BLOCK.source,capacity * sizeof(TYPE)))) error_throwReturn("MEMORY: realloc");
	if ((DKusize) size > BLOCK.size) memset(BLOCK.source + BLOCK.size,0,(size - BLOCK.size) * sizeof(TYPE));
	OLD_SIZE = BLOCK.size;
	block_update(BLOCK,source,size,capacity);
}

#alias block_getSize(BLOCK)
{
	BLOCK.size
}

#alias block_isEmpty(BLOCK)
{
	BLOCK.size == 0
}

#alias block_compare(BLOCK1,BLOCK2,#TYPE)
{
	(BLOCK1.size == BLOCK2.size) && (memcmp(BLOCK1.source,BLOCK2.source,BLOCK1.size * sizeof(TYPE)) == 0)
}
