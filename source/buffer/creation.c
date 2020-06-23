DKbuffer *dkBuffer_create(DKu8 ENDIAN)
{
	DKbuffer *buffer = NULL;
	DKu8 *source = NULL;
	unsafe_start();
	if (!(source = malloc(1))) error_throwReturn("MEMORY: malloc");
	blob_create(DKbuffer,source,0,1,buffer);
	buffer_calculateEndian(buffer,ENDIAN,buffer->endian);
	buffer->offset = 0;
	return buffer;
};

DKbuffer *dkBuffer_createFromRaw(DKu8 *SOURCE,DKusize SIZE,DKu8 ENDIAN,DKssize START,DKssize END)
{
	DKbuffer *buffer = NULL;
	unsafe_start();
	blob_createFromRaw(DKbuffer,DKu8,SOURCE,SIZE,START,END,buffer);
	buffer_calculateEndian(buffer,ENDIAN,buffer->endian);
	buffer->offset = 0;
	return buffer;
};

DKbuffer *dkBuffer_createFromCopy(DKbuffer *BUFFER,DKssize START,DKssize END)
{
	DKbuffer *buffer = NULL;
	safe_start(BUFFER);
	blob_createFromRaw(DKbuffer,DKu8,(BUFFER->block).source,(BUFFER->block).size,START,END,buffer);
	buffer_calculateEndian(buffer,BUFFER->endian,buffer->endian);
	buffer->offset = 0;
	safe_endReturn(BUFFER,buffer);
};

DKbuffer *dkBuffer_createFromFile(DKcharacter *FILE_NAME,DKu8 ENDIAN,DKssize START,DKssize END)
{
	DKbuffer *buffer = NULL;
	unsafe_start();
	blob_createFromFile(DKbuffer,DKu8,FILE_NAME,"rb",START,END,buffer);
	buffer_calculateEndian(buffer,ENDIAN,buffer->endian);
	buffer->offset = 0;
	return buffer;
};

DKbuffer *dkBuffer_destroy(DKbuffer *BUFFER)
{
	safe_start(BUFFER);
	blob_destroy(BUFFER);
	return NULL;
};
