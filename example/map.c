#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Boolean diffFunction(Undefined TARGET,Undefined SOURCE)
{
	return TARGET.unsignedSize == SOURCE.unsignedSize;
};

UnsignedSize hashFunction(Undefined KEY,UnsignedSize HASH_SIZE)
{
	return KEY.unsignedSize % HASH_SIZE;
};

int main(void)
{
	Map *map1 = Map_create(256 * 256,&hashFunction,&diffFunction);
	Map_debug(map1,"create");
	Map_insert(map1,(Undefined) "Hello",(Undefined) 0);
	Map_insert(map1,(Undefined) "Bella",(Undefined) 1);
	Map_debug(map1,"insert");
	Map_replace(map1,(Undefined) "Hello",(Undefined) 1);
	Map_debug(map1,"replace");
	printf("GET: %lli\n",Map_get(map1,(Undefined) "Bella").unsignedSize);
	Map_remove(map1,(Undefined) "Hello");
	Map_debug(map1,"remove");
	Map_set(map1,(Undefined) "Wellington",(Undefined) 2);
	Map_set(map1,(Undefined) "Bella",(Undefined) 2);
	Map_debug(map1,"set");

	Map *map2 = Map_create(256 * 256,NULL,NULL);

	NullString *keys = malloc(1024 * sizeof(NullString));
	for (UnsignedSize i = 0; i < 1024; ++i)
	{
		keys[i] = malloc(24);
		sprintf(keys[i],"key%lli",i);
	};

	clock_t time = clock();
	for (UnsignedSize i = 0; i < 1024; ++i) Map_insert(map2,(Undefined) keys[i],(Undefined) i);
	printf("STRING: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	time = clock();
	for (UnsignedSize i = 0; i < 1024; ++i) Map_insert(map2,(Undefined) i,(Undefined) i);
	printf("NUMBER: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	for (UnsignedSize i = 0; i < 1024; ++i) free(keys[i]);
	free(keys);

	map1 = Map_destroy(map1);
	map2 = Map_destroy(map2);

	return EXIT_SUCCESS;
};
