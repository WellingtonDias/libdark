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
	if ((index < 0) || (index >= (SignedSize) SIZE)) exception_throwBreak("invalid INDEX");
	OUTPUT_INDEX = index;
};

#routine box_calculateRange(INPUT_START,INPUT_END,SIZE,OUTPUT_START,OUTPUT_END)
{
	#local SignedSize start;
	#local SignedSize end;
	box_calculateIndex(INPUT_START,SIZE,start);
	if (start < 0) exception_throwBreak("invalid RANGE");
	box_calculateIndex(INPUT_END,SIZE,end);
	if ((end < start) || (end >= (SignedSize) SIZE)) exception_throwBreak("invalid RANGE");
	OUTPUT_START = start;
	OUTPUT_END = end;
};

#routine box_adjustCapacity(#TYPE,BOX,SIZE)
{
	#local UnsignedSize capacity;
	capacity = 1;
	while (capacity < BOX.offset + SIZE) capacity *= 2;
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

#routine box_createFromRawMemory(#TYPE,BOX,RAW_POINTER,SIZE)
{
	#local TYPE* source;
	if (!(source = malloc(SIZE * sizeof(TYPE)))) exception_throwBreak("MEMORY: malloc");
	memcpy(source,RAW_POINTER,SIZE * sizeof(TYPE));
	box_update(BOX,source,SIZE,SIZE);
};

#routine box_createFromMemory(#TYPE,BOX,POINTER,START,END)
{
	#local UnsignedSize index;
	#local UnsignedSize size;
	box_calculateRange(START,END,pointer_getSize(POINTER),index,size);
	size = size - index + 1;
	box_createFromRawMemory(TYPE,BOX,pointer_getSource(POINTER) + index,size);
};

#routine box_createFromCopy(#TYPE,BOX,SOURCE,START,END)
{
	#local UnsignedSize index;
	#local UnsignedSize size;
	box_calculateRange(START,END,SOURCE.size,index,size);
	size = size - index + 1;
	box_createFromRawMemory(TYPE,BOX,SOURCE.start + index,size);
};

#routine box_destroy(BOX,SOURCE)
{
	if (SOURCE) free(BOX.source);
	box_update(BOX,NULL,0,0);
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

#routine box_merge(#TYPE,TARGET_BOX,TARGET_INDEX,SOURCE_BOX,SOURCE_START,SOURCE_END)
{
	#local UnsignedSize targetIndex;
	#local UnsignedSize sourceIndex;
	#local UnsignedSize size;
	box_calculateSafeIndex(TARGET_INDEX,TARGET_BOX.size + 1,targetIndex);
	box_calculateRange(SOURCE_START,SOURCE_END,SOURCE_BOX.size,sourceIndex,size);
	size = size - sourceIndex + 1;
	box_adjustCapacity(TYPE,TARGET_BOX,TARGET_BOX.size + size);
	if (targetIndex < TARGET_BOX.size) memmove(TARGET_BOX.start + targetIndex + size,TARGET_BOX.start + targetIndex,(TARGET_BOX.size - targetIndex) * sizeof(TYPE));
	memcpy(TARGET_BOX.start + targetIndex,SOURCE_BOX.start + sourceIndex,size * sizeof(TYPE));
	TARGET_BOX.size += size;
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
