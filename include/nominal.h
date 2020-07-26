// Nominal
DKnominal *dkNominal_create(DKusize HASH_SIZE);
// DKnominal *dkNominal_createFromCopy(DKnominal *NOMINAL);
DKnominal *dkNominal_destroy(DKnominal *NOMINAL);
	// void dkNominal_merge(DKnominal *NOMINAL,DKnominal *SOURCE);
	void dkNominal_clear(DKnominal *NOMINAL);
	// DKboolean dkNominal_compare(DKnominal *NOMINAL1,DKnominal *NOMINAL2);
		void dkNominal_insert(DKnominal *NOMINAL,DKnullString KEY,DKvalue VALUE);
		// DKvalue dkNominal_replace(DKnominal *NOMINAL,DKnullString KEY,DKvalue VALUE);
		// DKvalue dkNominal_set(DKnominal *NOMINAL,DKnullString KEY,DKvalue VALUE);
		// void dkNominal_swap(DKnominal *NOMINAL,DKnullString KEY1,DKnullString KEY2);
		// DKvalue dkNominal_get(DKnominal *NOMINAL,DKnullString KEY);
		// DKvalue dkNominal_remove(DKnominal *NOMINAL,DKnullString KEY);
			DKusize dkNominal_getLength(DKnominal *NOMINAL);
			DKboolean dkNominal_isEmpty(DKnominal *NOMINAL);
			DKboolean dkNominal_isNotEmpty(DKnominal *NOMINAL);
			DKboolean dkNominal_setLock(DKnominal *NOMINAL,DKboolean LOCK);
			DKboolean dkNominal_getLock(DKnominal *NOMINAL);
				void dkNominal_debug(DKnominal *NOMINAL,DKnullString LABEL);
