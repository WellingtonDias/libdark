#macro stream_prepend(STREAM,#TYPE,VALUE)
{
	if (STREAM.offset > 0)
	{
		--STREAM.start;
		--STREAM.offset;
	}
	else
	{
		block_increase(STREAM,TYPE,STREAM.size + 1);
		error_bypass();
		memmove(STREAM.start + 1,STREAM.start,STREAM.size * sizeof(TYPE));
	}
	STREAM.start[0] = VALUE;
	++STREAM.size;
};

#macro stream_insert(STREAM,#TYPE,INDEX,VALUE)
{
	#local DKusize index;
	block_calculateSafePosition(INDEX,STREAM.size + 1,index);
	error_bypass();
	if ((index == 0) && (STREAM.offset > 0))
	{
		--STREAM.start;
		--STREAM.offset;
	}
	else
	{
		block_increase(STREAM,TYPE,STREAM.size + 1);
		error_bypass();
		memmove(STREAM.start + index + 1,STREAM.start + index,(STREAM.size - index) * sizeof(TYPE));
	}
	STREAM.start[index] = VALUE;
	++STREAM.size;
};

#macro stream_append(STREAM,#TYPE,VALUE)
{
	block_increase(STREAM,TYPE,STREAM.size + 1);
	error_bypass();
	STREAM.start[STREAM.size] = VALUE;
	++STREAM.size;
};

#macro stream_replace(STREAM,#TYPE,INDEX,NEW_VALUE,OLD_VALUE)
{
	#local DKusize index;
	block_calculateSafePosition(INDEX,STREAM.size,index);
	error_bypassCastReturn(TYPE);
	OLD_VALUE = STREAM.start[index];
	STREAM.start[index] = NEW_VALUE;
};

#macro stream_set(STREAM,#TYPE,INDEX,NEW_VALUE,OLD_VALUE)
{
	#local DKusize index;
	block_calculateUnsafePosition(INDEX,STREAM.size,index);
	error_bypassCastReturn(TYPE);
	if (index < STREAM.size) OLD_VALUE = STREAM.start[index];
	else
	{
		block_increase(STREAM,TYPE,index + 1);
		error_bypassCastReturn(TYPE);
		if (index > STREAM.size) memset(STREAM.start + STREAM.size,0,(index - STREAM.size) * sizeof(TYPE));
		STREAM.size = index + 1;
		OLD_VALUE = (DKscalar) NULL;
	};
	STREAM.start[index] = NEW_VALUE;
};

#macro stream_swap(STREAM,#TYPE,INDEX1,INDEX2)
{
	TYPE value;
	#local DKusize index1;
	#local DKusize index2;
	block_calculateSafePosition(INDEX1,STREAM.size,index1);
	error_bypass();
	block_calculateSafePosition(INDEX2,STREAM.size,index2);
	error_bypass();
	value = STREAM.start[index1];
	STREAM.start[index1] = STREAM.start[index2];
	STREAM.start[index2] = value;
};

#macro stream_getFront(STREAM,#TYPE,VALUE)
{
	if (STREAM.size == 0) error_throwCastReturn("STREAM: empty",TYPE);
	VALUE = STREAM.start[0];
};

#macro stream_getIndex(STREAM,#TYPE,INDEX,VALUE)
{
	#local DKusize index;
	block_calculateSafePosition(INDEX,STREAM.size,index);
	error_bypassCastReturn(TYPE);
	VALUE = STREAM.start[index];
};

#macro stream_getRear(STREAM,#TYPE,VALUE)
{
	if (STREAM.size == 0) error_throwCastReturn("STREAM: empty",TYPE);
	VALUE = STREAM.start[STREAM.size - 1];
};

#macro stream_dequeue(STREAM,#TYPE,VALUE)
{
	if (STREAM.size == 0) error_throwCastReturn("STREAM: empty",TYPE);
	--STREAM.size;
	VALUE = STREAM.start[0];
	++STREAM.start;
	++STREAM.offset;
};

#macro stream_remove(STREAM,#TYPE,INDEX,VALUE)
{
	#local DKusize index;
	block_calculateSafePosition(INDEX,STREAM.size,index);
	error_bypassCastReturn(TYPE);
	--STREAM.size;
	VALUE = STREAM.start[index];
	if (index == 0)
	{
		++STREAM.start;
		++STREAM.offset;
	}
	else
	{
		if (index < STREAM.size) memcpy(STREAM.start + index,STREAM.start + index + 1,(STREAM.size - index) * sizeof(TYPE));
		block_decrease(STREAM,TYPE,STREAM.size);
	};
};

#macro stream_pop(STREAM,#TYPE,VALUE)
{
	if (STREAM.size == 0) error_throwCastReturn("STREAM: empty",TYPE);
	--STREAM.size;
	VALUE = STREAM.start[STREAM.size];
	block_decrease(STREAM,TYPE,STREAM.size);
};
