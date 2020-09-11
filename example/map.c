#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	Map *map1 = Map_create(256 * 256);
	Map_debug(map1,"create");
	Map_insert(map1,"Hello",(Undefined) "World!!!");
	Map_insert(map1,"Bella",(Undefined) "Wellington");
	Map_debug(map1,"insert");

	Map *map2 = Map_create(256 * 256);

	NullString *keys = malloc(1024 * sizeof(NullString));
	for (UnsignedSize i = 0; i < 1024; ++i)
	{
		keys[i] = malloc(24);
		sprintf(keys[i],"key%lli",i);
	};

	clock_t time = clock();
	for (UnsignedSize i = 0; i < 1024; ++i) Map_insert(map2,keys[i],(Undefined) i);
	printf("insert: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	for (UnsignedSize i = 0; i < 1024; ++i) free(keys[i]);
	free(keys);

	while (true) {};

	map1 = Map_destroy(map1);
	map2 = Map_destroy(map2);

	return EXIT_SUCCESS;
};
