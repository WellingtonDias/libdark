#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	DKnominal *nominal1 = dkNominal_create(256);
	dkNominal_debug(nominal1,"create");
	DKnullString *keys = malloc(1024 * 1024 * sizeof(DKnullString));
	for (DKusize i = 0; i < 1024 * 1024; ++i)
	{
		keys[i] = malloc(24);
		sprintf(keys[i],"key%lli",i);
	};
	for (DKusize i = 0; i < 1024 * 1024; ++i)
	{
		dkNominal_insert(nominal1,keys[i],(DKvalue) i);
		free(keys[i]);
	};
	free(keys);
	printf("END");
	while (true) ;

	nominal1 = dkNominal_destroy(nominal1);

	return EXIT_SUCCESS;
};


// DKnullString keys[4] = {"key1","key2","key3","key4"};

// dkNominal_replace(nominal1,(HANDLE) (37),(HANDLE) 255);
// dkNominal_debug(nominal1,"replace");

// dkNominal_swap(nominal1,(HANDLE) (37),(HANDLE) 38);
// dkNominal_debug(nominal1,"swap");

// dkNominal_set(nominal1,(HANDLE) (36),(HANDLE) 127);
// dkNominal_debug(nominal1,"set");

// dkNominal_set(nominal1,(HANDLE) (57),(HANDLE) 63);
// dkNominal_debug(nominal1,"set");

// DARKnominal *nominal2 = dkNominal_copy(nominal1);
// dkNominal_debug(nominal2,"copy");

// printf("GET: %lli\n",dkNominal_get(nominal2,(HANDLE) 37).usize);

// dkNominal_remove(nominal2,(HANDLE) (36));
// dkNominal_debug(nominal2,"remove");

// printf("EXISTS: %i\n",dkNominal_exists(nominal2,(HANDLE) (37)));

// BOOLEAN found;
// HANDLE key = dkNominal_search(nominal2,(HANDLE) 255,&found);
// if (found) printf("KEY: %lli\n",key.usize);
// else printf("not found\n");

// printf("LENGTH: %lli\n",dkNominal_getLength(nominal2));

// dkNominal_set(nominal1,(HANDLE) (42),(HANDLE) 42);
// dkNominal_set(nominal1,(HANDLE) (37),(HANDLE) 42);
// dkNominal_concatenate(nominal2,nominal1);
// dkNominal_debug(nominal2,"concatenate");

// dkNominal_clear(nominal2);
// dkNominal_debug(nominal2,"clear");

// printf("EMPTY: %i\n",dkNominal_isEmpty(nominal2));
// printf("NOT EMPTY: %i\n",dkNominal_isNotEmpty(nominal2));

// nominal2 = dkNominal_destroy(nominal2);
