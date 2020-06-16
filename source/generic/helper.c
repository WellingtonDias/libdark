#macro helper_calculateIndex(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	OUTPUT_INDEX = INPUT_INDEX;
	if (INPUT_INDEX < 0) OUTPUT_INDEX += SIZE;
}

#alias helper_validateIndex(OUTPUT_INDEX,MINIMUM_INDEX,SIZE)
{
	(OUTPUT_INDEX >= (DKssize) MINIMUM_INDEX) && (OUTPUT_INDEX < (DKssize) SIZE)
}

#macro helper_calculateUnsafePosition(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	#local DKssize index;
	if (SIZE == 0) error_set("invalid SIZE");
	helper_calculateIndex((DKssize) INPUT_INDEX,SIZE,index);
	if (index < 0) error_set("invalid INDEX");
	OUTPUT_INDEX = index;
}

#macro helper_calculateSafePosition(INPUT_INDEX,SIZE,OUTPUT_INDEX)
{
	#local DKssize index;
	if (SIZE == 0) error_set("invalid SIZE");
	helper_calculateIndex((DKssize) INPUT_INDEX,SIZE,index);
	if (!helper_validateIndex(index,0,SIZE)) error_set("invalid INDEX");
	OUTPUT_INDEX = index;
}

#macro helper_calculateRange(START_INDEX,END_INDEX,SOURCE_SIZE,OUTPUT_INDEX,OUTPUT_SIZE)
{
	#local DKssize start;
	#local DKssize end;
	if (SOURCE_SIZE == 0) error_set("invalid SIZE");
	helper_calculateIndex((DKssize) START_INDEX,SOURCE_SIZE,start);
	if (!helper_validateIndex(start,0,SOURCE_SIZE)) error_set("invalid START");
	helper_calculateIndex((DKssize) END_INDEX,SOURCE_SIZE,end);
	if (!helper_validateIndex(end,start,SOURCE_SIZE)) error_set("invalid END");
	OUTPUT_INDEX = start;
	OUTPUT_SIZE = end - start + 1;
}

#macro helper_calculateCapacity(SIZE,CAPACITY)
{
	CAPACITY = 1;
	while (CAPACITY < SIZE) CAPACITY *= 2;
}

#macro helper_increaseCapacity(INPUT_CAPACITY,SIZE,OUTPUT_CAPACITY)
{
	OUTPUT_CAPACITY = INPUT_CAPACITY;
	while (OUTPUT_CAPACITY < SIZE) OUTPUT_CAPACITY *= 2;
}

#macro helper_decreaseCapacity(INPUT_CAPACITY,SIZE,OUTPUT_CAPACITY)
{
	OUTPUT_CAPACITY = INPUT_CAPACITY;
	while ((OUTPUT_CAPACITY > 1) && (OUTPUT_CAPACITY / 2 >= SIZE)) OUTPUT_CAPACITY /= 2;
}
