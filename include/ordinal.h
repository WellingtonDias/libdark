// Ordinal
DKordinal *dkOrdinal_create(void);
DKordinal *dkOrdinal_createFromCopy(DKordinal *ORDINAL,DKssize START,DKssize END);
DKordinal *dkOrdinal_destroy(DKordinal *ORDINAL);
	void dkOrdinal_merge(DKordinal *ORDINAL,DKssize INDEX,DKordinal *SOURCE,DKssize START,DKssize END);
	void dkOrdinal_clear(DKordinal *ORDINAL);
	DKboolean dkOrdinal_compare(DKordinal *ORDINAL1,DKordinal *ORDINAL2);
		void dkOrdinal_prepend(DKordinal *ORDINAL,DKvalue VALUE);
		void dkOrdinal_insert(DKordinal *ORDINAL,DKssize INDEX,DKvalue VALUE);
		void dkOrdinal_append(DKordinal *ORDINAL,DKvalue VALUE);
		DKvalue dkOrdinal_replace(DKordinal *ORDINAL,DKssize INDEX,DKvalue VALUE);
		DKvalue dkOrdinal_set(DKordinal *ORDINAL,DKssize INDEX,DKvalue VALUE);
		void dkOrdinal_swap(DKordinal *ORDINAL,DKssize INDEX1,DKssize INDEX2);
		DKvalue dkOrdinal_getFront(DKordinal *ORDINAL);
		DKvalue dkOrdinal_getIndex(DKordinal *ORDINAL,DKssize INDEX);
		DKvalue dkOrdinal_getRear(DKordinal *ORDINAL);
		DKvalue dkOrdinal_dequeue(DKordinal *ORDINAL);
		DKvalue dkOrdinal_remove(DKordinal *ORDINAL,DKssize INDEX);
		DKvalue dkOrdinal_pop(DKordinal *ORDINAL);
			DKusize dkOrdinal_setLength(DKordinal *ORDINAL,DKusize LENGTH);
			DKusize dkOrdinal_getLength(DKordinal *ORDINAL);
			DKboolean dkOrdinal_isEmpty(DKordinal *ORDINAL);
			DKboolean dkOrdinal_isNotEmpty(DKordinal *ORDINAL);
			DKboolean dkOrdinal_setLock(DKordinal *ORDINAL,DKboolean LOCK);
			DKboolean dkOrdinal_getLock(DKordinal *ORDINAL);
				void dkOrdinal_debug(DKordinal *ORDINAL,DKnullString LABEL);

#define dkOrdinal_enqueue dkOrdinal_append
#define dkOrdinal_push dkOrdinal_append
#define dkOrdinal_getTop dkOrdinal_getRear
