#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void operations(void)
{
	printf("OPERANTIONS\n");

	List *list1 = List_create(NULL);
	for (UnsignedSize i = 0; i <= 3; ++i) List_append(list1,(Undefined) i);
	List_debug(list1,"list1: append");
	for (UnsignedSize i = 4; i <= 7; ++i) List_insert(list1,2,(Undefined) i);
	List_debug(list1,"list1: insert(index=2)");
	for (UnsignedSize i = 8; i <= 11; ++i) List_prepend(list1,(Undefined) i);
	List_debug(list1,"list1: prepend");
	List_replace(list1,5,(Undefined) 255);
	List_debug(list1,"list1: replace(index=5)");
	List_set(list1,15,(Undefined) 127);
	List_debug(list1,"list1: set(index=15)");

	List *list2 = List_clone(list1);
	List_debug(list2,"list2: clone");
	printf("list2: getIndex(value=255): %llu\n",List_getIndex(list2,(Undefined) 255));
	printf("list2: getValue(index=5): %lli\n",List_getValue(list2,5).unsignedSize);
	printf("list2: getFront: %lli\n",List_getFront(list2).unsignedSize);
	printf("list2: getRear: %lli\n",List_getRear(list2).unsignedSize);
	List_remove(list2,5);
	List_debug(list2,"list2: remove(index=5)");
	List_dequeue(list2);
	List_debug(list2,"list2: dequeue");
	List_pop(list2);
	List_debug(list2,"list2: pop");
	List_swap(list2,0,-1);
	List_debug(list2,"list2: swap(index1=0 index2=-1)");
	List_setLength(list2,5);
	List_debug(list2,"list2: setLength(length=5)");

	List_merge(list1,5,list2);
	List_debug(list1,"list1: merge(index=5)");
	List_trim(list2);
	List_debug(list2,"list2: trim");
	List_clip(list1,5,-6);
	List_debug(list1,"list1: clip(start=5 end=-6)");

	printf("\n");

	list1 = List_destroy(list1);
	list2 = List_destroy(list2);
};

void benchmark(Boolean LOCK)
{
	printf("BENCHMARK(lock=%d)\n",LOCK);

	List *list = List_create(NULL);
	if (LOCK) List_setMutex(list,true);

	clock_t time = clock();
	for (UnsignedSize i = 0; i < 256 * 1024 * 1024; ++i) List_append(list,(Undefined) i);
	printf("append: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	time = clock();
	for (UnsignedSize i = 0; i < 256 * 1024 * 1024; ++i) List_dequeue(list);
	printf("dequeue: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	time = clock();
	for (UnsignedSize i = 0; i < 256 * 1024 * 1024; ++i) List_prepend(list,(Undefined) i);
	printf("prepend: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	printf("\n");

	list = List_destroy(list);
};

int main(void)
{
	operations();
	benchmark(false);
	benchmark(true);
	return EXIT_SUCCESS;
};
