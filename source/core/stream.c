#macro stream_prepend(STREAM,#TYPE,SOURCE)
{
	if (STREAM.offset > 0)
	{
		--STREAM.start;
		--STREAM.offset;
	}
	else
	{
		block_increase(STREAM,TYPE,STREAM.length + 1);
		error_bypassExit();
		memmove(STREAM.start + 1,STREAM.start,STREAM.length * sizeof(TYPE));
	};
	STREAM.start[0] = SOURCE;
	++STREAM.length;
};

#macro stream_insert(STREAM,#TYPE,INDEX,SOURCE)
{
	#local DKusize index;
	block_calculateSafePosition(INDEX,STREAM.length + 1,index);
	error_bypassExit();
	if ((index == 0) && (STREAM.offset > 0))
	{
		--STREAM.start;
		--STREAM.offset;
	}
	else
	{
		block_increase(STREAM,TYPE,STREAM.length + 1);
		error_bypassExit();
		memmove(STREAM.start + index + 1,STREAM.start + index,(STREAM.length - index) * sizeof(TYPE));
	};
	STREAM.start[index] = SOURCE;
	++STREAM.length;
};

#macro stream_append(STREAM,#TYPE,SOURCE)
{
	block_increase(STREAM,TYPE,STREAM.length + 1);
	error_bypassExit();
	STREAM.start[STREAM.length] = SOURCE;
	++STREAM.length;
};

#macro stream_replace(STREAM,#TYPE,INDEX,NEW_SOURCE,OLD_SOURCE)
{
	#local DKusize index;
	block_calculateSafePosition(INDEX,STREAM.length,index);
	error_bypassBreak();
	OLD_SOURCE = STREAM.start[index];
	STREAM.start[index] = NEW_SOURCE;
};

#macro stream_set(STREAM,#TYPE,INDEX,NEW_SOURCE,OLD_SOURCE)
{
	#local DKusize index;
	block_calculateUnsafePosition(INDEX,STREAM.length,index);
	error_bypassBreak();
	if (index < STREAM.length) OLD_SOURCE = STREAM.start[index];
	else
	{
		block_increase(STREAM,TYPE,index + 1);
		error_bypassBreak();
		if (index > STREAM.length) memset(STREAM.start + STREAM.length,0,(index - STREAM.length) * sizeof(TYPE));
		STREAM.length = index + 1;
		OLD_SOURCE = (TYPE) 0;
	};
	STREAM.start[index] = NEW_SOURCE;
};

#macro stream_swap(STREAM,#TYPE,INDEX1,INDEX2)
{
	TYPE SOURCE;
	#local DKusize index1;
	#local DKusize index2;
	block_calculateSafePosition(INDEX1,STREAM.length,index1);
	error_bypassExit();
	block_calculateSafePosition(INDEX2,STREAM.length,index2);
	error_bypassExit();
	SOURCE = STREAM.start[index1];
	STREAM.start[index1] = STREAM.start[index2];
	STREAM.start[index2] = SOURCE;
};

#macro stream_getFront(STREAM,#TYPE,SOURCE)
{
	if (STREAM.length == 0) error_throwBreak("STREAM: empty");
	SOURCE = STREAM.start[0];
};

#macro stream_getIndex(STREAM,#TYPE,INDEX,SOURCE)
{
	#local DKusize index;
	block_calculateSafePosition(INDEX,STREAM.length,index);
	error_bypassBreak();
	SOURCE = STREAM.start[index];
};

#macro stream_getRear(STREAM,#TYPE,SOURCE)
{
	if (STREAM.length == 0) error_throwBreak("STREAM: empty");
	SOURCE = STREAM.start[STREAM.length - 1];
};

#macro stream_dequeue(STREAM,#TYPE,SOURCE)
{
	if (STREAM.length == 0) error_throwBreak("STREAM: empty");
	--STREAM.length;
	SOURCE = STREAM.start[0];
	++STREAM.start;
	++STREAM.offset;
};

#macro stream_remove(STREAM,#TYPE,INDEX,SOURCE)
{
	#local DKusize index;
	block_calculateSafePosition(INDEX,STREAM.length,index);
	error_bypassBreak();
	--STREAM.length;
	SOURCE = STREAM.start[index];
	if (index == 0)
	{
		++STREAM.start;
		++STREAM.offset;
	}
	else
	{
		if (index < STREAM.length) memcpy(STREAM.start + index,STREAM.start + index + 1,(STREAM.length - index) * sizeof(TYPE));
		block_decrease(STREAM,TYPE,STREAM.length);
	};
};

#macro stream_pop(STREAM,#TYPE,SOURCE)
{
	if (STREAM.length == 0) error_throwBreak("STREAM: empty");
	--STREAM.length;
	SOURCE = STREAM.start[STREAM.length];
	block_decrease(STREAM,TYPE,STREAM.length);
};
