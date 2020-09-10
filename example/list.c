#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Undefined map(List *LIST,UnsignedSize INDEX,Undefined VALUE)
{
	return (Undefined) (VALUE.unsignedSize + 10);
};

Boolean filter(List *LIST,UnsignedSize INDEX,Undefined VALUE)
{
	return VALUE.unsignedSize > 20;
};

Undefined reduce(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined ACCUMULATOR)
{
	return (Undefined) (ACCUMULATOR.unsignedSize + VALUE.unsignedSize);
};

Boolean search(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined TARGET)
{
	return VALUE.unsignedSize == TARGET.unsignedSize;
};

void test1()
{
	List *list = List_create();
	for (UnsignedSize i = 0; i < 32; ++i) List_append(list,(Undefined) (5 + i));
	List_debug(list,"original");
	List_map(list,0,5,&map);
	List_debug(list,"mapped");
	List_filter(list,0,5,&filter);
	List_debug(list,"filtered");
	List_reverse(list,2,-3);
	List_debug(list,"reverse");
	List_shuffle(list,0,5);
	List_debug(list,"shuffle");
	Exception_start();
		List_replace(list,56,(Undefined) 45);
		Exception_debug(List_getException(list));
	Exception_end();
	UnsignedSize reduced = List_reduce(list,0,5,&reduce).unsignedSize;
	printf("REDUCED: %lli\n",reduced);
	Boolean found = List_search(list,0,5,(Undefined) 34,&search);
	printf("FOUND: %lli\n",(UnsignedSize) found);
	list = List_destroy(list,true);
};

void test2()
{
	List *list = List_create();

	clock_t time = clock();
	for (UnsignedSize i = 0; i < 1024 * 1024; ++i) List_append(list,(Undefined) i);
	printf("append: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	time = clock();
	for (UnsignedSize i = 0; i < 1024 * 1024; ++i) List_dequeue(list);
	printf("dequeue: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	time = clock();
	for (UnsignedSize i = 0; i < 1024 * 1024; ++i) List_prepend(list,(Undefined) i);
	printf("prepend: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	list = List_destroy(list,true);
};

int main(void)
{
// 	List *list1 = List_create();
// 	List_debug(list1,"create");
// 	for (UnsignedSize i = 0; i < 4; ++i) List_prepend(list1,(Undefined) (i + 35));
// 	List_debug(list1,"prepend");
// 	for (UnsignedSize i = 0; i < 4; ++i) List_insert(list1,1,(Undefined) (i + 54));
// 	List_debug(list1,"insert");
// 	for (UnsignedSize i = 0; i < 4; ++i) List_append(list1,(Undefined) (i + 19));
// 	List_debug(list1,"append");
// 	List_replace(list1,1,(Undefined) 99);
// 	List_debug(list1,"replace");
// 	List_swap(list1,5,4);
// 	List_debug(list1,"swap");
// 	List_set(list1,4,(Undefined) 127);
// 	List_debug(list1,"set");
// 	List_set(list1,20,(Undefined) 99);
// 	List_debug(list1,"set");
// 	printf("INDEX: %lli\n",List_get(list1,2).unsignedSize);
// 	printf("FRONT: %lli\n",List_getFront(list1).unsignedSize);
// 	printf("REAR: %lli\n",List_getRear(list1).unsignedSize);
// 	List_trim(list1);

// 	List *list2 = List_createFromCopy(list1,1,-2);
// 	List_debug(list2,"createFromCopy");
// 	List_merge(list2,15,list1,4,-11);
// 	List_debug(list2,"merge");

// 	List *list3 = List_createFromCopy(list2,1,7);
// 	List_debug(list3,"List_createFromCopy");
// 	List_dequeue(list3);
// 	List_debug(list3,"dequeue");
// 	List_remove(list3,2);
// 	List_debug(list3,"remove");
// 	List_pop(list3);
// 	List_debug(list3,"pop");
// 	printf("SIZE: %lli\n",List_getSize(list3));
// 	List_clear(list3);
// 	List_debug(list3,"clear");
// 	printf("EMPTY: %lli\n",(UnsignedSize) List_isEmpty(list3));
// 	printf("NOT EMPTY: %lli\n",(UnsignedSize) List_isNotEmpty(list3));

// 	List_trim(list2);
// 	Pointer *pointer1 = pointer_encapsulate(List_getSource(list1),List_getSize(list1));
// 	List *list4 = List_createFromMemory(pointer1,0,-1);
// 	List_debug(list4,"createFromMemory");
// 	for (UnsignedSize i = 0; i < 4; ++i) List_dequeue(list4);
// 	List_debug(list4,"dequeue");
// 	List_setSize(list4,32);
// 	List_debug(list4,"setSize");
// 	List_trim(list4);
// 	List_debug(list4,"trim");

// 	Pointer *pointer2 = pointer_encapsulate(List_getSource(list2),List_getSize(list2));
// 	List *list5 = List_createFromPointer(pointer2);
// 	List_debug(list5,"createFromPointer");
// 	List_replace(list5,2,(Undefined) 199);
// 	List_debug(list2,"replace list2");
// 	List_debug(list5,"replace list5");

// 	list1 = List_destroy(list1,false);
// 	list2 = List_destroy(list2,false);
// 	list3 = List_destroy(list3,true);
// 	list4 = List_destroy(list4,true);
// 	list5 = List_destroy(list5,true);

	test1();
	test2();

	return EXIT_SUCCESS;
};
