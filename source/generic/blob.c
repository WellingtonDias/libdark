#macro blob_create(#TYPE,SOURCE,SIZE,CAPACITY,BLOB)
{
	if (!(BLOB = malloc(sizeof(TYPE)))) error_throwReturn("MEMORY: malloc");
	block_update(BLOB->block,SOURCE,SIZE,CAPACITY);
	mutex_update(BLOB->mutex,NULL);
};

#macro blob_createFromRaw(#BLOB_TYPE,#BLOCK_TYPE,SOURCE,SIZE,START,END,BLOB)
{
	#local BLOCK_TYPE *source;
	#local DKusize index;
	#local DKusize size;
	#local DKusize capacity;
	helper_calculateRange(START,END,SIZE,index,size);
	error_bypassReturn();
	helper_calculateCapacity(size,capacity);
	if (!(source = malloc(capacity))) error_throwReturn("MEMORY: malloc");
	memcpy(source,SOURCE + index,size);
	blob_create(BLOB_TYPE,source,size,capacity,BLOB);
};

#macro blob_createFromFile(#BLOB_TYPE,#BLOCK_TYPE,FILE_NAME,FILE_TYPE,START,END,BLOB)
{
	#local FILE *file;
	#local BLOCK_TYPE *source;
	#local DKssize sourceSize;
	#local DKusize index;
	#local DKusize outputSize;
	#local DKusize capacity;
	if (!(file = fopen(FILE_NAME,FILE_TYPE))) error_throwReturn("FILE: open");
	if (fseek(file,0,SEEK_END) != 0) error_throwReturn("FILE: seek");
	if ((sourceSize = ftell(file)) == -1) error_throwReturn("FILE: tell");
	helper_calculateRange(START,END,sourceSize,index,outputSize);
	error_bypassReturn();
	helper_calculateCapacity(outputSize,capacity);
	if (!(source = malloc(capacity))) error_throwReturn("MEMORY: malloc");
	if (fseek(file,index,SEEK_SET) != 0) error_throwReturn("FILE: seek");
	if (fread(source,1,outputSize,file) != outputSize) error_throwReturn("FILE: read");
	if (fclose(file) != 0) error_throwReturn("FILE: close");
	blob_create(BLOB_TYPE,source,outputSize,capacity,BLOB);
};

#macro blob_save(BLOB,START,END,FILE_NAME,FILE_TYPE)
{
	#local FILE *file;
	#local DKusize index;
	#local DKusize size;
	helper_calculateRange(START,END,(BLOB->block).size,index,size);
	error_bypass();
	if (!(file = fopen(FILE_NAME,FILE_TYPE))) error_throw("FILE: open");
	if (fwrite((BLOB->block).source + index,1,size,file) != size) error_throw("FILE: write");
	if (FILE_TYPE == "w")
	{
		if (fwrite("\n",1,1,file) != 1) error_throw("FILE: write");
	};
	if (fclose(file) != 0) error_throw("FILE: close");
};

#macro blob_destroy(BLOB)
{
	block_destroy(BLOB->block);
	mutex_destroy(BLOB->mutex);
	free(BLOB);
};
