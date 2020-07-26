// String
DKstring *dkString_create(void);
DKstring *dkString_createFromMemory(DKnullString SOURCE,DKusize SIZE,DKssize START,DKssize END);
DKstring *dkString_createFromFile(DKnullString FILE_NAME,DKssize START,DKssize END);
DKstring *dkString_createFromCopy(DKstring *STRING,DKssize START,DKssize END);
DKstring *dkString_destroy(DKstring *STRING);
	void dkString_saveToFile(DKstring *STRING,DKssize START,DKssize END,DKnullString FILE_NAME);
	void dkString_merge(DKstring *STRING,DKssize INDEX,DKstring *SOURCE,DKssize START,DKssize END);
	void dkString_clear(DKstring *STRING);
	DKboolean dkString_compare(DKstring *STRING1,DKstring *STRING2);
		DKcharacter dkString_getCode(DKstring *STRING,DKssize INDEX);
		DKnullString dkString_getCharacter(DKstring *STRING,DKssize INDEX);
		DKnullString dkString_getNullString(DKstring *STRING,DKssize START,DKssize END);
		void dkString_toLowerCase(DKstring *STRING);
		void dkString_toUpperCase(DKstring *STRING);
		void dkString_toProperCase(DKstring *STRING);
		void dkString_toInvertedCase(DKstring *STRING);
		void dkString_toAlternatedCase(DKstring *STRING);
		void dkString_toRandomCase(DKstring *STRING);
		void dkString_toLowerSnakeCase(DKstring *STRING);
		void dkString_toUpperSnakeCase(DKstring *STRING);
		void dkString_toLowerKebabCase(DKstring *STRING);
		void dkString_toUpperKebabCase(DKstring *STRING);
		void dkString_toCamelCase(DKstring *STRING);
		void dkString_toPascalCase(DKstring *STRING);
		void dkString_trimStart(DKstring *STRING);
		void dkString_trimInner(DKstring *STRING);
		void dkString_trimEnd(DKstring *STRING);
		void dkString_trimOuter(DKstring *STRING);
			DKrawString dkString_getSource(DKstring *STRING);
			DKusize dkString_getLength(DKstring *STRING);
			DKboolean dkString_isEmpty(DKstring *STRING);
			DKboolean dkString_isNotEmpty(DKstring *STRING);
			DKboolean dkString_setLock(DKstring *STRING,DKboolean LOCK);
			DKboolean dkString_getLock(DKstring *STRING);
				void dkString_debug(DKstring *STRING,DKnullString LABEL);
