void dkList_insert(DKlist *LIST,DKssize INDEX,DKundefined VALUE)
{
	safe_start(LIST);
	block_insertElement(DKundefined,LIST->block,INDEX,VALUE);
	safe_endExit(LIST);
};

void dkList_prepend(DKlist *LIST,DKundefined VALUE)
{
	safe_start(LIST);
	block_insertElementAtStart(DKundefined,LIST->block,VALUE);
	safe_endExit(LIST);
};

void dkList_append(DKlist *LIST,DKundefined VALUE)
{
	safe_start(LIST);
	block_insertElementAtEnd(DKundefined,LIST->block,VALUE);
	safe_endExit(LIST);
};

DKundefined dkList_replace(DKlist *LIST,DKssize INDEX,DKundefined VALUE)
{
	DKundefined value;
	safe_start(LIST);
	block_replaceElement(DKundefined,LIST->block,INDEX,VALUE,value);
	safe_endReturn(LIST,value);
};

DKundefined dkList_set(DKlist *LIST,DKssize INDEX,DKundefined VALUE)
{
	DKundefined value;
	safe_start(LIST);
	block_setElement(DKundefined,LIST->block,INDEX,VALUE,value);
	safe_endReturn(LIST,value);
};

DKundefined dkList_get(DKlist *LIST,DKssize INDEX)
{
	DKundefined value;
	safe_start(LIST);
	block_getElement(DKundefined,LIST->block,INDEX,value);
	safe_endReturn(LIST,value);
};

DKundefined dkList_getFront(DKlist *LIST)
{
	DKundefined value;
	safe_start(LIST);
	block_getElementAtStart(DKundefined,LIST->block,value);
	safe_endReturn(LIST,value);
};

DKundefined dkList_getRear(DKlist *LIST)
{
	DKundefined value;
	safe_start(LIST);
	block_getElementAtEnd(DKundefined,LIST->block,value);
	safe_endReturn(LIST,value);
};

DKundefined dkList_remove(DKlist *LIST,DKssize INDEX)
{
	DKundefined value;
	safe_start(LIST);
	block_removeElement(DKundefined,LIST->block,INDEX,value);
	safe_endReturn(LIST,value);
};

DKundefined dkList_dequeue(DKlist *LIST)
{
	DKundefined value;
	safe_start(LIST);
	block_removeElementAtStart(DKundefined,LIST->block,value);
	safe_endReturn(LIST,value);
};

DKundefined dkList_pop(DKlist *LIST)
{
	DKundefined value;
	safe_start(LIST);
	block_removeElementAtEnd(DKundefined,LIST->block,value);
	safe_endReturn(LIST,value);
};

void dkList_map(DKlist *LIST,DKundefined (*CALLBACK)(DKlist *LIST,DKusize INDEX,DKundefined VALUE))
{
	safe_start(LIST);
	block_map(DKundefined,LIST->block,CALLBACK,LIST);
	safe_endExit(LIST);
};

void dkList_filter(DKlist *LIST,DKboolean (*CALLBACK)(DKlist *LIST,DKusize INDEX,DKundefined VALUE))
{
	safe_start(LIST);
	block_filter(DKundefined,LIST->block,CALLBACK,LIST);
	safe_endExit(LIST);
};

DKundefined dkList_reduce(DKlist *LIST,DKundefined (*CALLBACK)(DKlist *LIST,DKusize INDEX,DKundefined VALUE,DKundefined ACCUMULATOR))
{
	DKundefined value = (DKundefined) 0;
	safe_start(LIST);
	block_reduce(DKundefined,LIST->block,CALLBACK,LIST,value);
	safe_endReturn(LIST,value);
};
