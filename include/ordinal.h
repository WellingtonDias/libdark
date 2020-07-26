// // Ordinal
// DKordinal *dkOrdinal_create(void);
// DKordinal *dkOrdinal_createFromCopy(DKordinal *ORDINAL,DKssize START,DKssize END);
// DKordinal *dkOrdinal_destroy(DKordinal *ORDINAL);
// 	void dkOrdinal_merge(DKordinal *ORDINAL,DKssize INDEX,DKordinal *SOURCE,DKssize START,DKssize END);
// 	void dkOrdinal_clear(DKordinal *ORDINAL);
// 	DKboolean dkOrdinal_compare(DKordinal *ORDINAL1,DKordinal *ORDINAL2);
// 		void dkOrdinal_prepend(DKordinal *ORDINAL,DKhandleUnion SOURCE);
// 		void dkOrdinal_insert(DKordinal *ORDINAL,DKssize INDEX,DKhandleUnion SOURCE);
// 		void dkOrdinal_append(DKordinal *ORDINAL,DKhandleUnion SOURCE);
// 		DKhandleUnion dkOrdinal_replace(DKordinal *ORDINAL,DKssize INDEX,DKhandleUnion SOURCE);
// 		DKhandleUnion dkOrdinal_set(DKordinal *ORDINAL,DKssize INDEX,DKhandleUnion SOURCE);
// 		void dkOrdinal_swap(DKordinal *ORDINAL,DKssize INDEX1,DKssize INDEX2);
// 		DKhandleUnion dkOrdinal_getFront(DKordinal *ORDINAL);
// 		DKhandleUnion dkOrdinal_getIndex(DKordinal *ORDINAL,DKssize INDEX);
// 		DKhandleUnion dkOrdinal_getRear(DKordinal *ORDINAL);
// 		DKhandleUnion dkOrdinal_dequeue(DKordinal *ORDINAL);
// 		DKhandleUnion dkOrdinal_remove(DKordinal *ORDINAL,DKssize INDEX);
// 		DKhandleUnion dkOrdinal_pop(DKordinal *ORDINAL);
// 			DKusize dkOrdinal_setSize(DKordinal *ORDINAL,DKusize SIZE);
// 			DKusize dkOrdinal_getSize(DKordinal *ORDINAL);
// 			DKboolean dkOrdinal_isEmpty(DKordinal *ORDINAL);
//			DKboolean dkOrdinal_isNotEmpty(DKordinal *ORDINAL);
// 			void dkOrdinal_setLock(DKordinal *ORDINAL,DKboolean LOCK);
// 			DKboolean dkOrdinal_getLock(DKordinal *ORDINAL);
// 				void dkOrdinal_debug(DKordinal *ORDINAL,DKnullString LABEL);

// // Aliases
// #define dkOrdinal_enqueue dkOrdinal_append
// #define dkOrdinal_push dkOrdinal_append
// #define dkOrdinal_getTop dkOrdinal_getRear

// // USIZE DARKordinal_search(DARKordinal *ORDINAL,HANDLE SOURCE,BOOLEAN *FOUND);
// // void DARKordinal_reverse(DARKordinal *ORDINAL,USIZE INDEX,USIZE SIZE);
// // void DARKordinal_shuffle(DARKordinal *ORDINAL,USIZE INDEX,USIZE SIZE);
