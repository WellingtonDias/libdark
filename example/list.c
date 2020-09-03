#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Undefined map(List *LIST,UnsignedSize INDEX,Undefined VALUE)
{
	return (Undefined) (VALUE.usize + 10);
};

Boolean filter(List *LIST,UnsignedSize INDEX,Undefined VALUE)
{
	return VALUE.usize > 20;
};

Undefined reduce(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined ACCUMULATOR)
{
	return (Undefined) (ACCUMULATOR.usize + VALUE.usize);
};

Boolean search(List *LIST,UnsignedSize INDEX,Undefined VALUE,Undefined TARGET)
{
	return VALUE.usize == TARGET.usize;
};

void test1()
{
	List *list = list_create();
	for (UnsignedSize i = 0; i < 32; ++i) list_append(list,(Undefined) (5 + i));
	list_debug(list,"original");
	list_map(list,0,5,&map);
	list_debug(list,"mapped");
	list_filter(list,0,5,&filter);
	list_debug(list,"filtered");
	list_reverse(list,2,-3);
	list_debug(list,"reverse");
	list_shuffle(list,0,5);
	list_debug(list,"shuffle");
	UnsignedSize reduced = list_reduce(list,0,5,&reduce).usize;
	printf("REDUCED: %lli\n",reduced);
	Boolean found = list_search(list,0,5,(Undefined) 34,&search);
	printf("FOUND: %lli\n",(UnsignedSize) found);
	list = list_destroy(list,true);
};

void test2()
{
	List *list = list_create();

	clock_t time = clock();
	for (UnsignedSize i = 0; i < 1024 * 1024; ++i) list_append(list,(Undefined) i);
	printf("append: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	time = clock();
	for (UnsignedSize i = 0; i < 1024 * 1024; ++i) list_dequeue(list);
	printf("dequeue: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	time = clock();
	for (UnsignedSize i = 0; i < 1024 * 1024; ++i) list_prepend(list,(Undefined) i);
	printf("prepend: %lf\n",(Float64) (clock() - time) / CLOCKS_PER_SEC);

	list = list_destroy(list,true);
};

int main(void)
{
	List *list1 = list_create();
	list_debug(list1,"create");
	for (UnsignedSize i = 0; i < 4; ++i) list_prepend(list1,(Undefined) (i + 35));
	list_debug(list1,"prepend");
	for (UnsignedSize i = 0; i < 4; ++i) list_insert(list1,1,(Undefined) (i + 54));
	list_debug(list1,"insert");
	for (UnsignedSize i = 0; i < 4; ++i) list_append(list1,(Undefined) (i + 19));
	list_debug(list1,"append");
	list_replace(list1,1,(Undefined) 99);
	list_debug(list1,"replace");
	list_swap(list1,5,4);
	list_debug(list1,"swap");
	list_set(list1,4,(Undefined) 127);
	list_debug(list1,"set");
	list_set(list1,20,(Undefined) 99);
	list_debug(list1,"set");
	printf("INDEX: %lli\n",list_get(list1,2).usize);
	printf("FRONT: %lli\n",list_getFront(list1).usize);
	printf("REAR: %lli\n",list_getRear(list1).usize);
	list_trim(list1);

	List *list2 = list_createFromCopy(list1,1,-2);
	list_debug(list2,"createFromCopy");
	list_merge(list2,15,list1,4,-11);
	list_debug(list2,"merge");

	List *list3 = list_createFromCopy(list2,1,7);
	list_debug(list3,"list_createFromCopy");
	list_dequeue(list3);
	list_debug(list3,"dequeue");
	list_remove(list3,2);
	list_debug(list3,"remove");
	list_pop(list3);
	list_debug(list3,"pop");
	printf("SIZE: %lli\n",list_getSize(list3));
	list_clear(list3);
	list_debug(list3,"clear");
	printf("EMPTY: %lli\n",(UnsignedSize) list_isEmpty(list3));
	printf("NOT EMPTY: %lli\n",(UnsignedSize) list_isNotEmpty(list3));

	list_trim(list2);
	Pointer *pointer1 = pointer_encapsulate(list_getSource(list1),list_getSize(list1));
	List *list4 = list_createFromMemory(pointer1,0,-1);
	list_debug(list4,"createFromMemory");
	for (UnsignedSize i = 0; i < 4; ++i) list_dequeue(list4);
	list_debug(list4,"dequeue");
	list_setSize(list4,32);
	list_debug(list4,"setSize");
	list_trim(list4);
	list_debug(list4,"trim");

	Pointer *pointer2 = pointer_encapsulate(list_getSource(list2),list_getSize(list2));
	List *list5 = list_createFromPointer(pointer2);
	list_debug(list5,"createFromPointer");
	list_replace(list5,2,(Undefined) 199);
	list_debug(list2,"replace list2");
	list_debug(list5,"replace list5");

	list1 = list_destroy(list1,false);
	list2 = list_destroy(list2,false);
	list3 = list_destroy(list3,true);
	list4 = list_destroy(list4,true);
	list5 = list_destroy(list5,true);

	test1();
	test2();

	return EXIT_SUCCESS;
};
