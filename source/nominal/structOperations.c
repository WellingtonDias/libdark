void DKnominal_merge(DKnominal *NOMINAL,DKnominal *SOURCE);

void DKnominal_clear(DKnominal *NOMINAL);
// {
// 	safe_start(NOMINAL);
// 	for (DKusize hash = 0; hash < NOMINAL->hashSize; ++hash) block_clear(NOMINAL->block[hash],DKblock_pair);
// 	NOMINAL->length = 0;
// 	safe_endExit(NOMINAL);
// };

DKboolean DKnominal_compare(DKnominal *NOMINAL1,DKnominal *NOMINAL2);
