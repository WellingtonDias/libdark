// List
DKlist *dkList_create(void);
DKlist *dkList_createFromPointer(DKundefined *ADDRESS,DKusize SIZE);
DKlist *dkList_createFromMemory(DKundefined *ADDRESS,DKusize SIZE,DKssize START,DKssize END);
DKlist *dkList_createFromCopy(DKlist *LIST,DKssize START,DKssize END);
DKlist *dkList_destroy(DKlist *LIST,DKboolean SOURCE);

void dkList_merge(DKlist *TARGET_LIST,DKssize TARGET_INDEX,DKlist *SOURCE_LIST,DKssize SOURCE_START,DKssize SOURCE_END);
void dkList_trim(DKlist *LIST);
void dkList_clear(DKlist *LIST);
DKboolean dkList_compare(DKlist *LIST1,DKlist *LIST2);

void dkList_insert(DKlist *LIST,DKssize INDEX,DKundefined VALUE);
void dkList_prepend(DKlist *LIST,DKundefined VALUE);
void dkList_append(DKlist *LIST,DKundefined VALUE);
DKundefined dkList_replace(DKlist *LIST,DKssize INDEX,DKundefined VALUE);
DKundefined dkList_set(DKlist *LIST,DKssize INDEX,DKundefined VALUE);
DKundefined dkList_get(DKlist *LIST,DKssize INDEX);
DKundefined dkList_getFront(DKlist *LIST);
DKundefined dkList_getRear(DKlist *LIST);
DKundefined dkList_remove(DKlist *LIST,DKssize INDEX);
DKundefined dkList_dequeue(DKlist *LIST);
DKundefined dkList_pop(DKlist *LIST);

void dkList_map(DKlist *LIST,DKundefined (*CALLBACK)(DKlist *LIST,DKusize INDEX,DKundefined VALUE));
void dkList_filter(DKlist *LIST,DKboolean (*CALLBACK)(DKlist *LIST,DKusize INDEX,DKundefined VALUE));
DKundefined dkList_reduce(DKlist *LIST,DKundefined (*CALLBACK)(DKlist *LIST,DKusize INDEX,DKundefined VALUE,DKundefined ACCUMULATOR));

DKundefined *dkList_getSource(DKlist *LIST);
DKusize dkList_getOffset(DKlist *LIST);
DKusize dkList_setSize(DKlist *LIST,DKusize SIZE);
DKusize dkList_getSize(DKlist *LIST);
DKboolean dkList_isEmpty(DKlist *LIST);
DKboolean dkList_isNotEmpty(DKlist *LIST);
DKusize dkList_getCapacity(DKlist *LIST);
DKboolean dkList_setLock(DKlist *LIST,DKboolean LOCK);
DKboolean dkList_getLock(DKlist *LIST);

void dkList_debug(DKlist *LIST,DKnullString LABEL);

#define dkList_enqueue dkList_append
#define dkList_push    dkList_append
#define dkList_getTop  dkList_getHear
