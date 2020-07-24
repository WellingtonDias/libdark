#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	DKusize i;

	DKvector *vector1 = dkVector_create();

	for (i = 0; i < 4; ++i) dkVector_prepend(vector1,(DKscalar) (i + 35));
	dkVector_debug(vector1,"prepend");

	for (i = 0; i < 4; ++i) dkVector_insert(vector1,1,(DKscalar) (i + 54));
	dkVector_debug(vector1,"insert");

	for (i = 0; i < 4; ++i) dkVector_append(vector1,(DKscalar) (i + 19));
	dkVector_debug(vector1,"append");

	dkVector_replace(vector1,1,(DKscalar) 99);
	dkVector_debug(vector1,"replace");

	dkVector_swap(vector1,5,4);
	dkVector_debug(vector1,"swap");

	// dkVector_shuffle(vector1,7,4);
	// dkVector_debug(vector1,"shuffle");

	// dkVector_reverse(vector1,2,4);
	// dkVector_debug(vector1,"reverse");

	dkVector_set(vector1,4,(DKscalar) 127);
	dkVector_debug(vector1,"set");

	dkVector_set(vector1,20,(DKscalar) 255);
	dkVector_debug(vector1,"set");

	printf("FRONT: %lli\n",dkVector_getFront(vector1).usize);
	printf("INDEX: %lli\n",dkVector_getIndex(vector1,2).usize);
	printf("REAR: %lli\n",dkVector_getRear(vector1).usize);

	DKvector *vector2 = dkVector_createFromCopy(vector1,0,-1);
	DKvector *vector3 = dkVector_createFromCopy(vector2,1,8);
	dkVector_debug(vector3,"createFromCopy");

	dkVector_dequeue(vector3);
	dkVector_debug(vector3,"dequeue");

	dkVector_remove(vector3,2);
	dkVector_debug(vector3,"remove");

	dkVector_pop(vector3);
	dkVector_debug(vector3,"pop");

	// BOOLEAN found;
	// USIZE index = dkVector_search(vector3,(DKscalar) 56,&found);
	// if (found) printf("INDEX: %lli\n",index);

	printf("SIZE: %lli\n",dkVector_getSize(vector3));

	dkVector_clear(vector3);
	dkVector_debug(vector3,"clear");

	printf("EMPTY: %i\n",dkVector_isEmpty(vector3));

	vector1 = dkVector_destroy(vector1);
	vector2 = dkVector_destroy(vector2);
	vector3 = dkVector_destroy(vector3);

	return EXIT_SUCCESS;
};
