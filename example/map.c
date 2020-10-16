#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void benchmark(Map *MAP,UnsignedSize HASH_SIZE)
{
	Map_setHashSize(MAP,HASH_SIZE);
	Map_debug(MAP,"");

	clock_t time = clock();
	for (UnsignedSize i = 0; i < 1024 * 1024; ++i) Map_insert(MAP,(Undefined) i,(Undefined) ((1024 * 1024) - i));
	printf("insert: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	time = clock();
	for (UnsignedSize i = 0; i < 1024 * 1024; ++i) Map_remove(MAP,(Undefined) i);
	printf("remove: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	printf("benchmark\n\n");
};

void structOperations(void)
{
	Map *map1 = Map_create(256 * 256,NULL,NULL);
	Map_insert(map1,(Undefined) 0,(Undefined) 0);
	Map_insert(map1,(Undefined) 1,(Undefined) 1);
	Map_insert(map1,(Undefined) 2,(Undefined) 2);
	Map_debug(map1,"insert");

	Map *map2 = Map_clone(map1);
	Map_debug(map2,"clone");

	Map *map3 = Map_create(256,NULL,NULL);
	Map_insert(map3,(Undefined) 0,(Undefined) 0);
	Map_insert(map3,(Undefined) 1,(Undefined) 1);
	Map_insert(map3,(Undefined) 2,(Undefined) 2);
	Map_debug(map3,"insert");

	printf("compare: %d\n",Map_compare(map2,map3));

	Map_insert(map2,(Undefined) 1024,(Undefined) 1024);
	Map_debug(map2,"insert");

	Map_insert(map3,(Undefined) 4,(Undefined) 3);
	Map_insert(map3,(Undefined) 1024,(Undefined) 4);
	Map_debug(map3,"insert");

	printf("compare: %d\n",Map_compare(map2,map3));

	Map_merge(map2,map3);
	Map_debug(map2,"merge");

	Map_clear(map2);
	Map_debug(map2,"merge");
	Map_clear(map3);
	Map_debug(map3,"merge");

	map1 = Map_destroy(map1);
	map2 = Map_destroy(map2);
	map3 = Map_destroy(map3);

	printf("structOperations\n\n");
};

void properties(void)
{
	Map *map = Map_create(256,NULL,NULL);

	Map_insert(map,(Undefined) 0,(Undefined) 0);
	Map_insert(map,(Undefined) 1,(Undefined) 1);
	Map_insert(map,(Undefined) 2,(Undefined) 2);

	printf("length: %lli\n",Map_getLength(map));
	printf("empty: %d\n",Map_isEmpty(map));
	printf("not empty: %d\n",Map_isNotEmpty(map));
	printf("hashsize: %lli\n",Map_getHashSize(map));

	Map_setHashSize(map,1);
	Map_debug(map,"setHashSize: 1");
	Map_setHashSize(map,2);
	Map_debug(map,"setHashSize: 2");
	Map_setHashSize(map,16);
	Map_debug(map,"setHashSize: 16");
	Map_setHashSize(map,256 * 256);
	Map_debug(map,"setHashSize: 256 * 256");

	map = Map_destroy(map);

	printf("properties\n\n");
};

int main(void)
{
	Map *map = Map_create(256 * 256,NULL,NULL);
	for (UnsignedSize i = 256; i <= 256 * 256; i *= 2) benchmark(map,i);
	structOperations();
	properties();
	map = Map_destroy(map);
	return EXIT_SUCCESS;
};
