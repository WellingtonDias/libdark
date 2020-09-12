#routine stream_unsafeInsert(EXCEPTION,#TYPE,STREAM,INDEX,VALUE)
{
	block_adjustCapacity(EXCEPTION,TYPE,STREAM,STREAM.length + 1);
	exception_routineBypass(EXCEPTION);
	if (INDEX < STREAM.length) memmove(STREAM.start + INDEX + 1,STREAM.start + INDEX,(STREAM.length - INDEX) * sizeof(TYPE));
	STREAM.start[INDEX] = VALUE;
	++STREAM.length;
};

#routine stream_insert(EXCEPTION,#TYPE,STREAM,INDEX,VALUE)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(EXCEPTION,INDEX,STREAM.length + 1,index);
	exception_routineBypass(EXCEPTION);
	stream_unsafeInsert(EXCEPTION,TYPE,STREAM,index,VALUE);
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

#routine stream_unsafeReplace(EXCEPTION,#TYPE,STREAM,INDEX,VALUE,RETURN)
{
	RETURN = STREAM.start[INDEX];
	STREAM.start[INDEX] = VALUE;
};

#routine stream_replace(EXCEPTION,#TYPE,STREAM,INDEX,VALUE,RETURN)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(EXCEPTION,INDEX,STREAM.length,index);
	exception_routineBypass(EXCEPTION);
	stream_unsafeReplace(EXCEPTION,TYPE,STREAM,index,VALUE,RETURN);
};

#routine stream_unsafeSet(EXCEPTION,#TYPE,STREAM,INDEX,VALUE,RETURN)
{
	if (INDEX >= STREAM.length)
	{
		block_adjustCapacity(EXCEPTION,TYPE,STREAM,INDEX + 1);
		exception_routineBypass(EXCEPTION);
		if (INDEX > STREAM.length) memset(STREAM.start + STREAM.length,0,(INDEX - STREAM.length) * sizeof(TYPE));
		STREAM.length = INDEX + 1;
		RETURN = (TYPE) 0;
	}
	else RETURN = STREAM.start[INDEX];
	STREAM.start[INDEX] = VALUE;
};

#routine stream_set(EXCEPTION,#TYPE,STREAM,INDEX,VALUE,RETURN)
{
	#local UnsignedSize index;
	block_calculateUnsafeIndex(EXCEPTION,INDEX,STREAM.length,index);
	exception_routineBypass(EXCEPTION);
	stream_unsafeSet(EXCEPTION,TYPE,STREAM,index,VALUE,RETURN);
};

#routine stream_unsafeGet(EXCEPTION,#TYPE,STREAM,INDEX,RETURN)
{
	RETURN = STREAM.start[INDEX];
};

#routine stream_get(EXCEPTION,#TYPE,STREAM,INDEX,RETURN)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(EXCEPTION,INDEX,STREAM.length,index);
	exception_routineBypass(EXCEPTION);
	stream_unsafeGet(EXCEPTION,TYPE,STREAM,index,RETURN);
};

#routine stream_unsafeGetAtStart(EXCEPTION,#TYPE,STREAM,RETURN)
{
	RETURN = STREAM.start[0];
};

#routine stream_getAtStart(EXCEPTION,#TYPE,STREAM,RETURN)
{
	if (STREAM.length == 0) exception_routineThrow(EXCEPTION,"STREAM: empty");
	stream_unsafeGetAtStart(EXCEPTION,TYPE,STREAM,RETURN);
};

#routine stream_unsafeGetAtEnd(EXCEPTION,#TYPE,STREAM,RETURN)
{
	RETURN = STREAM.start[STREAM.length - 1];
};

#routine stream_getAtEnd(EXCEPTION,#TYPE,STREAM,RETURN)
{
	if (STREAM.length == 0) exception_routineThrow(EXCEPTION,"STREAM: empty");
	stream_unsafeGetAtEnd(EXCEPTION,TYPE,STREAM,RETURN);
};

#routine stream_unsafeRemove(EXCEPTION,#TYPE,STREAM,INDEX,RETURN)
{
	--STREAM.length;
	RETURN = STREAM.start[INDEX];
	if (INDEX < STREAM.length) memcpy(STREAM.start + INDEX,STREAM.start + INDEX + 1,(STREAM.length - INDEX) * sizeof(TYPE));
	block_adjustCapacity(EXCEPTION,TYPE,STREAM,STREAM.length);
};

#routine stream_remove(EXCEPTION,#TYPE,STREAM,INDEX,RETURN)
{
	#local UnsignedSize index;
	block_calculateSafeIndex(EXCEPTION,INDEX,STREAM.length,index);
	exception_routineBypass(EXCEPTION);
	stream_unsafeRemove(EXCEPTION,TYPE,STREAM,index,RETURN);
};

#routine stream_unsafeRemoveAtStart(EXCEPTION,#TYPE,STREAM,RETURN)
{
	--STREAM.length;
	RETURN = STREAM.start[0];
	++STREAM.start;
	++STREAM.offset;
};

#routine stream_removeAtStart(EXCEPTION,#TYPE,STREAM,RETURN)
{
	if (STREAM.length == 0) exception_routineThrow(EXCEPTION,"STREAM: empty");
	stream_unsafeRemoveAtStart(EXCEPTION,TYPE,STREAM,RETURN);
};

#routine stream_unsafeRemoveAtEnd(EXCEPTION,#TYPE,STREAM,RETURN)
{
	--STREAM.length;
	RETURN = STREAM.start[STREAM.length];
	block_adjustCapacity(EXCEPTION,TYPE,STREAM,STREAM.length);
};

#routine stream_removeAtEnd(EXCEPTION,#TYPE,STREAM,RETURN)
{
	if (STREAM.length == 0) exception_routineThrow(EXCEPTION,"STREAM: empty");
	stream_unsafeRemoveAtEnd(EXCEPTION,TYPE,STREAM,RETURN);
};

#routine stream_unsafeSwap(EXCEPTION,#TYPE,STREAM,INDEX1,INDEX2)
{
	#local TYPE value;
	value = STREAM.start[INDEX1];
	STREAM.start[INDEX1] = STREAM.start[INDEX2];
	STREAM.start[INDEX2] = value;
};

#routine stream_swap(EXCEPTION,#TYPE,STREAM,INDEX1,INDEX2)
{
	#local UnsignedSize index1;
	#local UnsignedSize index2;
	block_calculateSafeIndex(EXCEPTION,INDEX1,STREAM.length,index1);
	block_calculateSafeIndex(EXCEPTION,INDEX2,STREAM.length,index2);
	exception_routineBypass(EXCEPTION);
	stream_unsafeSwap(EXCEPTION,TYPE,STREAM,index1,index2);
};

#routine stream_unsafeShuffle(EXCEPTION,#TYPE,STREAM,START,END)
{
	#local TYPE value;
	#local UnsignedSize random;
	srand(time(NULL));
	for (; END > START; --END)
	{
		random = START + (rand() % (END + 1));
		value = STREAM.start[START + END];
		STREAM.start[START + END] = STREAM.start[random];
		STREAM.start[random] = value;
	};
};

#routine stream_shuffle(EXCEPTION,#TYPE,STREAM,START,END)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	stream_unsafeShuffle(EXCEPTION,TYPE,STREAM,start,end);
};

#routine stream_unsafeReverse(EXCEPTION,#TYPE,STREAM,START,END)
{
	#local TYPE value;
	while (START < END)
	{
		value = STREAM.start[START];
		STREAM.start[START] = STREAM.start[END];
		STREAM.start[END] = value;
		++START;
		--END;
	};
};

#routine stream_reverse(EXCEPTION,#TYPE,STREAM,START,END)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	stream_unsafeReverse(EXCEPTION,TYPE,STREAM,start,end);
};

#routine stream_unsafeMap(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT)
{
	for (; START <= END; ++START) STREAM.start[START] = (*CALLBACK)(STRUCT,START,STREAM.start[START]);
};

#routine stream_map(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	stream_unsafeMap(EXCEPTION,TYPE,STREAM,start,end,CALLBACK,STRUCT);
};

#routine stream_unsafeFilter(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT)
{
	for (; START <= END; ++START)
	{
		if (!(*CALLBACK)(STRUCT,START,STREAM.start[START]))
		{
			--STREAM.length;
			if (START < STREAM.length) memcpy(STREAM.start + START,STREAM.start + START + 1,(STREAM.length - START) * sizeof(TYPE));
			--START;
		};
	};
	block_adjustCapacity(EXCEPTION,TYPE,STREAM,STREAM.length);
};

#routine stream_filter(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	stream_unsafeFilter(EXCEPTION,TYPE,STREAM,start,end,CALLBACK,STRUCT);
};

#routine stream_unsafeReduce(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT,RETURN)
{
	for (; START <= END; ++START) RETURN = (*CALLBACK)(STRUCT,START,STREAM.start[START],RETURN);
};

#routine stream_reduce(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT,RETURN)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	stream_unsafeReduce(EXCEPTION,TYPE,STREAM,start,end,CALLBACK,STRUCT,RETURN);
};

#routine stream_unsafeSearch(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT,TARGET,RETURN)
{
	for (; START <= END; ++START)
	{
		if ((*CALLBACK)(STRUCT,START,STREAM.start[START],TARGET)) break;
	};
	RETURN = START <= END;
};

#routine stream_search(EXCEPTION,#TYPE,STREAM,START,END,#CALLBACK,STRUCT,TARGET,RETURN)
{
	#local UnsignedSize start;
	#local UnsignedSize end;
	block_calculateRange(EXCEPTION,START,END,STREAM.length,start,end);
	exception_routineBypass(EXCEPTION);
	stream_unsafeSearch(EXCEPTION,TYPE,STREAM,start,end,CALLBACK,STRUCT,TARGET,RETURN);
};
