// String
String *String_create();
String *String_createFromContainer(Container *CONTAINER);
String *String_clone(String *STRING);
String *String_destroy(String *STRING);

Boolean String_compare(String *STRING1,String *STRING2);
void String_merge(String *TARGET,SignedSize INDEX,String *SOURCE);
void String_clear(String *STRING);

void String_setLength(String *STRING,UnsignedSize LENGTH);
UnsignedSize String_getLength(String *STRING);
Boolean String_isEmpty(String *STRING);
Boolean String_isNotEmpty(String *STRING);
void String_setMutex(String *STRING,Boolean LOCK);
Boolean String_getMutex(String *STRING);
NullString String_getException(String *STRING);

void String_debug(String *STRING,NullString MESSAGE);
