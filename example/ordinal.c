#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	DKordinal *ordinal1 = dkOrdinal_create();
	dkOrdinal_debug(ordinal1,"create");
	for (DKusize i = 0; i < 4; ++i) dkOrdinal_prepend(ordinal1,(DKvalue) (i + 35));
	dkOrdinal_debug(ordinal1,"prepend");
	for (DKusize i = 0; i < 4; ++i) dkOrdinal_insert(ordinal1,1,(DKvalue) (i + 54));
	dkOrdinal_debug(ordinal1,"insert");
	for (DKusize i = 0; i < 4; ++i) dkOrdinal_append(ordinal1,(DKvalue) (i + 19));
	dkOrdinal_debug(ordinal1,"append");
	dkOrdinal_replace(ordinal1,1,(DKvalue) 99);
	dkOrdinal_debug(ordinal1,"replace");
	dkOrdinal_swap(ordinal1,5,4);
	dkOrdinal_debug(ordinal1,"swap");
	dkOrdinal_set(ordinal1,4,(DKvalue) 127);
	dkOrdinal_debug(ordinal1,"set");
	dkOrdinal_set(ordinal1,20,(DKvalue) 255);
	dkOrdinal_debug(ordinal1,"set");
	printf("FRONT: %lli\n",dkOrdinal_getFront(ordinal1).usize);
	printf("INDEX: %lli\n",dkOrdinal_getIndex(ordinal1,2).usize);
	printf("REAR: %lli\n",dkOrdinal_getRear(ordinal1).usize);

	DKordinal *ordinal2 = dkOrdinal_createFromCopy(ordinal1,0,-1);

	DKordinal *ordinal3 = dkOrdinal_createFromCopy(ordinal2,1,8);
	dkOrdinal_debug(ordinal3,"createFromCopy");
	dkOrdinal_dequeue(ordinal3);
	dkOrdinal_debug(ordinal3,"dequeue");
	dkOrdinal_remove(ordinal3,2);
	dkOrdinal_debug(ordinal3,"remove");
	dkOrdinal_pop(ordinal3);
	dkOrdinal_debug(ordinal3,"pop");
	printf("LENGTH: %lli\n",dkOrdinal_getLength(ordinal3));
	dkOrdinal_clear(ordinal3);
	dkOrdinal_debug(ordinal3,"clear");
	printf("EMPTY: %s\n",boolean_toString[dkOrdinal_isEmpty(ordinal3)]);
	printf("NOT EMPTY: %s\n",boolean_toString[dkOrdinal_isNotEmpty(ordinal3)]);

	ordinal1 = dkOrdinal_destroy(ordinal1);
	ordinal2 = dkOrdinal_destroy(ordinal2);
	ordinal3 = dkOrdinal_destroy(ordinal3);

	return EXIT_SUCCESS;
};
