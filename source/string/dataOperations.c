#alias string_isSpace(BLOCK,INDEX)
{
	(BLOCK.source[INDEX] == ' ') || (BLOCK.source[INDEX] == '\t') || (BLOCK.source[INDEX] == '\v') || (BLOCK.source[INDEX] == '\f') || (BLOCK.source[INDEX] == '\r') || (BLOCK.source[INDEX] == '\n')
};

#alias string_isLowerCase(BLOCK,INDEX)
{
	(BLOCK.source[INDEX] >= 97) && (BLOCK.source[INDEX] <= 122)
};

#alias string_isUpperCase(BLOCK,INDEX)
{
	(BLOCK.source[INDEX] >= 65) && (BLOCK.source[INDEX] <= 90)
};

#macro string_toLowerCase(BLOCK,INDEX)
{
	BLOCK.source[INDEX] += 32;
};

#macro string_toUpperCase(BLOCK,INDEX)
{
	BLOCK.source[INDEX] -= 32;
};

#macro string_lowerCase(BLOCK)
{
	for (DKusize i = 0; i < BLOCK.size; ++i)
	{
		if (string_isUpperCase(BLOCK,i)) string_toLowerCase(BLOCK,i);
	};
};

#macro string_upperCase(BLOCK)
{
	for (DKusize i = 0; i < BLOCK.size; ++i)
	{
		if (string_isLowerCase(BLOCK,i)) string_toUpperCase(BLOCK,i);
	};
};

#macro string_properCase(BLOCK)
{
	if (string_isLowerCase(BLOCK,0)) string_toUpperCase(BLOCK,0);
	for (DKusize i = 1; i < BLOCK.size; ++i)
	{
		if (string_isSpace(BLOCK,i - 1))
		{
			if (string_isLowerCase(BLOCK,i)) string_toUpperCase(BLOCK,i);
		}
		else if (string_isUpperCase(BLOCK,i)) string_toLowerCase(BLOCK,i);
	};
};

#macro string_alternateCase(BLOCK)
{
	for (DKusize i = 0; i < BLOCK.size; ++i)
	{
		if (i % 2)
		{
			if (string_isUpperCase(BLOCK,i)) string_toLowerCase(BLOCK,i);
		}
		else if (string_isLowerCase(BLOCK,i)) string_toUpperCase(BLOCK,i);
	};
};

#macro string_invertCase(BLOCK)
{
	for (DKusize i = 0; i < BLOCK.size; ++i)
	{
		if (string_isUpperCase(BLOCK,i)) string_toLowerCase(BLOCK,i)
		else if (string_isLowerCase(BLOCK,i)) string_toUpperCase(BLOCK,i);
	};
};

void dkString_convert(DKstring *STRING,DKu8 TYPE)
{
	safe_start(STRING);
	switch (TYPE)
	{
		case DARK_STRING_LOWER_CASE: string_lowerCase(STRING->block); break;
		case DARK_STRING_UPPER_CASE: string_upperCase(STRING->block); break;
		case DARK_STRING_PROPER_CASE: string_properCase(STRING->block); break;
		case DARK_STRING_ALTERNATE_CASE: string_alternateCase(STRING->block); break;
		case DARK_STRING_INVERT_CASE: string_invertCase(STRING->block); break;
		default: error_throw("invalid TYPE");
	};
	safe_end(STRING);
};

#macro string_trimStart(BLOCK)
{
	#local DKusize i;
	for (i = 0; i < BLOCK.size; ++i)
	{
		if (!string_isSpace(BLOCK,i)) break;
	};
	if (i > 0) block_remove(BLOCK,DKcharacter,0,i);
};

#macro string_trimEnd(BLOCK)
{
	#local DKusize i;
	for (i = 0; i < BLOCK.size; ++i)
	{
		if (!string_isSpace(BLOCK,(BLOCK.size - 1) - i)) break;
	};
	if (i > 0) block_remove(BLOCK,DKcharacter,BLOCK.size - i,i);
};

void dkString_trim(DKstring *STRING,DKu8 TYPE)
{
	safe_start(STRING);
	switch (TYPE)
	{
		case DARK_STRING_TRIM_START: string_trimStart(STRING->block); break;
		case DARK_STRING_TRIM_END: string_trimEnd(STRING->block); break;
		case DARK_STRING_TRIM_ALL:
		{
			string_trimStart(STRING->block);
			string_trimEnd(STRING->block);
			break;
		};
		default: error_throw("invalid TYPE");
	};
	safe_end(STRING);
};
