DKordinal *dkOrdinal_create(void)
{
	DKordinal *ordinal;
	unsafe_start();
	struct_createFromNothing(DKordinal,DKhandle,ordinal);
	return ordinal;
};

DKordinal *dkOrdinal_createFromCopy(DKordinal *ORDINAL,DKssize START,DKssize END)
{
	DKordinal *ordinal;
	safe_start(ORDINAL);
	struct_createFromMemory(DKordinal,DKhandle,(ORDINAL->block).start,(ORDINAL->block).size,START,END,ordinal);
	safe_endReturn(ORDINAL,ordinal);
};

DKordinal *dkOrdinal_destroy(DKordinal *ORDINAL)
{
	safe_start(ORDINAL);
	struct_destroy(ORDINAL);
	return NULL;
};
