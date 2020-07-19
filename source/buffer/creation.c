DKbuffer *dkBuffer_create(DKu8 ENDIAN)
{
	DKbuffer *buffer = NULL;
	unsafe_start();
	struct_createFromNothing(DKbuffer,DKu8,buffer);
	buffer_calculateEndian(ENDIAN,buffer->endian);
	error_bypassReturn();
	buffer->offset = 0;
	return buffer;
};

DKbuffer *dkBuffer_createFromMemory(DKu8 *SOURCE,DKusize SIZE,DKssize START,DKssize END,DKu8 ENDIAN)
{
	DKbuffer *buffer = NULL;
	unsafe_start();
	struct_createFromMemory(DKbuffer,DKu8,SOURCE,SIZE,START,END,buffer);
	buffer_calculateEndian(ENDIAN,buffer->endian);
	error_bypassReturn();
	buffer->offset = 0;
	return buffer;
};

DKbuffer *dkBuffer_createFromFile(DKnstring FILE_NAME,DKssize START,DKssize END,DKu8 ENDIAN)
{
	DKbuffer *buffer = NULL;
	unsafe_start();
	struct_createFromFile(DKbuffer,DKu8,FILE_NAME,"rb",START,END,buffer);
	buffer_calculateEndian(ENDIAN,buffer->endian);
	error_bypassReturn();
	buffer->offset = 0;
	return buffer;
};

DKbuffer *dkBuffer_createFromCopy(DKbuffer *BUFFER,DKssize START,DKssize END)
{
	DKbuffer *buffer = NULL;
	safe_start(BUFFER);
	struct_createFromMemory(DKbuffer,DKu8,(BUFFER->stream).start,(BUFFER->stream).size,START,END,buffer);
	buffer->endian = BUFFER->endian;
	buffer->offset = 0;
	safe_endReturn(BUFFER,buffer);
};

DKbuffer *dkBuffer_destroy(DKbuffer *BUFFER)
{
	safe_start(BUFFER);
	struct_destroy(BUFFER);
	return NULL;
};
