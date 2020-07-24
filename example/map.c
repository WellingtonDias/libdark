#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	USIZE i;

	DARKmap *map1 = DARKmap_create(256);

	for (i = 0; i < 4; ++i)
	{
		DARKmap_insert(map1,(SCALAR) (i + 35),(SCALAR) (i + 99));
		DARKmap_debug(map1,"insert");
	};

	DARKmap_replace(map1,(SCALAR) (37),(SCALAR) 255);
	DARKmap_debug(map1,"replace");

	DARKmap_swap(map1,(SCALAR) (37),(SCALAR) 38);
	DARKmap_debug(map1,"swap");

	DARKmap_set(map1,(SCALAR) (36),(SCALAR) 127);
	DARKmap_debug(map1,"set");

	DARKmap_set(map1,(SCALAR) (57),(SCALAR) 63);
	DARKmap_debug(map1,"set");

	DARKmap *map2 = DARKmap_copy(map1);
	DARKmap_debug(map2,"copy");

	printf("GET: %lli\n",DARKmap_get(map2,(SCALAR) 37).usize);

	DARKmap_remove(map2,(SCALAR) (36));
	DARKmap_debug(map2,"remove");

	printf("EXISTS: %i\n",DARKmap_exists(map2,(SCALAR) (37)));

	BOOLEAN found;
	SCALAR key = DARKmap_search(map2,(SCALAR) 255,&found);
	if (found) printf("KEY: %lli\n",key.usize);
	else printf("not found\n");

	printf("SIZE: %lli\n",DARKmap_getSize(map2));

	DARKmap_set(map1,(SCALAR) (42),(SCALAR) 42);
	DARKmap_set(map1,(SCALAR) (37),(SCALAR) 42);
	DARKmap_concatenate(map2,map1);
	DARKmap_debug(map2,"concatenate");

	DARKmap_clear(map2);
	DARKmap_debug(map2,"clear");

	printf("EMPTY: %i\n",DARKmap_isEmpty(map2));

	map1 = DARKmap_destroy(map1);
	map2 = DARKmap_destroy(map2);

	return EXIT_SUCCESS;
};
