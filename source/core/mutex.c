typedef struct
{
	mtx_t *lock;
} DKmutex;

#macro mutex_enable(MUTEX)
{
	#local mtx_t *lock;
	if (!(lock = malloc(sizeof(mtx_t)))) error_throwReturn("MEMORY: malloc");
	if (mtx_init(lock,mtx_plain) == thrd_error) error_throwReturn("MUTEX: init");
	MUTEX.lock = lock;
};

#macro mutex_disable(MUTEX)
{
	mtx_unlock(MUTEX.lock);
	mtx_destroy(MUTEX.lock);
	free(MUTEX.lock);
	MUTEX.lock = NULL;
};

#macro mutex_update(MUTEX,LOCK)
{
	MUTEX.lock = LOCK;
};

#macro mutex_destroy(MUTEX)
{
	if (MUTEX.lock) mutex_disable(MUTEX);
};

#macro mutex_lock(MUTEX)
{
	if (MUTEX.lock) mtx_lock(MUTEX.lock);
};

#macro mutex_unlock(MUTEX)
{
	if (MUTEX.lock) mtx_unlock(MUTEX.lock);
};

#macro mutex_setLock(MUTEX,LOCK)
{
	if (LOCK)
	{
		if (!(MUTEX.lock)) mutex_enable(MUTEX)
		else error_throwReturn("invalid LOCK");
	}
	else if (MUTEX.lock) mutex_disable(MUTEX)
	else error_throwReturn("invalid LOCK");
};

#alias mutex_getLock(MUTEX)
{
	MUTEX.lock
};
