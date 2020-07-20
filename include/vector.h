// Vector
DKvector *dkVector_create(void);
DKvector *dkVector_createFromCopy(DKvector *VECTOR,DKssize START,DKssize END);
DKvector *dkVector_destroy(DKvector *VECTOR);
	void dkVector_merge(DKvector *VECTOR,DKssize INDEX,DKvector *SOURCE,DKssize START,DKssize END);
	void dkVector_clear(DKvector *VECTOR);
	DKboolean dkVector_compare(DKvector *VECTOR1,DKvector *VECTOR2);
		void dkVector_prepend(DKvector *VECTOR,DKscalar VALUE);
		void dkVector_insert(DKvector *VECTOR,DKssize INDEX,DKscalar VALUE);
		void dkVector_append(DKvector *VECTOR,DKscalar VALUE);
		DKscalar dkVector_replace(DKvector *VECTOR,DKssize INDEX,DKscalar VALUE);
		DKscalar dkVector_set(DKvector *VECTOR,DKssize INDEX,DKscalar VALUE);
		void dkVector_swap(DKvector *VECTOR,DKssize INDEX1,DKssize INDEX2);
		DKscalar dkVector_getFront(DKvector *VECTOR);
		DKscalar dkVector_getIndex(DKvector *VECTOR,DKssize INDEX);
		DKscalar dkVector_getRear(DKvector *VECTOR);
		DKscalar dkVector_dequeue(DKvector *VECTOR);
		DKscalar dkVector_remove(DKvector *VECTOR,DKssize INDEX);
		DKscalar dkVector_pop(DKvector *VECTOR);
			DKusize dkVector_setSize(DKvector *VECTOR,DKusize SIZE);
			DKusize dkVector_getSize(DKvector *VECTOR);
			DKboolean dkVector_isEmpty(DKvector *VECTOR);
			void dkVector_setLock(DKvector *VECTOR,DKboolean LOCK);
			DKboolean dkVector_getLock(DKvector *VECTOR);
				void dkVector_debug(DKvector *VECTOR,DKnstring LABEL);

// Aliases
#define dkVector_enqueue dkVector_append
#define dkVector_push dkVector_append
#define dkVector_getTop dkVector_getRear

// USIZE DARKvector_search(DARKvector *VECTOR,SCALAR VALUE,BOOLEAN *FOUND);
// void DARKvector_reverse(DARKvector *VECTOR,USIZE INDEX,USIZE SIZE);
// void DARKvector_shuffle(DARKvector *VECTOR,USIZE INDEX,USIZE SIZE);
