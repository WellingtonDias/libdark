#macro string_calculateStartSpace(BUFFER,START)
{
	#local DKusize i;
	for (i = 0; i < BUFFER.size; ++i)
	{
		if (!string_isSpace(BUFFER,i)) break;
	};
	START = i;
};

#macro string_calculateEndSpace(BUFFER,END)
{
	#local DKusize i;
	for (i = 0; i < BUFFER.size; ++i)
	{
		if (!string_isSpace(BUFFER,(BUFFER.size - 1) - i)) break;
	};
	END = BUFFER.size - i;
};

#alias string_isSpace(BUFFER,INDEX)
{
	(BUFFER.start[INDEX] == ' ') || (BUFFER.start[INDEX] == '\t') || (BUFFER.start[INDEX] == '\v') || (BUFFER.start[INDEX] == '\f') || (BUFFER.start[INDEX] == '\r') || (BUFFER.start[INDEX] == '\n')
};

#alias string_isLetter(BUFFER,INDEX)
{
	((BUFFER.start[INDEX] >= 97) && (BUFFER.start[INDEX] <= 122)) || ((BUFFER.start[INDEX] >= 65) && (BUFFER.start[INDEX] <= 90))
};

#alias string_isLower(BUFFER,INDEX)
{
	(BUFFER.start[INDEX] >= 97) && (BUFFER.start[INDEX] <= 122)
};

#alias string_isUpper(BUFFER,INDEX)
{
	(BUFFER.start[INDEX] >= 65) && (BUFFER.start[INDEX] <= 90)
};

#macro string_toLower(BUFFER,INDEX)
{
	BUFFER.start[INDEX] += 32;
};

#macro string_toUpper(BUFFER,INDEX)
{
	BUFFER.start[INDEX] -= 32;
};

#macro string_toLowerCase(BUFFER)
{
	for (DKusize i = 0; i < BUFFER.size; ++i)
	{
		if (string_isUpper(BUFFER,i)) string_toLower(BUFFER,i);
	};
};

#macro string_toUpperCase(BUFFER)
{
	for (DKusize i = 0; i < BUFFER.size; ++i)
	{
		if (string_isLower(BUFFER,i)) string_toUpper(BUFFER,i);
	};
};

#macro string_toConditionalCase(BUFFER,INDEX,CASE)
{
	if (CASE)
	{
		if (string_isLower(BUFFER,INDEX)) string_toUpper(BUFFER,INDEX);
	}
	else if (string_isUpper(BUFFER,INDEX)) string_toLower(BUFFER,INDEX);
};

#macro string_removeSpace(BUFFER,INDEX,END)
{
	#local DKusize i;
	for (i = 0; INDEX + i < END; ++i)
	{
		if (!string_isSpace(BUFFER,INDEX + i)) break;
	};
	if (i > 0)
	{
		buffer_remove(BUFFER,DKcharacter,INDEX,i);
		END -= i;
	};
};

#macro string_removeAllSpace(BUFFER,CASE)
{
	#local DKboolean case;
	#local DKusize start;
	#local DKusize end;
	case = !case;
	string_calculateStartSpace(BUFFER,start);
	string_calculateEndSpace(BUFFER,end);
	string_toConditionalCase(BUFFER,start,CASE);
	for (++start; start < end; ++start)
	{
		if (string_isSpace(BUFFER,start))
		{
			string_removeSpace(BUFFER,start,end);
			if (start < end)
			{
				string_toConditionalCase(BUFFER,start,case);
				case = !case;
			};
		};
	};
};

// if (CASE)
// {
// 	if (string_isLower(BUFFER,start)) string_toUpper(BUFFER,start);
// }
// else if (string_isUpper(BUFFER,start)) string_toLower(BUFFER,start);

// if (case)
// {
// 	if (string_isLower(BUFFER,i)) string_toUpper(BUFFER,i);
// }
// else if (string_isUpper(BUFFER,i)) string_toLower(BUFFER,i);

#macro string_replaceSpace(BUFFER,CHARACTER)
{
	#local DKusize start;
	#local DKusize end;
	string_calculateStartSpace(BUFFER,start);
	string_calculateEndSpace(BUFFER,end);
	for (; start < end; ++start)
	{
		if (string_isSpace(BUFFER,start))
		{
			BUFFER.start[start] = CHARACTER;
			string_removeSpace(BUFFER,start + 1,end);
		};
	};
};

void dkString_toLowerCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toLowerCase(STRING->block);
	safe_end(STRING);
};

void dkString_toUpperCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toUpperCase(STRING->block);
	safe_end(STRING);
};

void dkString_toProperCase(DKstring *STRING)
{
	safe_start(STRING);
	if (string_isLower(STRING->block,0)) string_toUpper(STRING->block,0);
	for (DKusize i = 1; i < (STRING->block).size; ++i)
	{
		string_toConditionalCase(STRING->block,i,!string_isLetter(STRING->block,i - 1));
		// if (!string_isLetter(STRING->block,i - 1))
		// {
		// 	if (string_isLower(STRING->block,i)) string_toUpper(STRING->block,i);
		// }
		// else if (string_isUpper(STRING->block,i)) string_toLower(STRING->block,i);
	};
	safe_end(STRING);
};

void dkString_invertCase(DKstring *STRING)
{
	safe_start(STRING);
	for (DKusize i = 0; i < (STRING->block).size; ++i)
	{
		if (string_isUpper(STRING->block,i)) string_toLower(STRING->block,i)
		else if (string_isLower(STRING->block,i)) string_toUpper(STRING->block,i);
	};
	safe_end(STRING);
};

void dkString_alternateCase(DKstring *STRING)
{
	safe_start(STRING);
	for (DKusize i = 0; i < (STRING->block).size; ++i)
	{
		string_toConditionalCase(STRING->block,i,i % 2);
	};
	safe_end(STRING);
};

void dkString_toRandomCase(DKstring *STRING)
{
	safe_start(STRING);
	srand(time(0));
	for (DKusize i = 0; i < (STRING->block).size; ++i)
	{
		string_toConditionalCase(STRING->block,i,rand() % 2);
	};
	safe_end(STRING);
};

void dkString_toLowerSnakeCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toLowerCase(STRING->block);
	string_replaceSpace(STRING->block,'_');
	safe_end(STRING);
};

void dkString_toUpperSnakeCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toUpperCase(STRING->block);
	string_replaceSpace(STRING->block,'_');
	safe_end(STRING);
};

void dkString_toLowerKebabCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toLowerCase(STRING->block);
	string_replaceSpace(STRING->block,'-');
	safe_end(STRING);
};

void dkString_toUpperKebabCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toUpperCase(STRING->block);
	string_replaceSpace(STRING->block,'-');
	safe_end(STRING);
};

void dkString_toCamelCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toLowerCase(STRING->block);
	string_removeAllSpace(STRING->block,false);
	safe_end(STRING);
};

void dkString_toPascalCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toLowerCase(STRING->block);
	string_removeAllSpace(STRING->block,true);
	safe_end(STRING);
};

#macro string_trimStart(BUFFER)
{
	#local DKusize start;
	string_calculateStartSpace(BUFFER,start);
	if (start > 0) buffer_remove(BUFFER,DKcharacter,0,start);
};

#macro string_trimEnd(BUFFER)
{
	#local DKusize end;
	string_calculateEndSpace(BUFFER,end);
	if (end < BUFFER.size) buffer_remove(BUFFER,DKcharacter,end,BUFFER.size - end);
};

void dkString_trimStart(DKstring *STRING)
{
	safe_start(STRING);
	string_trimStart(STRING->block);
	safe_end(STRING);
};

void dkString_trimInner(DKstring *STRING)
{
	DKusize start;
	DKusize end;
	string_calculateStartSpace(STRING->block,start);
	string_calculateEndSpace(STRING->block,end);
	for (; start < end; ++start)
	{
		if (string_isSpace(STRING->block,start)) string_removeSpace(STRING->block,start,end);
	};
};

void dkString_trimEnd(DKstring *STRING)
{
	safe_start(STRING);
	string_trimEnd(STRING->block);
	safe_end(STRING);
};

void dkString_trimOuter(DKstring *STRING)
{
	safe_start(STRING);
	string_trimStart(STRING->block);
	string_trimEnd(STRING->block);
	safe_end(STRING);
};
