#routine stream_insert(#TYPE,STREAM,INDEX,VALUE)
{
	#local UnsignedSize index;
	box_calculateSafeIndex(INDEX,STREAM.size + 1,index);
	box_adjustCapacity(TYPE,STREAM,STREAM.size + 1);
	if (index < STREAM.size) memmove(STREAM.start + index + 1,STREAM.start + index,(STREAM.size - index) * sizeof(TYPE));
	STREAM.start[index] = VALUE;
	++STREAM.size;
};

#routine stream_insertAtStart(#TYPE,STREAM,VALUE)
{
	if (STREAM.offset > 0)
	{
		--STREAM.start;
		--STREAM.offset;
	}
	else
	{
		box_adjustCapacity(TYPE,STREAM,STREAM.size + 1);
		if (STREAM.size > 0) memmove(STREAM.start + 1,STREAM.start,STREAM.size * sizeof(TYPE));
	};
	STREAM.start[0] = VALUE;
	++STREAM.size;
};

#routine stream_insertAtEnd(#TYPE,STREAM,VALUE)
{
	box_adjustCapacity(TYPE,STREAM,STREAM.size + 1);
	STREAM.start[STREAM.size] = VALUE;
	++STREAM.size;
};

#routine stream_replace(#TYPE,STREAM,INDEX,NEW_VALUE,OLD_VALUE)
{
	#local UnsignedSize index;
	box_calculateSafeIndex(INDEX,STREAM.size,index);
	OLD_VALUE = STREAM.start[index];
	STREAM.start[index] = NEW_VALUE;
};

#routine stream_set(#TYPE,STREAM,INDEX,NEW_VALUE,OLD_VALUE)
{
	#local UnsignedSize index;
	box_calculateUnsafeIndex(INDEX,STREAM.size,index);
	if (index >= STREAM.size)
	{
		box_adjustCapacity(TYPE,STREAM,index + 1);
		if (index > STREAM.size) memset(STREAM.start + STREAM.size,0,(index - STREAM.size) * sizeof(TYPE));
		STREAM.size = index + 1;
		OLD_VALUE = (TYPE) 0;
	}
	else OLD_VALUE = STREAM.start[index];
	STREAM.start[index] = NEW_VALUE;
};

#routine stream_get(#TYPE,STREAM,INDEX,VALUE)
{
	#local UnsignedSize index;
	box_calculateSafeIndex(INDEX,STREAM.size,index);
	VALUE = STREAM.start[index];
};

#routine stream_getAtStart(#TYPE,STREAM,VALUE)
{
	if (STREAM.size == 0) exception_throwBreak("STREAM: empty");
	VALUE = STREAM.start[0];
};

#routine stream_getAtEnd(#TYPE,STREAM,VALUE)
{
	if (STREAM.size == 0) exception_throwBreak("STREAM: empty");
	VALUE = STREAM.start[STREAM.size - 1];
};

#routine stream_erase(#TYPE,STREAM,INDEX,VALUE)
{
	#local UnsignedSize index;
	box_calculateSafeIndex(INDEX,STREAM.size,index);
	VALUE = STREAM.start[index];
	STREAM.start[index] = (TYPE) 0;
};

#routine stream_remove(#TYPE,STREAM,INDEX,VALUE)
{
	#local UnsignedSize index;
	box_calculateSafeIndex(INDEX,STREAM.size,index);
	--STREAM.size;
	VALUE = STREAM.start[index];
	if (index < STREAM.size) memcpy(STREAM.start + index,STREAM.start + index + 1,(STREAM.size - index) * sizeof(TYPE));
	box_adjustCapacity(TYPE,STREAM,STREAM.size);
};

#routine stream_removeAtStart(#TYPE,STREAM,VALUE)
{
	if (STREAM.size == 0) exception_throwBreak("STREAM: empty");
	--STREAM.size;
	VALUE = STREAM.start[0];
	++STREAM.start;
	++STREAM.offset;
};

#routine stream_removeAtEnd(#TYPE,STREAM,VALUE)
{
	if (STREAM.size == 0) exception_throwBreak("STREAM: empty");
	--STREAM.size;
	VALUE = STREAM.start[STREAM.size];
	box_adjustCapacity(TYPE,STREAM,STREAM.size);
};

#routine stream_swap(#TYPE,STREAM,INDEX1,INDEX2)
{
	#local TYPE value;
	#local UnsignedSize index1;
	#local UnsignedSize index2;
	box_calculateSafeIndex(INDEX1,STREAM.size,index1);
	box_calculateSafeIndex(INDEX2,STREAM.size,index2);
	value = STREAM.start[index1];
	STREAM.start[index1] = STREAM.start[index2];
	STREAM.start[index2] = value;
};

#routine stream_shuffle(#TYPE,STREAM,START,END)
{
	#local TYPE value;
	#local UnsignedSize start;
	#local UnsignedSize end;
	#local UnsignedSize index;
	#local UnsignedSize random;
	box_calculateRange(START,END,STREAM.size,start,end);
	srand(time(NULL));
	for (index = end; index > start; --index)
	{
		random = start + (rand() % (index + 1));
		value = STREAM.start[start + index];
		STREAM.start[start + index] = STREAM.start[random];
		STREAM.start[random] = value;
	};
};

#routine stream_reverse(#TYPE,STREAM,START,END)
{
	#local TYPE value;
	#local UnsignedSize start;
	#local UnsignedSize end;
	box_calculateRange(START,END,STREAM.size,start,end);
	while (start < end)
	{
		value = STREAM.start[start];
		STREAM.start[start] = STREAM.start[end];
		STREAM.start[end] = value;
		++start;
		--end;
	};
};

#routine stream_map(#TYPE,STREAM,START,END,#CALLBACK,STRUCT)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	box_calculateRange(START,END,STREAM.size,start,end);
	for (; start < end; ++start) STREAM.start[start] = (*CALLBACK)(STRUCT,start,STREAM.start[start]);
};

#routine stream_filter(#TYPE,STREAM,START,END,#CALLBACK,STRUCT)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	box_calculateRange(START,END,STREAM.size,start,end);
	for (; start < end; ++start)
	{
		if (!(*CALLBACK)(STRUCT,start,STREAM.start[start]))
		{
			--STREAM.size;
			if (start < STREAM.size) memcpy(STREAM.start + start,STREAM.start + start + 1,(STREAM.size - start) * sizeof(TYPE));
			--start;
		};
	};
	box_adjustCapacity(TYPE,STREAM,STREAM.size);
};

#routine stream_reduce(#TYPE,STREAM,START,END,#CALLBACK,STRUCT,ACCUMULATOR)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	box_calculateRange(START,END,STREAM.size,start,end);
	for (; start < end; ++start) ACCUMULATOR = (*CALLBACK)(STRUCT,start,STREAM.start[start],ACCUMULATOR);
};

#routine stream_search(#TYPE,STREAM,START,END,#CALLBACK,STRUCT,TARGET,FOUND)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	box_calculateRange(START,END,STREAM.size,start,end);
	for (; start < end; ++start)
	{
		if ((*CALLBACK)(STRUCT,start,STREAM.start[start],TARGET)) break;
	};
	FOUND = start < end;
};
