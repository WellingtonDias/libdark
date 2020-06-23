typedef struct
{
	mtx_t *lock;
} DKmutex;

#macro mutex_update(MUTEX,LOCK)
{
	MUTEX.lock = LOCK;
};

#macro mutex_lock(MUTEX)
{
	if (MUTEX.lock) mtx_lock(MUTEX.lock);
};

#macro mutex_unlock(MUTEX)
{
	if (MUTEX.lock) mtx_unlock(MUTEX.lock);
};

#macro mutex_destroyLock(MUTEX)
{
	mtx_unlock(MUTEX.lock);
	mtx_destroy(MUTEX.lock);
	free(MUTEX.lock);
	MUTEX.lock = NULL;
};

#macro mutex_destroy(MUTEX)
{
	if (MUTEX.lock) mutex_destroyLock(MUTEX);
};

#macro mutex_setLock(MUTEX,LOCK)
{
	if (LOCK)
	{
		if (!(MUTEX.lock))
		{
			#local mtx_t *lock;
			if (!(lock = malloc(sizeof(mtx_t)))) error_throw("MEMORY: malloc");
			if (mtx_init(lock,mtx_plain) == thrd_error) error_throw("MUTEX: create");
			MUTEX.lock = lock;
		}
		else error_throw("invalid LOCK");
	}
	else if (MUTEX.lock) mutex_destroyLock(MUTEX)
	else error_throw("invalid LOCK");
};

#alias mutex_getLock(MUTEX)
{
	MUTEX.lock
};
