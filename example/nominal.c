#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	USIZE i;

	DARKnominal *nominal1 = DKnominal_create(256);

	for (i = 0; i < 4; ++i)
	{
		DKnominal_insert(nominal1,(HANDLE) (i + 35),(HANDLE) (i + 99));
		DKnominal_debug(nominal1,"insert");
	};

	DKnominal_replace(nominal1,(HANDLE) (37),(HANDLE) 255);
	DKnominal_debug(nominal1,"replace");

	DKnominal_swap(nominal1,(HANDLE) (37),(HANDLE) 38);
	DKnominal_debug(nominal1,"swap");

	DKnominal_set(nominal1,(HANDLE) (36),(HANDLE) 127);
	DKnominal_debug(nominal1,"set");

	DKnominal_set(nominal1,(HANDLE) (57),(HANDLE) 63);
	DKnominal_debug(nominal1,"set");

	DARKnominal *nominal2 = DKnominal_copy(nominal1);
	DKnominal_debug(nominal2,"copy");

	printf("GET: %lli\n",DKnominal_get(nominal2,(HANDLE) 37).usize);

	DKnominal_remove(nominal2,(HANDLE) (36));
	DKnominal_debug(nominal2,"remove");

	printf("EXISTS: %i\n",DKnominal_exists(nominal2,(HANDLE) (37)));

	BOOLEAN found;
	HANDLE key = DKnominal_search(nominal2,(HANDLE) 255,&found);
	if (found) printf("KEY: %lli\n",key.usize);
	else printf("not found\n");

	printf("SIZE: %lli\n",DKnominal_getSize(nominal2));

	DKnominal_set(nominal1,(HANDLE) (42),(HANDLE) 42);
	DKnominal_set(nominal1,(HANDLE) (37),(HANDLE) 42);
	DKnominal_concatenate(nominal2,nominal1);
	DKnominal_debug(nominal2,"concatenate");

	DKnominal_clear(nominal2);
	DKnominal_debug(nominal2,"clear");

	printf("EMPTY: %i\n",DKnominal_isEmpty(nominal2));
	printf("NOT EMPTY: %i\n",DKnominal_isNotEmpty(nominal2));

	nominal1 = DKnominal_destroy(nominal1);
	nominal2 = DKnominal_destroy(nominal2);

	return EXIT_SUCCESS;
};
