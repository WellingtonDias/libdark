#include <DARK.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

DKblob *Blob;
DKu8 *Source;

void independent(void)
{
	DKblob *blob1 = dkBlob_create(DARK_BLOB_SYSTEM_ENDIAN);
	dkBlob_debug(blob1,"create");

	DKu8 source[5] = {0,1,2,3,4};
	DKblob *blob2 = dkBlob_createFromMemory(&source,5,1,-2,DARK_BLOB_SYSTEM_ENDIAN);
	dkBlob_debug(blob2,"createFromMemory");

	DKblob *blob3 = dkBlob_createFromCopy(blob2,1,-2);
	dkBlob_debug(blob3,"createFromCopy");

	DKblob *blob4 = dkBlob_createFromFile("./example/blobLoad",0,-1,DARK_BLOB_SYSTEM_ENDIAN);
	dkBlob_debug(blob4,"createFromFile");
	dkBlob_saveToFile(blob4,0,-1,"./example/blobSave");
	dkBlob_saveToFile(blob4,2,-3,"./example/blobPartialSave");

	DKblob *blob5 = dkBlob_createFromCopy(blob4,0,-1);
	dkBlob_merge(blob5,5,blob2,1,2);
	dkBlob_debug(blob5,"merge");
	dkBlob_clear(blob5);
	dkBlob_debug(blob5,"clear");

	blob1 = dkBlob_destroy(blob1);
	blob2 = dkBlob_destroy(blob2);
	blob3 = dkBlob_destroy(blob3);
	blob4 = dkBlob_destroy(blob4);
	blob5 = dkBlob_destroy(blob5);
};

void single()
{
	DKblob *blob = dkBlob_create(DARK_BLOB_SYSTEM_ENDIAN);
	dkBlob_setLock(blob,true);
	dkBlob_writeAt(blob,2684354560,Source,256);
	clock_t time = clock();
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	dkBlob_resetOffset(blob);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	dkBlob_resetOffset(blob);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	dkBlob_resetOffset(blob);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	dkBlob_resetOffset(blob);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	dkBlob_resetOffset(blob);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	dkBlob_resetOffset(blob);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	dkBlob_resetOffset(blob);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	dkBlob_resetOffset(blob);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	dkBlob_resetOffset(blob);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	dkBlob_resetOffset(blob);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	dkBlob_resetOffset(blob);
	for (DKusize i = 0; i < 10 * 1024 * 1024; ++i) dkBlob_write(blob,Source,256);
	printf("SINGLE-THREAD TIME: %lf\n",(DKf64) (clock() - time) / CLOCKS_PER_SEC);
	blob = dkBlob_destroy(blob);
};

int multi(void *arguments)
{
	clock_t time = clock();
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	for (DKusize i = 0; i < 1024 * 1024; ++i) dkBlob_write(Blob,Source,256);
	dkBlob_resetOffset(Blob);
	printf("MULTI-THREAD  TIME: %lf\n",(DKf64) (clock() - time) / CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
};

int main(void)
{
	thrd_t list[10];
	independent();
	Source = malloc(256);
	Blob = dkBlob_create(DARK_BLOB_SYSTEM_ENDIAN);
	dkBlob_debug(Blob,"create");
	dkBlob_setLock(Blob,true);
	dkBlob_writeAt(Blob,2684354560,Source,256);
	single();
	for (DKusize i = 0; i < 10; ++i)
	{
		if (thrd_create(list + i,multi,NULL) == thrd_success) thrd_detach(list[i]);
	};
	single();
	while (true) ;
	free(Source);
	Blob = dkBlob_destroy(Blob);
	return EXIT_SUCCESS;
};
