#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	DKstring *string1 = dkString_createFromMemory("              Hello ",0,3,-1);
	dkString_debug(string1,"createFromMemory");

	DKstring *string2 = dkString_createFromFile("./example/stringLoad",0,-1);
	dkString_debug(string2,"createFromFile");

	DKstring *string3 = dkString_createFromCopy(string1,0,-1);
	dkString_debug(string3,"createFromCopy");
	dkString_merge(string3,-1,string2,0,-1);
	dkString_debug(string3,"merge");
	dkString_saveToFile(string3,0,-1,"./example/stringSave");

	DKstring *string4 = dkString_createFromCopy(string3,0,-1);
	printf("COMPARE: %lli\n",(DKusize) dkString_compare(string4,string3));
	dkString_trimStart(string4);
	dkString_debug(string4,"trimStart");
	dkString_trimEnd(string4);
	dkString_debug(string4,"trimEnd");
	dkString_trimInner(string4);
	dkString_debug(string4,"trimInner");

	DKstring *string5 = dkString_createFromCopy(string3,0,-1);
	dkString_trimOuter(string5);
	dkString_debug(string5,"trimOuter");
	dkString_toLowerCase(string5);
	dkString_debug(string5,"toLowerCase");
	dkString_toUpperCase(string5);
	dkString_debug(string5,"toUpperCase");
	dkString_toProperCase(string5);
	dkString_debug(string5,"toProperCase");
	dkString_invertCase(string5);
	dkString_debug(string5,"invertCase");
	dkString_alternateCase(string5);
	dkString_debug(string5,"alternateCase");
	dkString_toRandomCase(string5);
	dkString_debug(string5,"toRandomCase");
	dkString_toLowerSnakeCase(string5);
	dkString_debug(string5,"toLowerSnakeCase");
	dkString_toUpperSnakeCase(string5);
	dkString_debug(string5,"toUpperSnakeCase");

	DKstring *string6 = dkString_createFromCopy(string3,0,-1);
	dkString_trimOuter(string6);
	dkString_toCamelCase(string6);
	dkString_debug(string6,"toCamelCase");

	DKstring *string7 = dkString_createFromCopy(string3,0,-1);
	dkString_trimOuter(string7);
	dkString_toPascalCase(string7);
	dkString_debug(string7,"toPascalCase");

	DKstring *string8 = dkString_createFromCopy(string3,0,-1);
	dkString_trimOuter(string8);
	dkString_toLowerKebabCase(string8);
	dkString_debug(string8,"toLowerKebabCase");
	dkString_toUpperKebabCase(string8);
	dkString_debug(string8,"toUpperKebabCase");
	dkString_saveToFile(string8,0,-1,"./example/stringSaveTrim");
	printf("CODE: %lli\n",(DKusize) dkString_getCode(string8,2));
	printf("CHARACTER: %.*s\n",1,dkString_getCharacter(string8,2));
	printf("SOURCE: %.*s\n",(DKu32) dkString_getLength(string8),dkString_getSource(string8));
	printf("LENGTH: %lli\n",dkString_getLength(string8));
	printf("EMPTY: %lli\n",(DKusize) dkString_isEmpty(string8));
	printf("NOT EMPTY: %lli\n",(DKusize) dkString_isNotEmpty(string8));
	dkString_clear(string8);
	dkString_debug(string8,"clear");

	dkString_destroy(string1);
	dkString_destroy(string2);
	dkString_destroy(string3);
	dkString_destroy(string5);
	dkString_destroy(string6);
	dkString_destroy(string7);
	dkString_destroy(string8);

	return EXIT_SUCCESS;
};
