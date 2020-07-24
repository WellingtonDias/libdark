#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

DKbuffer *Buffer;
DKu8 *Source;

void independent(void)
{
	DKbuffer *buffer1 = dkBuffer_create(DARK_BUFFER_SYSTEM_ENDIAN);
	dkBuffer_debug(buffer1,"create");

	DKu8 source[5] = {0,1,2,3,4};
	DKbuffer *buffer2 = dkBuffer_createFromRaw((DKpointer) &source,5,1,-2,DARK_BUFFER_SYSTEM_ENDIAN);
	dkBuffer_debug(buffer2,"createFromRaw");

	DKbuffer *buffer3 = dkBuffer_createFromCopy(buffer2,0,-1);
	dkBuffer_debug(buffer3,"createFromCopy");

	DKbuffer *buffer4 = dkBuffer_createFromFile("./example/buffer_load",0,-1,DARK_BUFFER_SYSTEM_ENDIAN);
	dkBuffer_debug(buffer4,"createFromFile");

	dkBuffer_save(buffer4,0,-1,"./example/buffer_save");
	dkBuffer_save(buffer4,5,9,"./example/buffer_partialSave");

	DKbuffer *buffer5 = dkBuffer_createFromCopy(buffer4,0,-1);
	dkBuffer_merge(buffer5,5,buffer2,1,2);
	dkBuffer_debug(buffer5,"merge");

	dkBuffer_clear(buffer5);
	dkBuffer_debug(buffer5,"clear");

	buffer1 = dkBuffer_destroy(buffer1);
	buffer2 = dkBuffer_destroy(buffer2);
	buffer3 = dkBuffer_destroy(buffer3);
	buffer4 = dkBuffer_destroy(buffer4);
	buffer5 = dkBuffer_destroy(buffer5);
};

int dependent(void *arg)
{
	clock_t time = clock();
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBuffer_writeRaw(Buffer,Source,256);
	dkBuffer_resetOffset(Buffer);
	printf("MULTI-THREAD  TIME: %lf\n",(DKf64) (clock() - time) / CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
};

void dependent2()
{
	DKbuffer *buffer = dkBuffer_create(DARK_BUFFER_SYSTEM_ENDIAN);
	dkBuffer_setLock(buffer,true);
	dkBuffer_writeRawAt(buffer,2684354560,Source,256);
	clock_t time = clock();
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	dkBuffer_resetOffset(buffer);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	dkBuffer_resetOffset(buffer);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	dkBuffer_resetOffset(buffer);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	dkBuffer_resetOffset(buffer);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	dkBuffer_resetOffset(buffer);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	dkBuffer_resetOffset(buffer);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	dkBuffer_resetOffset(buffer);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	dkBuffer_resetOffset(buffer);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	dkBuffer_resetOffset(buffer);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	dkBuffer_resetOffset(buffer);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	dkBuffer_resetOffset(buffer);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBuffer_writeRaw(buffer,Source,256);
	printf("SINGLE-THREAD TIME: %lf\n",(DKf64) (clock() - time) / CLOCKS_PER_SEC);
	buffer = dkBuffer_destroy(buffer);
};

int main(void)
{
	thrd_t list[10];
	independent();
	Source = malloc(256);
	Buffer = dkBuffer_create(DARK_BUFFER_SYSTEM_ENDIAN);
	dkBuffer_debug(Buffer,"create");
	dkBuffer_setLock(Buffer,true);
	dkBuffer_writeRawAt(Buffer,2684354560,Source,256);
	for (DKusize i = 0; i < 10; ++i)
	{
		if (thrd_create(list + i,dependent,NULL) == thrd_success) thrd_detach(list[i]);
	};
	dependent2();
	while (true) {};
	Buffer = dkBuffer_destroy(Buffer);
	return EXIT_SUCCESS;
};
