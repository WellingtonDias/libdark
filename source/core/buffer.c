#macro buffer_createFromFile(BUFFER,#TYPE,FILE_NAME,FILE_TYPE,START,END)
{
	#local FILE *file;
	#local DKssize inputSize;
	if (!(file = fopen(FILE_NAME,FILE_TYPE))) error_throwReturn("FILE: open");
	if (fseek(file,0,SEEK_END) != 0) error_throwReturn("FILE: seek");
	if ((inputSize = ftell(file)) == -1) error_throwReturn("FILE: tell");
	if (inputSize > 0)
	{
		#local TYPE *source;
		#local DKusize index;
		#local DKusize outputSize;
		#local DKusize capacity;
		block_calculateRange(START,END,inputSize,index,outputSize);
		error_bypassReturn();
		block_calculateCapacity(outputSize,capacity);
		if (!(source = malloc(capacity))) error_throwReturn("MEMORY: malloc");
		if (fseek(file,index,SEEK_SET) != 0) error_throwReturn("FILE: seek");
		if (fread(source,1,outputSize,file) != outputSize) error_throwReturn("FILE: read");
		if (fclose(file) != 0) error_throwReturn("FILE: close");
		block_update(BUFFER,source,outputSize,capacity);
	}
	else block_createFromNothing(BUFFER,TYPE);
};

#macro buffer_saveToFile(BUFFER,START,END,FILE_NAME,FILE_TYPE)
{
	#local FILE *file;
	#local DKusize index;
	#local DKusize size;
	block_calculateRange(START,END,BUFFER.size,index,size);
	error_bypass();
	if (!(file = fopen(FILE_NAME,FILE_TYPE))) error_throw("FILE: open");
	if (fwrite(BUFFER.start + index,1,size,file) != size) error_throw("FILE: write");
	if (FILE_TYPE == "w")
	{
		if (fwrite("\n",1,1,file) != 1) error_throw("FILE: write");
	};
	if (fclose(file) != 0) error_throw("FILE: close");
};

#macro buffer_insert(BUFFER,#TYPE,INDEX,SOURCE,SIZE)
{
	#local DKusize size;
	size = ((INDEX > BUFFER.size)? INDEX : BUFFER.size) + SIZE;
	block_increase(BUFFER,TYPE,size);
	error_bypass();
	if (INDEX > BUFFER.size) memset(BUFFER.start + BUFFER.size,0,INDEX - BUFFER.size);
	else memmove(BUFFER.start + INDEX + SIZE,BUFFER.start + INDEX,BUFFER.size - INDEX);
	BUFFER.size = size;
	memcpy(BUFFER.start + INDEX,SOURCE,SIZE);
};

#macro buffer_write(BUFFER,#TYPE,INDEX,SOURCE,SIZE)
{
	if (INDEX + SIZE > BUFFER.size)
	{
		block_increase(BUFFER,TYPE,INDEX + SIZE);
		error_bypass();
		if (INDEX > BUFFER.size) memset(BUFFER.start + BUFFER.size,0,INDEX - BUFFER.size);
		BUFFER.size = INDEX + SIZE;
	};
	memcpy(BUFFER.start + INDEX,SOURCE,SIZE);
};

#macro buffer_erase(BUFFER,#TYPE,INDEX,SIZE)
{
	if (SIZE > BUFFER.size) error_throw("invalid SIZE");
	if ((DKssize) INDEX > (DKssize) BUFFER.size - (DKssize) SIZE) error_throw("invalid INDEX");
	memset(BUFFER.start + INDEX,0,SIZE);
};

#macro buffer_remove(BUFFER,#TYPE,INDEX,SIZE)
{
	if (SIZE > BUFFER.size) error_throw("invalid SIZE");
	if ((DKssize) INDEX > (DKssize) BUFFER.size - (DKssize) SIZE) error_throw("invalid INDEX");
	memcpy(BUFFER.start + INDEX,BUFFER.start + INDEX + SIZE,BUFFER.size - SIZE - INDEX);
	BUFFER.size -= SIZE;
	block_decrease(BUFFER,TYPE,BUFFER.size);
};
