#routine bucket_calculateIndex(INDEX,LENGTH,RETURN)
{
	RETURN = INDEX;
	if (RETURN < 0) RETURN += LENGTH;
};

#routine bucket_calculateUnsafeIndex(STRUCT,INDEX,LENGTH,RETURN)
{
	#local SignedSize index;
	bucket_calculateIndex(INDEX,LENGTH,index);
	if (index < 0) exception_routineThrow(STRUCT->exception,"invalid INDEX");
	RETURN = index;
};

#routine bucket_calculateSafeIndex(STRUCT,INDEX,LENGTH,RETURN)
{
	#local SignedSize index;
	bucket_calculateIndex(INDEX,LENGTH,index);
	if ((index < 0) || (index >= (SignedSize) LENGTH)) exception_routineThrow(STRUCT->exception,"invalid INDEX");
	RETURN = index;
};

#routine bucket_calculateRange(STRUCT,START,END,LENGTH,RETURN1,RETURN2)
{
	#local SignedSize start;
	#local SignedSize end;
	bucket_calculateIndex(START,LENGTH,start);
	if (start < 0) exception_routineThrow(STRUCT->exception,"invalid RANGE");
	bucket_calculateIndex(END,LENGTH,end);
	if ((end < start) || (end >= (SignedSize) LENGTH)) exception_routineThrow(STRUCT->exception,"invalid RANGE");
	RETURN1 = start;
	RETURN2 = end;
};
