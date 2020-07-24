// #alias string_isSpace(STREAM,INDEX)
// {
// 	(STREAM.source[INDEX] == ' ') || (STREAM.source[INDEX] == '\t') || (STREAM.source[INDEX] == '\v') || (STREAM.source[INDEX] == '\f') || (STREAM.source[INDEX] == '\r') || (STREAM.source[INDEX] == '\n')
// };

// #alias string_isLowerCase(STREAM,INDEX)
// {
// 	(STREAM.source[INDEX] >= 97) && (STREAM.source[INDEX] <= 122)
// };

// #alias string_isUpperCase(STREAM,INDEX)
// {
// 	(STREAM.source[INDEX] >= 65) && (STREAM.source[INDEX] <= 90)
// };

// #macro string_toLowerCase(STREAM,INDEX)
// {
// 	STREAM.source[INDEX] += 32;
// };

// #macro string_toUpperCase(STREAM,INDEX)
// {
// 	STREAM.source[INDEX] -= 32;
// };

// #macro string_lowerCase(STREAM)
// {
// 	for (DKusize i = 0; i < STREAM.size; ++i)
// 	{
// 		if (string_isUpperCase(STREAM,i)) string_toLowerCase(STREAM,i);
// 	};
// };

// #macro string_upperCase(STREAM)
// {
// 	for (DKusize i = 0; i < STREAM.size; ++i)
// 	{
// 		if (string_isLowerCase(STREAM,i)) string_toUpperCase(STREAM,i);
// 	};
// };

// #macro string_properCase(STREAM)
// {
// 	if (string_isLowerCase(STREAM,0)) string_toUpperCase(STREAM,0);
// 	for (DKusize i = 1; i < STREAM.size; ++i)
// 	{
// 		if (string_isSpace(STREAM,i - 1))
// 		{
// 			if (string_isLowerCase(STREAM,i)) string_toUpperCase(STREAM,i);
// 		}
// 		else if (string_isUpperCase(STREAM,i)) string_toLowerCase(STREAM,i);
// 	};
// };

// #macro string_alternateCase(STREAM)
// {
// 	for (DKusize i = 0; i < STREAM.size; ++i)
// 	{
// 		if (i % 2)
// 		{
// 			if (string_isUpperCase(STREAM,i)) string_toLowerCase(STREAM,i);
// 		}
// 		else if (string_isLowerCase(STREAM,i)) string_toUpperCase(STREAM,i);
// 	};
// };

// #macro string_invertCase(STREAM)
// {
// 	for (DKusize i = 0; i < STREAM.size; ++i)
// 	{
// 		if (string_isUpperCase(STREAM,i)) string_toLowerCase(STREAM,i)
// 		else if (string_isLowerCase(STREAM,i)) string_toUpperCase(STREAM,i);
// 	};
// };

// void dkString_convert(DKstring *STRING,DKu8 TYPE)
// {
// 	safe_start(STRING);
// 	switch (TYPE)
// 	{
// 		case DARK_STRING_LOWER_CASE: string_lowerCase(STRING->block); break;
// 		case DARK_STRING_UPPER_CASE: string_upperCase(STRING->block); break;
// 		case DARK_STRING_PROPER_CASE: string_properCase(STRING->block); break;
// 		case DARK_STRING_ALTERNATE_CASE: string_alternateCase(STRING->block); break;
// 		case DARK_STRING_INVERT_CASE: string_invertCase(STRING->block); break;
// 		default: error_throw("invalid TYPE");
// 	};
// 	safe_end(STRING);
// };

// #macro string_trimStart(STREAM)
// {
// 	#local DKusize i;
// 	for (i = 0; i < STREAM.size; ++i)
// 	{
// 		if (!string_isSpace(STREAM,i)) break;
// 	};
// 	if (i > 0) blob_remove(STREAM,DKcharacter,0,i);
// };

// #macro string_trimEnd(STREAM)
// {
// 	#local DKusize i;
// 	for (i = 0; i < STREAM.size; ++i)
// 	{
// 		if (!string_isSpace(STREAM,(STREAM.size - 1) - i)) break;
// 	};
// 	if (i > 0) blob_remove(STREAM,DKcharacter,STREAM.size - i,i);
// };

// void dkString_trim(DKstring *STRING,DKu8 TYPE)
// {
// 	safe_start(STRING);
// 	switch (TYPE)
// 	{
// 		case DARK_STRING_TRIM_START: string_trimStart(STRING->block); break;
// 		case DARK_STRING_TRIM_END: string_trimEnd(STRING->block); break;
// 		case DARK_STRING_TRIM_ALL:
// 		{
// 			string_trimStart(STRING->block);
// 			string_trimEnd(STRING->block);
// 			break;
// 		};
// 		default: error_throw("invalid TYPE");
// 	};
// 	safe_end(STRING);
// };
