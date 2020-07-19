void dkBuffer_save(DKbuffer *BUFFER,DKssize START,DKssize END,DKnstring FILE_NAME)
{
	safe_start(BUFFER);
	stream_save(BUFFER->stream,START,END,FILE_NAME,"wb");
	safe_end(BUFFER);
};

void dkBuffer_merge(DKbuffer *BUFFER,DKssize OFFSET,DKbuffer *SOURCE,DKssize START,DKssize END)
{
	safe_start(BUFFER);
	mutex_lock(SOURCE->mutex);
	stream_merge(BUFFER->stream,DKu8,OFFSET,SOURCE->stream,START,END)
	mutex_unlock(SOURCE->mutex);
	safe_end(BUFFER);
};

void dkBuffer_clear(DKbuffer *BUFFER)
{
	safe_start(BUFFER);
	stream_clear(BUFFER->stream,DKu8);
	safe_end(BUFFER);
};

DKboolean dkBuffer_compare(DKbuffer *BUFFER1,DKbuffer *BUFFER2)
{
	safe_start(BUFFER1);
	mutex_lock(BUFFER2->mutex);
	DKboolean comparison = stream_compare(BUFFER1->stream,BUFFER2->stream,DKu8);
	mutex_unlock(BUFFER2->mutex);
	safe_endReturn(BUFFER1,comparison);
};
