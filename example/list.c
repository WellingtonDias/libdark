#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

DKundefined map(DKlist *LIST,DKusize INDEX,DKundefined VALUE)
{
	return (DKundefined) (VALUE.usize + 10);
};

DKboolean filter(DKlist *LIST,DKusize INDEX,DKundefined VALUE)
{
	return (VALUE.usize > 20);
};

DKundefined reduce(DKlist *LIST,DKusize INDEX,DKundefined VALUE,DKundefined ACCUMULATOR)
{
	return (DKundefined) (ACCUMULATOR.usize + VALUE.usize);
};

int main(void)
{
	DKlist *list1 = dkList_create();
	dkList_debug(list1,"create");
	for (DKusize i = 0; i < 4; ++i) dkList_prepend(list1,(DKundefined) (i + 35));
	dkList_debug(list1,"prepend");
	for (DKusize i = 0; i < 4; ++i) dkList_insert(list1,1,(DKundefined) (i + 54));
	dkList_debug(list1,"insert");
	for (DKusize i = 0; i < 4; ++i) dkList_append(list1,(DKundefined) (i + 19));
	dkList_debug(list1,"append");
	dkList_replace(list1,1,(DKundefined) 99);
	dkList_debug(list1,"replace");
	// dkList_swap(list1,5,4);
	// dkList_debug(list1,"swap");
	dkList_set(list1,4,(DKundefined) 127);
	dkList_debug(list1,"set");
	dkList_set(list1,20,(DKundefined) 99);
	dkList_debug(list1,"set");
	printf("INDEX: %lli\n",dkList_get(list1,2).usize);
	printf("FRONT: %lli\n",dkList_getFront(list1).usize);
	printf("HEAR: %lli\n",dkList_getHear(list1).usize);

	// DKlist *list2 = dkList_createFromCopy(list1,0,-1);

	// DKlist *list3 = dkList_createFromCopy(list2,1,8);
	// dkList_debug(list3,"createFromCopy");
	// dkList_dequeue(list3);
	// dkList_debug(list3,"dequeue");
	// dkList_remove(list3,2);
	// dkList_debug(list3,"remove");
	// dkList_pop(list3);
	// dkList_debug(list3,"pop");
	// printf("SIZE: %lli\n",dkList_getSize(list3));
	// dkList_clear(list3);
	// dkList_debug(list3,"clear");
	// printf("EMPTY: %lli\n",(DKusize) dkList_isEmpty(list3));
	// printf("NOT EMPTY: %lli\n",(DKusize) dkList_isNotEmpty(list3));

	// DKlist *list4 = dkList_createFromMemory(dkList_getSource(list2),dkList_getSize(list2),0,-1);
	// dkList_debug(list4,"createFromMemory");
	// for (DKusize i = 0; i < 4; ++i) dkList_dequeue(list4);
	// dkList_debug(list4,"dequeue");
	// dkList_setSize(list4,32);
	// dkList_debug(list4,"setSize");
	// dkList_trim(list4);
	// dkList_debug(list4,"trim");

	// DKlist *list5 = dkList_createFromPointer(dkList_getSource(list2),dkList_getSize(list2));
	// dkList_saveToFile(list5,0,-1,"./example/listSave");
	// dkList_debug(list5,"createFromPointer");

	// DKlist *list6 = dkList_createFromFile("./example/listLoad",0,-1);
	// dkList_debug(list6,"createFromFile");

	list1 = dkList_destroy(list1,true);
	// list2 = dkList_destroy(list2,false);
	// list3 = dkList_destroy(list3,true);
	// list4 = dkList_destroy(list4,true);
	// list5 = dkList_destroy(list5,true);
	// list6 = dkList_destroy(list6,true);



	// DKlist *list = dkList_create();

	// clock_t time = clock();
	// for (DKusize i = 0; i < 1024 * 1024; ++i) dkList_append(list,(DKundefined) i);
	// printf("append: %lf\n",(DKf64) (clock() - time) / CLOCKS_PER_SEC);

	// time = clock();
	// for (DKusize i = 0; i < 1024 * 1024; ++i) dkList_dequeue(list);
	// printf("dequeue: %lf\n",(DKf64) (clock() - time) / CLOCKS_PER_SEC);

	// time = clock();
	// for (DKusize i = 0; i < 1024 * 1024; ++i) dkList_prepend(list,(DKundefined) i);
	// printf("prepend: %lf\n",(DKf64) (clock() - time) / CLOCKS_PER_SEC);

	// list = dkList_destroy(list,true);

	DKlist *list = dkList_create();
	for (DKusize i = 0; i < 10; ++i) dkList_append(list,(DKundefined) (5 + i));
	dkList_debug(list,"original");
	dkList_map(list,&map);
	dkList_debug(list,"mapped");
	dkList_filter(list,&filter);
	dkList_debug(list,"filtered");
	DKusize reduced = dkList_reduce(list,&reduce).usize;
	printf("REDUCED: %lli\n",reduced);
	list = dkList_destroy(list,true);

	return EXIT_SUCCESS;
};
