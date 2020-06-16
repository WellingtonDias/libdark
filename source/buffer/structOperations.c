void dkBuffer_save(DKbuffer *BUFFER,DKssize START,DKssize END,DKchar *FILE_NAME)
{
	safe_start(BUFFER);
	blob_save(BUFFER,START,END,FILE_NAME,"wb");
	safe_end(BUFFER);
}

void dkBuffer_merge(DKbuffer *BUFFER,DKssize OFFSET,DKbuffer *SOURCE,DKssize START,DKssize END)
{
	safe_start(BUFFER);
	mutex_lock(SOURCE->mutex);
	block_merge(BUFFER->block,DKu8,OFFSET,SOURCE->block,START,END)
	mutex_unlock(SOURCE->mutex);
	safe_end(BUFFER);
}

void dkBuffer_clear(DKbuffer *BUFFER)
{
	safe_start(BUFFER);
	block_clear(BUFFER->block,DKu8);
	safe_end(BUFFER);
}

DKboolean dkBuffer_compare(DKbuffer *BUFFER1,DKbuffer *BUFFER2)
{
	safe_start(BUFFER1);
	mutex_lock(BUFFER2->mutex);
	DKboolean comparison = block_compare(BUFFER1->block,BUFFER2->block,DKu8);
	mutex_unlock(BUFFER2->mutex);
	safe_endReturn(BUFFER1,comparison);
}
