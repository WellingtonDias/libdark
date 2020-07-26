#alias char_isSpace(BUFFER,INDEX)
{
	(block_getSource(BUFFER)[INDEX] == ' ') || (block_getSource(BUFFER)[INDEX] == '\t') || (block_getSource(BUFFER)[INDEX] == '\v') || (block_getSource(BUFFER)[INDEX] == '\f') || (block_getSource(BUFFER)[INDEX] == '\r') || (block_getSource(BUFFER)[INDEX] == '\n')
};

#alias char_isNotSpace(BUFFER,INDEX)
{
	(block_getSource(BUFFER)[INDEX] != ' ') && (block_getSource(BUFFER)[INDEX] != '\t') && (block_getSource(BUFFER)[INDEX] != '\v') && (block_getSource(BUFFER)[INDEX] != '\f') && (block_getSource(BUFFER)[INDEX] != '\r') && (block_getSource(BUFFER)[INDEX] != '\n')
};

#alias char_isLetter(BUFFER,INDEX)
{
	((block_getSource(BUFFER)[INDEX] >= 97) && (block_getSource(BUFFER)[INDEX] <= 122)) || ((block_getSource(BUFFER)[INDEX] >= 65) && (block_getSource(BUFFER)[INDEX] <= 90))
};

#alias char_isNotLetter(BUFFER,INDEX)
{
	!((block_getSource(BUFFER)[INDEX] >= 97) && (block_getSource(BUFFER)[INDEX] <= 122)) && !((block_getSource(BUFFER)[INDEX] >= 65) && (block_getSource(BUFFER)[INDEX] <= 90))
};

#alias char_isLowerCase(BUFFER,INDEX)
{
	(block_getSource(BUFFER)[INDEX] >= 97) && (block_getSource(BUFFER)[INDEX] <= 122)
};

#alias char_isUpperCase(BUFFER,INDEX)
{
	(block_getSource(BUFFER)[INDEX] >= 65) && (block_getSource(BUFFER)[INDEX] <= 90)
};

#macro char_toLowerCase(BUFFER,INDEX)
{
	block_getSource(BUFFER)[INDEX] += 32;
};

#macro char_toUpperCase(BUFFER,INDEX)
{
	block_getSource(BUFFER)[INDEX] -= 32;
};

#macro char_toConditionedCase(BUFFER,INDEX,CASE)
{
	if (CASE)
	{
		if (char_isLowerCase(BUFFER,INDEX)) char_toUpperCase(BUFFER,INDEX);
	}
	else if (char_isUpperCase(BUFFER,INDEX)) char_toLowerCase(BUFFER,INDEX);
};

#macro string_calculateLeadingSpace(BUFFER,INDEX)
{
	#local DKusize i;
	for (i = 0; i < block_getLength(BUFFER); ++i)
	{
		if (char_isNotSpace(BUFFER,i)) break;
	};
	INDEX = i;
};

#macro string_calculateTrailingSpace(BUFFER,INDEX)
{
	#local DKusize i;
	for (i = 0; i < block_getLength(BUFFER); ++i)
	{
		if (char_isNotSpace(BUFFER,(block_getLength(BUFFER) - 1) - i)) break;
	};
	INDEX = block_getLength(BUFFER) - i;
};

#macro string_removeSpace(BUFFER,START,END)
{
	#local DKusize length;
	for (length = 0; START + length < END; ++length)
	{
		if (char_isNotSpace(BUFFER,START + length)) break;
	};
	if (length > 0)
	{
		buffer_remove(BUFFER,DKcharacter,START,length);
		END -= length;
	};
};

#macro string_removeAllSpace(BUFFER,CASE)
{
	#local DKboolean case;
	#local DKusize start;
	#local DKusize end;
	string_calculateLeadingSpace(BUFFER,start);
	if (start < block_getLength(BUFFER))
	{
		string_calculateTrailingSpace(BUFFER,end);
		char_toConditionedCase(BUFFER,start,CASE);
		case = !case;
		for (++start; start < end; ++start)
		{
			if (char_isSpace(BUFFER,start))
			{
				string_removeSpace(BUFFER,start,end);
				char_toConditionedCase(BUFFER,start,case);
				case = !case;
			};
		};
	};
};

#macro string_replaceAllSpace(BUFFER,CHARACTER)
{
	#local DKusize start;
	#local DKusize end;
	string_calculateLeadingSpace(BUFFER,start);
	string_calculateTrailingSpace(BUFFER,end);
	for (; start < end; ++start)
	{
		if (char_isSpace(BUFFER,start))
		{
			block_getSource(BUFFER)[start] = CHARACTER;
			string_removeSpace(BUFFER,start + 1,end);
		};
	};
};

#macro string_toLowerCase(BUFFER)
{
	for (DKusize i = 0; i < block_getLength(BUFFER); ++i)
	{
		if (char_isUpperCase(BUFFER,i)) char_toLowerCase(BUFFER,i);
	};
};

#macro string_toUpperCase(BUFFER)
{
	for (DKusize i = 0; i < block_getLength(BUFFER); ++i)
	{
		if (char_isLowerCase(BUFFER,i)) char_toUpperCase(BUFFER,i);
	};
};

#macro string_trimStart(BUFFER)
{
	#local DKusize start;
	string_calculateLeadingSpace(BUFFER,start);
	if (start > 0) buffer_remove(BUFFER,DKcharacter,0,start);
};

#macro string_trimEnd(BUFFER)
{
	#local DKusize end;
	string_calculateTrailingSpace(BUFFER,end);
	if (end < block_getLength(BUFFER)) buffer_remove(BUFFER,DKcharacter,end,block_getLength(BUFFER) - end);
};

DKcharacter dkString_getCode(DKstring *STRING,DKssize INDEX)
{
	DKusize index;
	safe_start(STRING);
	block_calculateSafePosition(INDEX,block_getLength(STRING->block),index);
	safe_bypassReturn(STRING);
	DKcharacter code = block_getSource(STRING->block)[index];
	safe_endReturnValue(STRING,code);
};

DKnullString dkString_getCharacter(DKstring *STRING,DKssize INDEX)
{
	DKnullString character;
	DKusize index;
	safe_start(STRING);
	block_calculateSafePosition(INDEX,block_getLength(STRING->block),index);
	safe_bypassReturn(STRING);
	if (!(character = malloc(2))) error_throwReturn("MEMORY: malloc");
	character[0] = block_getSource(STRING->block)[index];
	character[1] = '\0';
	safe_endReturnValue(STRING,character);
};

DKnullString dkString_getNullString(DKstring *STRING,DKssize START,DKssize END)
{
	DKnullString nullString;
	DKusize index;
	DKusize length;
	safe_start(STRING);
	block_calculateRange(START,END,block_getLength(STRING->block),index,length);
	safe_bypassReturn(STRING);
	if (!(nullString = malloc(length + 1))) error_throwReturn("MEMORY: malloc");
	memcpy(nullString,block_getSource(STRING->block) + index,length);
	nullString[length] = '\0';
	safe_endReturnValue(STRING,nullString);
};

void dkString_toLowerCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toLowerCase(STRING->block);
	safe_endExit(STRING);
};

void dkString_toUpperCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toUpperCase(STRING->block);
	safe_endExit(STRING);
};

void dkString_toProperCase(DKstring *STRING)
{
	safe_start(STRING);
	if (block_isNotEmpty(STRING->block))
	{
		if (char_isLowerCase(STRING->block,0)) char_toUpperCase(STRING->block,0);
		for (DKusize i = 1; i < block_getLength(STRING->block); ++i) char_toConditionedCase(STRING->block,i,char_isSpace(STRING->block,i - 1));
	};
	safe_endExit(STRING);
};

void dkString_toInvertedCase(DKstring *STRING)
{
	safe_start(STRING);
	for (DKusize i = 0; i < block_getLength(STRING->block); ++i)
	{
		if (char_isUpperCase(STRING->block,i)) char_toLowerCase(STRING->block,i)
		else if (char_isLowerCase(STRING->block,i)) char_toUpperCase(STRING->block,i);
	};
	safe_endExit(STRING);
};

void dkString_toAlternatedCase(DKstring *STRING)
{
	safe_start(STRING);
	for (DKusize i = 0; i < block_getLength(STRING->block); ++i) char_toConditionedCase(STRING->block,i,i % 2);
	safe_endExit(STRING);
};

void dkString_toRandomCase(DKstring *STRING)
{
	safe_start(STRING);
	srand(time(0));
	for (DKusize i = 0; i < block_getLength(STRING->block); ++i) char_toConditionedCase(STRING->block,i,rand() % 2);
	safe_endExit(STRING);
};

void dkString_toLowerSnakeCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toLowerCase(STRING->block);
	string_replaceAllSpace(STRING->block,'_');
	safe_endExit(STRING);
};

void dkString_toUpperSnakeCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toUpperCase(STRING->block);
	string_replaceAllSpace(STRING->block,'_');
	safe_endExit(STRING);
};

void dkString_toLowerKebabCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toLowerCase(STRING->block);
	string_replaceAllSpace(STRING->block,'-');
	safe_endExit(STRING);
};

void dkString_toUpperKebabCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toUpperCase(STRING->block);
	string_replaceAllSpace(STRING->block,'-');
	safe_endExit(STRING);
};

void dkString_toCamelCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toLowerCase(STRING->block);
	string_removeAllSpace(STRING->block,false);
	safe_endExit(STRING);
};

void dkString_toPascalCase(DKstring *STRING)
{
	safe_start(STRING);
	string_toLowerCase(STRING->block);
	string_removeAllSpace(STRING->block,true);
	safe_endExit(STRING);
};

void dkString_trimStart(DKstring *STRING)
{
	safe_start(STRING);
	string_trimStart(STRING->block);
	safe_endExit(STRING);
};

void dkString_trimInner(DKstring *STRING)
{
	DKusize start;
	DKusize end;
	safe_start(STRING);
	string_calculateLeadingSpace(STRING->block,start);
	string_calculateTrailingSpace(STRING->block,end);
	for (; start < end; ++start)
	{
		if (char_isSpace(STRING->block,start)) string_removeSpace(STRING->block,start,end);
	};
	safe_endExit(STRING);
};

void dkString_trimEnd(DKstring *STRING)
{
	safe_start(STRING);
	string_trimEnd(STRING->block);
	safe_endExit(STRING);
};

void dkString_trimOuter(DKstring *STRING)
{
	safe_start(STRING);
	string_trimStart(STRING->block);
	string_trimEnd(STRING->block);
	safe_endExit(STRING);
};
