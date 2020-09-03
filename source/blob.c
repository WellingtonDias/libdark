// #routine blob_insert(#TYPE,BLOB,INDEX,VALUE,SIZE)
// {
// 	box_adjustCapacity(TYPE,BLOB,BLOB.size + SIZE);
// 	if (INDEX < BLOB.size) memmove(BLOB.start + INDEX + SIZE,BLOB.start + INDEX,(BLOB.size - INDEX) * sizeof(TYPE));
// 	memcpy(BLOB.start + INDEX,VALUE,SIZE * sizeof(TYPE));
// 	BLOB.size += SIZE;
// };

// #routine blob_replace(#TYPE,BLOB,INDEX,VALUE,SIZE)
// {
// 	memcpy(BLOB.start + INDEX,VALUE,SIZE * sizeof(TYPE));
// };

// #routine blob_set(#TYPE,BLOB,INDEX,VALUE,SIZE)
// {
// 	if (INDEX > BLOB.size - SIZE)
// 	{
// 		box_adjustCapacity(TYPE,BLOB,INDEX + SIZE);
// 		if (INDEX > BLOB.size) memset(BLOB.start + BLOB.size,0,(INDEX - BLOB.size) * sizeof(TYPE));
// 		BLOB.size = INDEX + SIZE;
// 	};
// 	memcpy(BLOB.start + INDEX,VALUE,SIZE * sizeof(TYPE));
// };

// #routine blob_erase(#TYPE,BLOB,INDEX,SIZE)
// {
// 	memset(BLOB.start + INDEX,0,SIZE * sizeof(TYPE));
// };

// #routine blob_remove(#TYPE,BLOB,INDEX,SIZE)
// {
// 	BLOB.size -= SIZE;
// 	if (INDEX < BLOB.size) memcpy(BLOB.start + INDEX,BLOB.start + INDEX + SIZE,(BLOB.size - INDEX) * sizeof(TYPE));
// 	box_adjustCapacity(TYPE,BLOB,BLOB.size);
// };
