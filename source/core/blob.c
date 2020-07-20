#macro blob_createFromFile(BLOB,#TYPE,FILE_NAME,FILE_TYPE,START,END)
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
		block_update(BLOB,source,outputSize,capacity);
	}
	else block_createFromNothing(BLOB,TYPE);
};

#macro blob_saveToFile(BLOB,START,END,FILE_NAME,FILE_TYPE)
{
	#local FILE *file;
	#local DKusize index;
	#local DKusize size;
	block_calculateRange(START,END,BLOB.size,index,size);
	error_bypass();
	if (!(file = fopen(FILE_NAME,FILE_TYPE))) error_throw("FILE: open");
	if (fwrite(BLOB.start + index,1,size,file) != size) error_throw("FILE: write");
	if (FILE_TYPE == "w")
	{
		if (fwrite("\n",1,1,file) != 1) error_throw("FILE: write");
	};
	if (fclose(file) != 0) error_throw("FILE: close");
};

#macro blob_insert(BLOB,#TYPE,INDEX,SOURCE,SIZE)
{
	#local DKusize size;
	size = ((INDEX > BLOB.size)? INDEX : BLOB.size) + SIZE;
	block_increase(BLOB,TYPE,size);
	error_bypass();
	if (INDEX > BLOB.size) memset(BLOB.start + BLOB.size,0,INDEX - BLOB.size);
	else memmove(BLOB.start + INDEX + SIZE,BLOB.start + INDEX,BLOB.size - INDEX);
	BLOB.size = size;
	memcpy(BLOB.start + INDEX,SOURCE,SIZE);
};

#macro blob_write(BLOB,#TYPE,INDEX,SOURCE,SIZE)
{
	if (INDEX + SIZE > BLOB.size)
	{
		block_increase(BLOB,TYPE,INDEX + SIZE);
		error_bypass();
		if (INDEX > BLOB.size) memset(BLOB.start + BLOB.size,0,INDEX - BLOB.size);
		BLOB.size = INDEX + SIZE;
	};
	memcpy(BLOB.start + INDEX,SOURCE,SIZE);
};

#macro blob_erase(BLOB,#TYPE,INDEX,SIZE)
{
	if (SIZE > BLOB.size) error_throw("invalid SIZE");
	if ((DKssize) INDEX > (DKssize) BLOB.size - (DKssize) SIZE) error_throw("invalid INDEX");
	memset(BLOB.start + INDEX,0,SIZE);
};

#macro blob_remove(BLOB,#TYPE,INDEX,SIZE)
{
	if (SIZE > BLOB.size) error_throw("invalid SIZE");
	if ((DKssize) INDEX > (DKssize) BLOB.size - (DKssize) SIZE) error_throw("invalid INDEX");
	BLOB.size -= SIZE;
	memcpy(BLOB.start + INDEX,BLOB.start + INDEX + SIZE,BLOB.size - INDEX);
	block_decrease(BLOB,TYPE,BLOB.size);
};
