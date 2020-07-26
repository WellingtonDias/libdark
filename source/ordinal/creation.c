DKordinal *dkOrdinal_create(void)
{
	DKordinal *ordinal;
	unsafe_start();
	struct_createFromNothing(DKordinal,DKvalue,ordinal);
	return ordinal;
};

DKordinal *dkOrdinal_createFromCopy(DKordinal *ORDINAL,DKssize START,DKssize END)
{
	DKordinal *ordinal;
	safe_start(ORDINAL);
	struct_createFromMemory(DKordinal,DKvalue,block_getSource(ORDINAL->block),block_getLength(ORDINAL->block),START,END,ordinal);
	safe_endReturnValue(ORDINAL,ordinal);
};

DKordinal *dkOrdinal_destroy(DKordinal *ORDINAL)
{
	safe_start(ORDINAL);
	struct_destroy(ORDINAL);
	return NULL;
};
