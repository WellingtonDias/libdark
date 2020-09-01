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

#routine struct_createFromMemoryInInterval(#STRUCT_TYPE,#BOX_TYPE,POINTER,INDEX,SIZE,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	box_createFromMemoryInInterval(BOX_TYPE,STRUCT->box,POINTER,INDEX,SIZE);
};

#routine struct_createFromMemoryInRange(#STRUCT_TYPE,#BOX_TYPE,POINTER,START,END,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	box_createFromMemoryInRange(BOX_TYPE,STRUCT->box,POINTER,START,END);
};

#routine struct_createFromCopyInInterval(#STRUCT_TYPE,#BOX_TYPE,SOURCE,INDEX,SIZE,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	box_createFromCopyInInterval(BOX_TYPE,STRUCT->box,SOURCE->box,INDEX,SIZE);
};

#routine struct_createFromCopyInRange(#STRUCT_TYPE,#BOX_TYPE,SOURCE,START,END,STRUCT)
{
	struct_allocate(STRUCT_TYPE,STRUCT);
	box_createFromCopyInRange(BOX_TYPE,STRUCT->box,SOURCE->box,START,END);
};

#routine struct_destroy(STRUCT,SOURCE)
{
	if (SOURCE) box_destroy(STRUCT->box);
	mutex_destroy(STRUCT->mutex);
	free(STRUCT);
};
