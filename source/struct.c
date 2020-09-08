#routine struct_allocate(#TYPE,STRUCT)
{
	if (!(STRUCT = calloc(1,sizeof(TYPE)))) exception_throwBreak("MEMORY: calloc");
};

#routine struct_create(#STRUCT_TYPE,#BOX_TYPE,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	box_create(BOX_TYPE,STRUCT->box);
};

#routine struct_createFromPointer(#STRUCT_TYPE,#BOX_TYPE,POINTER,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	box_createFromPointer(BOX_TYPE,STRUCT->box,POINTER);
};

#routine struct_createFromMemory(#STRUCT_TYPE,#BOX_TYPE,POINTER,START,END,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	box_createFromMemory(BOX_TYPE,STRUCT->box,POINTER,START,END);
};

#routine struct_createFromCopy(#STRUCT_TYPE,#BOX_TYPE,SOURCE,START,END,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	box_createFromCopy(BOX_TYPE,STRUCT->box,SOURCE->box,START,END);
};

#routine struct_destroy(STRUCT,SOURCE)
{
	box_destroy(STRUCT->box,SOURCE);
	mutex_destroy(STRUCT->mutex);
	free(STRUCT);
};
