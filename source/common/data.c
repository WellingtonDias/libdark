#routine data_calculateIndex(INDEX,LENGTH,RETURN)
{
	RETURN = INDEX;
	if (RETURN < 0) RETURN += LENGTH;
};

#routine data_calculateUnsafeIndex(EXCEPTION,INDEX,LENGTH,RETURN)
{
	#local SignedSize index;
	data_calculateIndex(INDEX,LENGTH,index);
	if (index < 0) exception_routineThrow(EXCEPTION,"invalid INDEX");
	RETURN = index;
};

#routine data_calculateSafeIndex(EXCEPTION,INDEX,LENGTH,RETURN)
{
	#local SignedSize index;
	data_calculateIndex(INDEX,LENGTH,index);
	if ((index < 0) || (index >= (SignedSize) LENGTH)) exception_routineThrow(EXCEPTION,"invalid INDEX");
	RETURN = index;
};

#routine data_calculateRange(EXCEPTION,START,END,LENGTH,RETURN1,RETURN2)
{
	#local SignedSize start;
	#local SignedSize end;
	data_calculateIndex(START,LENGTH,start);
	if (start < 0) exception_routineThrow(EXCEPTION,"invalid RANGE");
	data_calculateIndex(END,LENGTH,end);
	if ((end < start) || (end >= (SignedSize) LENGTH)) exception_routineThrow(EXCEPTION,"invalid RANGE");
	RETURN1 = start;
	RETURN2 = end;
};

#routine data_adjustCapacity(EXCEPTION,DATA,LENGTH,#TYPE)
{
	#local UnsignedSize capacity;
	capacity = 1;
	while (capacity < LENGTH) capacity *= 2;
	if (capacity != DATA.capacity)
	{
		#local TYPE* pointer;
		if ((pointer = realloc(DATA.pointer,capacity * sizeof(TYPE))) == NULL) exception_routineThrow(EXCEPTION,"MEMORY: realloc");
		DATA.pointer = pointer;
		DATA.capacity = capacity;
	};
};

#routine data_compare(DATA1,DATA2,#POINTER,#TYPE,RETURN)
{
	RETURN = (DATA1.length == DATA2.length) && (memcmp(DATA1.POINTER,DATA2.POINTER,DATA1.length * sizeof(TYPE)) == 0);
};

#routine data_merge(EXCEPTION,TARGET,INDEX,SOURCE,#DATA_ADJUST_CAPACITY,#POINTER,#TYPE)
{
	UnsignedSize index;
	data_calculateSafeIndex(EXCEPTION,INDEX,TARGET.length + 1,index);
	exception_routineBypass(EXCEPTION);
	DATA_ADJUST_CAPACITY(EXCEPTION,TARGET,TARGET.length + SOURCE.length);
	exception_routineBypass(EXCEPTION);
	if (index < TARGET.length) memmove(TARGET.POINTER + index + SOURCE.length,TARGET.POINTER + index,(TARGET.length - index) * sizeof(TYPE));
	memcpy(TARGET.POINTER + index,SOURCE.POINTER,SOURCE.length * sizeof(TYPE));
	TARGET.length += SOURCE.length;
};

#routine data_clear(EXCEPTION,DATA,#TYPE)
{
	if (DATA.length > 0)
	{
		#local TYPE* pointer;
		if ((pointer = realloc(DATA.pointer,sizeof(TYPE))) == NULL) exception_routineThrow(EXCEPTION,"MEMORY: realloc");
		DATA.pointer = pointer;
		DATA.length = 0;
		DATA.capacity = 1;
	};
};

#routine data_setLength(EXCEPTION,DATA,LENGTH,#DATA_ADJUST_CAPACITY,#POINTER,#TYPE,#VALUE)
{
	if (LENGTH == DATA.length) exception_routineThrow(EXCEPTION,"invalid LENGTH");
	DATA_ADJUST_CAPACITY(EXCEPTION,DATA,LENGTH);
	exception_routineBypass(EXCEPTION);
	if (LENGTH > DATA.length) memset(DATA.POINTER + DATA.length,VALUE,(LENGTH - DATA.length) * sizeof(TYPE));
	DATA.length = LENGTH;
};
