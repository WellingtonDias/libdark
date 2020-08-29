DKlist *dkList_create(void)
{
	DKlist *list;
	error_throwUnhandled();
	struct_create(DKlist,DKundefined,list);
	return list;
};

DKlist *dkList_createFromPointer(DKundefined *ADDRESS,DKusize SIZE)
{
	DKlist *list;
	error_throwUnhandled();
	struct_createFromPointer(DKlist,DKundefined,ADDRESS,SIZE,list);
	return list;
};

DKlist *dkList_createFromMemory(DKundefined *ADDRESS,DKusize SIZE,DKssize START,DKssize END)
{
	DKlist *list;
	error_throwUnhandled();
	struct_createFromMemory(DKlist,DKundefined,ADDRESS,SIZE,START,END,list);
	return list;
};

DKlist *dkList_createFromCopy(DKlist *LIST,DKssize START,DKssize END)
{
	DKlist *list;
	safe_start(LIST);
	struct_createFromCopy(DKlist,DKundefined,LIST,START,END,list);
	safe_endReturn(LIST,list);
};

DKlist *dkList_destroy(DKlist *LIST,DKboolean SOURCE)
{
	safe_start(LIST);
	struct_destroy(LIST,SOURCE);
	return NULL;
};
