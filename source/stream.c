#routine stream_insert(EXCEPTION,#TYPE,STREAM,INDEX,VALUE)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(EXCEPTION,INDEX,STREAM.length + 1,index);
	exception_routineBypass(EXCEPTION);
	block_adjustCapacity(EXCEPTION,TYPE,STREAM,STREAM.length + 1);
	exception_routineBypass(EXCEPTION);
	if (index < STREAM.length) memmove(STREAM.start + index + 1,STREAM.start + index,(STREAM.length - index) * sizeof(TYPE));
	STREAM.start[index] = VALUE;
	++STREAM.length;
};

#routine stream_insertAtStart(EXCEPTION,#TYPE,STREAM,VALUE)
{
	if (STREAM.offset > 0)
	{
		--STREAM.start;
		--STREAM.offset;
	}
	else
	{
		block_adjustCapacity(EXCEPTION,TYPE,STREAM,STREAM.length + 1);
		exception_routineBypass(EXCEPTION);
		if (STREAM.length > 0) memmove(STREAM.start + 1,STREAM.start,STREAM.length * sizeof(TYPE));
	};
	STREAM.start[0] = VALUE;
	++STREAM.length;
};

#routine stream_insertAtEnd(EXCEPTION,#TYPE,STREAM,VALUE)
{
	block_adjustCapacity(EXCEPTION,TYPE,STREAM,STREAM.length + 1);
	exception_routineBypass(EXCEPTION);
	STREAM.start[STREAM.length] = VALUE;
	++STREAM.length;
};

#routine stream_replace(EXCEPTION,#TYPE,STREAM,INDEX,VALUE,RETURN)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(EXCEPTION,INDEX,STREAM.length,index);
	exception_routineBypass(EXCEPTION);
	RETURN = STREAM.start[index];
	STREAM.start[index] = VALUE;
};

#routine stream_set(EXCEPTION,#TYPE,STREAM,INDEX,VALUE,RETURN)
{
	#local UnsignedSize index;
	block_calculateUnsafeIndex(EXCEPTION,INDEX,STREAM.length,index);
	exception_routineBypass(EXCEPTION);
	if (index >= STREAM.length)
	{
		block_adjustCapacity(EXCEPTION,TYPE,STREAM,index + 1);
		exception_routineBypass(EXCEPTION);
		if (index > STREAM.length) memset(STREAM.start + STREAM.length,0,(index - STREAM.length) * sizeof(TYPE));
		STREAM.length = index + 1;
		RETURN = (TYPE) 0;
	}
	else RETURN = STREAM.start[index];
	STREAM.start[index] = VALUE;
};

#routine stream_get(EXCEPTION,#TYPE,STREAM,INDEX,RETURN)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(EXCEPTION,INDEX,STREAM.length,index);
	exception_routineBypass(EXCEPTION);
	RETURN = STREAM.start[index];
};

#routine stream_getAtStart(EXCEPTION,#TYPE,STREAM,RETURN)
{
	if (STREAM.length == 0) exception_routineThrow(EXCEPTION,"STREAM: empty");
	RETURN = STREAM.start[0];
};

#routine stream_getAtEnd(EXCEPTION,#TYPE,STREAM,RETURN)
{
	if (STREAM.length == 0) exception_routineThrow(EXCEPTION,"STREAM: empty");
	RETURN = STREAM.start[STREAM.length - 1];
};

#routine stream_remove(EXCEPTION,#TYPE,STREAM,INDEX,RETURN)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(EXCEPTION,INDEX,STREAM.length,index);
	exception_routineBypass(EXCEPTION);
	--STREAM.length;
	RETURN = STREAM.start[index];
	if (index < STREAM.length) memcpy(STREAM.start + index,STREAM.start + index + 1,(STREAM.length - index) * sizeof(TYPE));
	block_adjustCapacity(EXCEPTION,TYPE,STREAM,STREAM.length);
};

#routine stream_removeAtStart(EXCEPTION,#TYPE,STREAM,RETURN)
{
	if (STREAM.length == 0) exception_routineThrow(EXCEPTION,"STREAM: empty");
	--STREAM.length;
	RETURN = STREAM.start[0];
	++STREAM.start;
	++STREAM.offset;
};

#routine stream_removeAtEnd(EXCEPTION,#TYPE,STREAM,RETURN)
{
	if (STREAM.length == 0) exception_routineThrow(EXCEPTION,"STREAM: empty");
	--STREAM.length;
	RETURN = STREAM.start[STREAM.length];
	block_adjustCapacity(EXCEPTION,TYPE,STREAM,STREAM.length);
};

#routine stream_swap(EXCEPTION,#TYPE,STREAM,INDEX1,INDEX2)
{
	#local TYPE value;
	#local UnsignedSize index1;
	#local UnsignedSize index2;
	block_calculateSafeIndex(EXCEPTION,INDEX1,STREAM.length,index1);
	block_calculateSafeIndex(EXCEPTION,INDEX2,STREAM.length,index2);
	exception_routineBypass(EXCEPTION);
	value = STREAM.start[index1];
	STREAM.start[index1] = STREAM.start[index2];
	STREAM.start[index2] = value;
};

#routine stream_shuffle(EXCEPTION,#TYPE,STREAM,START,END)
{
	#local TYPE value;
	#local UnsignedSize start;
	#local UnsignedSize end;
	#local UnsignedSize index;
	#local UnsignedSize random;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	srand(time(NULL));
	for (index = end; index > start; --index)
	{
		random = start + (rand() % (index + 1));
		value = STREAM.start[start + index];
		STREAM.start[start + index] = STREAM.start[random];
		STREAM.start[random] = value;
	};
};

#routine stream_reverse(EXCEPTION,#TYPE,STREAM,START,END)
{
	#local TYPE value;
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	while (start < end)
	{
		value = STREAM.start[start];
		STREAM.start[start] = STREAM.start[end];
		STREAM.start[end] = value;
		++start;
		--end;
	};
};

#routine stream_map(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	for (; start <= end; ++start) STREAM.start[start] = (*CALLBACK)(STRUCT,start,STREAM.start[start]);
};

#routine stream_filter(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	for (; start <= end; ++start)
	{
		if (!(*CALLBACK)(STRUCT,start,STREAM.start[start]))
		{
			--STREAM.length;
			if (start < STREAM.length) memcpy(STREAM.start + start,STREAM.start + start + 1,(STREAM.length - start) * sizeof(TYPE));
			--start;
		};
	};
	block_adjustCapacity(EXCEPTION,TYPE,STREAM,STREAM.length);
};

#routine stream_reduce(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT,RETURN)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	for (; start <= end; ++start) RETURN = (*CALLBACK)(STRUCT,start,STREAM.start[start],RETURN);
};

#routine stream_search(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT,TARGET,RETURN)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	for (; start <= end; ++start)
	{
		if ((*CALLBACK)(STRUCT,start,STREAM.start[start],TARGET)) break;
	};
	RETURN = start <= end;
};
