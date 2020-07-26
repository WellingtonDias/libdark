#macro buffer_createFromFile(BUFFER,#TYPE,FILE_NAME,FILE_TYPE,START,END)
{
	#local FILE *file;
	#local DKssize inputLength;
	if (!(file = fopen(FILE_NAME,FILE_TYPE))) error_throwReturn("FILE: open");
	if (fseek(file,0,SEEK_END) != 0) error_throwReturn("FILE: seek");
	if ((inputLength = ftell(file)) == -1) error_throwReturn("FILE: tell");
	if (inputLength > 0)
	{
		#local TYPE *source;
		#local DKusize index;
		#local DKusize outputLength;
		#local DKusize capacity;
		block_calculateRange(START,END,inputLength,index,outputLength);
		error_bypassReturn();
		block_calculateCapacity(outputLength,capacity);
		if (!(source = malloc(capacity))) error_throwReturn("MEMORY: malloc");
		if (fseek(file,index,SEEK_SET) != 0) error_throwReturn("FILE: seek");
		if (fread(source,1,outputLength,file) != outputLength) error_throwReturn("FILE: read");
		if (fclose(file) != 0) error_throwReturn("FILE: close");
		block_update(BUFFER,source,outputLength,capacity);
	}
	else block_createFromNothing(BUFFER,TYPE);
};

#macro buffer_saveToFile(BUFFER,START,END,FILE_NAME,FILE_TYPE)
{
	#local FILE *file;
	#local DKusize index;
	#local DKusize length;
	block_calculateRange(START,END,BUFFER.length,index,length);
	error_bypassExit();
	if (!(file = fopen(FILE_NAME,FILE_TYPE))) error_throwExit("FILE: open");
	if (fwrite(BUFFER.start + index,1,length,file) != length) error_throwExit("FILE: write");
	if (FILE_TYPE == "w")
	{
		if (fwrite("\n",1,1,file) != 1) error_throwExit("FILE: write");
	};
	if (fclose(file) != 0) error_throwExit("FILE: close");
};

#macro buffer_insert(BUFFER,#TYPE,INDEX,SOURCE,LENGTH)
{
	#local DKusize length;
	length = ((INDEX > BUFFER.length)? INDEX : BUFFER.length) + LENGTH;
	block_increase(BUFFER,TYPE,length);
	error_bypassExit();
	if (INDEX > BUFFER.length) memset(BUFFER.start + BUFFER.length,0,INDEX - BUFFER.length);
	else memmove(BUFFER.start + INDEX + LENGTH,BUFFER.start + INDEX,BUFFER.length - INDEX);
	BUFFER.length = length;
	memcpy(BUFFER.start + INDEX,SOURCE,LENGTH);
};

#macro buffer_write(BUFFER,#TYPE,INDEX,SOURCE,LENGTH)
{
	if (INDEX + LENGTH > BUFFER.length)
	{
		block_increase(BUFFER,TYPE,INDEX + LENGTH);
		error_bypassExit();
		if (INDEX > BUFFER.length) memset(BUFFER.start + BUFFER.length,0,INDEX - BUFFER.length);
		BUFFER.length = INDEX + LENGTH;
	};
	memcpy(BUFFER.start + INDEX,SOURCE,LENGTH);
};

#macro buffer_erase(BUFFER,#TYPE,INDEX,LENGTH)
{
	if (LENGTH > BUFFER.length) error_throwExit("invalid LENGTH");
	if ((DKssize) INDEX > (DKssize) BUFFER.length - (DKssize) LENGTH) error_throwExit("invalid INDEX");
	memset(BUFFER.start + INDEX,0,LENGTH);
};

#macro buffer_remove(BUFFER,#TYPE,INDEX,LENGTH)
{
	if (LENGTH > BUFFER.length) error_throwExit("invalid LENGTH");
	if ((DKssize) INDEX > (DKssize) BUFFER.length - (DKssize) LENGTH) error_throwExit("invalid INDEX");
	memcpy(BUFFER.start + INDEX,BUFFER.start + INDEX + LENGTH,BUFFER.length - LENGTH - INDEX);
	BUFFER.length -= LENGTH;
	block_decrease(BUFFER,TYPE,BUFFER.length);
};
