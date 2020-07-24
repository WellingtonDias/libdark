#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	DKchar *error;
	dkError_start();
		// DKstring *string0 = dkString_create(NULL,0,0,0);
		// if (!(error = dkError_catch())) dkString_debug(string0,"string0");
		// else dkError_debug(error);

		// DKstring *string00 = dkString_copy(string0,0,0);
		// if (!(error = dkError_catch())) dkString_debug(string00,"string00");
		// else dkError_debug(error);

		DKstring *string1 = dkString_extendedCreate("              Hello ",DARK_AUTO,0,-1);
		if (!(error = dkError_catch())) dkString_debug(string1,"create");
		else dkError_debug(error);

		// dkString_merge(string0,0,string1,0,-1);
		// if (!(error = dkError_catch())) dkString_debug(string0,"merge");
		// else dkError_debug(error);

		DKstring *string2 = dkString_load("./example/string_load",0,-3);
		dkString_debug(string2,"load");

		DKstring *string3 = dkString_copy(string1,0,-1);
		dkString_debug(string3,"copy");

		dkString_merge(string3,-1,string2,0,-1);
		dkString_debug(string3,"merge");

		dkString_save(string3,0,-1,"./example/string_save");

		DKstring *string4 = dkString_copy(string3,0,-1);
		dkString_trim(string4,DARK_STRING_START);
		dkString_debug(string4,"trim-start");
		dkString_trim(string4,DARK_STRING_END);
		dkString_debug(string4,"trim-end");

		DKstring *string5 = dkString_copy(string3,0,-1);
		dkString_trim(string5,DARK_STRING_ALL);
		if (!(error = dkError_catch())) dkString_debug(string5,"trim-all");
		else dkError_debug(error);

		dkString_convert(string5,DARK_STRING_LOWER_CASE);
		dkString_debug(string5,"lower-case");
		dkString_convert(string5,DARK_STRING_UPPER_CASE);
		dkString_debug(string5,"upper-case");
		dkString_convert(string5,DARK_STRING_PROPER_CASE);
		dkString_debug(string5,"proper-case");
		dkString_convert(string5,DARK_STRING_INVERT_CASE);
		dkString_debug(string5,"invert-case");
		dkString_convert(string5,DARK_STRING_ALTERNATE_CASE);
		dkString_debug(string5,"alternate-case");

		dkString_save(string5,0,-1,"./example/string_saveTrim");

		printf("CHARACTER: %c\n",dkString_getCharacter(string5,2));
		printf("SOURCE: %.*s\n",(DKu32) dkString_getLength(string5),dkString_getSource(string5));

		dkString_destroy(string1);
		dkString_destroy(string2);
		dkString_destroy(string3);
		dkString_destroy(string4);
		dkString_destroy(string5);
	dkError_end();

	return EXIT_SUCCESS;
};
