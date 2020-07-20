// String
#define DARK_STRING_LOWER_CASE     0
#define DARK_STRING_UPPER_CASE     1
#define DARK_STRING_PROPER_CASE    2
#define DARK_STRING_ALTERNATE_CASE 3
#define DARK_STRING_INVERT_CASE    4

#define DARK_STRING_TRIM_START 0
#define DARK_STRING_TRIM_END   1
#define DARK_STRING_TRIM_ALL   2

DKstring *dkString_create(void);
DKstring *dkString_createFromMemory(DKnstring SOURCE,DKusize SIZE,DKssize START,DKssize END);
DKstring *dkString_createFromFile(DKnstring FILE_NAME,DKssize START,DKssize END);
DKstring *dkString_createFromCopy(DKstring *STRING,DKssize START,DKssize END);
DKstring *dkString_destroy(DKstring *STRING);
	void dkString_save(DKstring *STRING,DKssize START,DKssize END,DKnstring FILE_NAME);
	void dkString_merge(DKstring *STRING,DKssize INDEX,DKstring *SOURCE,DKssize START,DKssize END);
	void dkString_clear(DKstring *STRING);
	DKboolean dkString_compare(DKstring *STRING1,DKstring *STRING2);
		void dkString_convert(DKstring *STRING,DKu8 TYPE);
		void dkString_trim(DKstring *STRING,DKu8 TYPE);
			DKcharacter dkString_getCharacter(DKstring *STRING,DKssize INDEX);
			DKnstring dkString_getSource(DKstring *STRING);
			DKusize dkString_getLength(DKstring *STRING);
			DKboolean dkString_isEmpty(DKstring *STRING);
			void dkString_setLock(DKstring *STRING,DKboolean LOCK);
			DKboolean dkString_getLock(DKstring *STRING);
				void dkString_debug(DKstring *STRING,DKnstring LABEL);
