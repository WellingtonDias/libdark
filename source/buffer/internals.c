#macro buffer_getScalar(BUFFER,SCALAR,TYPE,SOURCE,SIZE)
{
	if (TYPE < DARK_BUFFER_NSTRING)
	{
		SOURCE = (DKu8*) &SCALAR;
		SIZE = BufferSize[TYPE];
	}
	else
	{
		switch (TYPE)
		{
			case DARK_BUFFER_NSTRING:
			case DARK_BUFFER_RSTRING:
			{
				SOURCE = (DKu8*) SCALAR.nstring;
				SIZE = strlen(SCALAR.nstring);
				if (TYPE == DARK_BUFFER_NSTRING) ++SIZE;
				else if (SIZE == 0) error_throw("invalid SOURCE");
				break;
			};
			default: error_throw("invalid TYPE");
		};
	};
};

#macro buffer_getStringLength(BLOCK,OFFSET,LENGTH)
{
	if (OFFSET >= BLOCK.size) error_throwCastReturn("invalid OFFSET",DKscalar);
	while (true)
	{
		if (BLOCK.source[OFFSET + LENGTH] == '\0') break;
		++LENGTH;
		if (OFFSET + LENGTH == BLOCK.size) error_throwCastReturn("invalid TYPE",DKscalar);
	};
	++LENGTH;
};

#macro buffer_readScalar(BLOCK,OFFSET,TYPE,SCALAR,SIZE)
{
	if (TYPE > DARK_BUFFER_NSTRING) error_throwCastReturn("invalid TYPE",DKscalar);
	if (TYPE != DARK_BUFFER_NSTRING)
	{
		SIZE = BufferSize[TYPE];
		if ((DKssize) OFFSET > (DKssize) BLOCK.size - (DKssize) SIZE) error_throwCastReturn("invalid OFFSET",DKscalar);
		memcpy(&SCALAR,BLOCK.source + OFFSET,SIZE);
	}
	else
	{
		buffer_getStringLength(BLOCK,OFFSET,SIZE);
		error_bypassCastReturn(DKscalar);
		if (!(SCALAR.nstring = malloc(SIZE))) error_throwCastReturn("MEMORY: malloc",DKscalar);
		memcpy(SCALAR.nstring,BLOCK.source + OFFSET,SIZE);
	};
};

#macro buffer_readRaw(BLOCK,OFFSET,SIZE,SOURCE)
{
	if (SIZE > BLOCK.size) error_throwReturn("invalid SIZE");
	if ((DKssize) OFFSET > (DKssize) BLOCK.size - (DKssize) SIZE) error_throwReturn("invalid OFFSET");
	if (!(SOURCE = malloc(SIZE))) error_throwReturn("MEMORY: malloc");
	memcpy(SOURCE,BLOCK.source + OFFSET,SIZE);
};

#macro buffer_erase(BLOCK,OFFSET,SIZE)
{
	#local DKusize offset;
	helper_calculateUnsafePosition(OFFSET,BLOCK.size,offset);
	error_bypass();
	block_erase(BLOCK,DKu8,offset,SIZE);
};

#macro buffer_remove(BLOCK,OFFSET,SIZE)
{
	#local DKusize offset;
	helper_calculateUnsafePosition(OFFSET,BLOCK.size,offset);
	error_bypass();
	block_remove(BLOCK,DKu8,offset,SIZE);
};

#macro buffer_calculateEndian(BUFFER,VALUE,ENDIAN)
{
	switch (VALUE)
	{
		case DARK_BUFFER_UNDEFINED_ENDIAN:
		case DARK_BUFFER_LITTLE_ENDIAN:
		case DARK_BUFFER_BIG_ENDIAN: ENDIAN = VALUE; break;
		case DARK_BUFFER_SYSTEM_ENDIAN: ENDIAN = DARK_ENDIAN; break;
		default: error_set("invalid ENDIAN");
	};
};

#macro buffer_calculateOffset(BUFFER,KIND,VALUE,OFFSET)
{
	switch (KIND)
	{
		case DARK_START: OFFSET = VALUE; break;
		case DARK_CURRENT: OFFSET = BUFFER->offset + VALUE; break;
		case DARK_END: OFFSET = (BUFFER->block).size + VALUE; break;
		default: error_throwReturn("invalid KIND");
	};
	if (OFFSET < 0) error_throwReturn("invalid OFFSET");
};
