#routine data_calculateIndex(INDEX,LENGTH,RETURN)
{
	RETURN = INDEX;
	if (RETURN < 0) RETURN += LENGTH;
};

#routine data_calculateUnsafeIndex(STRUCT,INDEX,LENGTH,RETURN)
{
	#local SignedSize index;
	data_calculateIndex(INDEX,LENGTH,index);
	if (index < 0) exception_routineThrow(STRUCT->exception,"invalid INDEX");
	RETURN = index;
};

#routine data_calculateSafeIndex(STRUCT,INDEX,LENGTH,RETURN)
{
	#local SignedSize index;
	data_calculateIndex(INDEX,LENGTH,index);
	if ((index < 0) || (index >= (SignedSize) LENGTH)) exception_routineThrow(STRUCT->exception,"invalid INDEX");
	RETURN = index;
};

#routine data_calculateRange(STRUCT,START,END,LENGTH,RETURN1,RETURN2)
{
	#local SignedSize start;
	#local SignedSize end;
	data_calculateIndex(START,LENGTH,start);
	if (start < 0) exception_routineThrow(STRUCT->exception,"invalid RANGE");
	data_calculateIndex(END,LENGTH,end);
	if ((end < start) || (end >= (SignedSize) LENGTH)) exception_routineThrow(STRUCT->exception,"invalid RANGE");
	RETURN1 = start;
	RETURN2 = end;
};
