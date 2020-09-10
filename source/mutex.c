typedef struct
{
	mtx_t* lock;
} Mutex;

#routine mutex_enable(EXCEPTION,MUTEX)
{
	#local mtx_t* lock;
	if (!(lock = malloc(sizeof(mtx_t)))) exception_routineThrow(EXCEPTION,"MEMORY: malloc");
	if (mtx_init(lock,mtx_plain) == thrd_error) exception_routineThrow(EXCEPTION,"MUTEX: init");
	MUTEX.lock = lock;
};

#routine mutex_disable(MUTEX)
{
	mtx_unlock(MUTEX.lock);
	mtx_destroy(MUTEX.lock);
	free(MUTEX.lock);
	MUTEX.lock = NULL;
};

#routine mutex_destroy(MUTEX)
{
	if (MUTEX.lock) mutex_disable(MUTEX);
};

#routine mutex_lock(MUTEX)
{
	if (MUTEX.lock) mtx_lock(MUTEX.lock);
};

#routine mutex_unlock(MUTEX)
{
	if (MUTEX.lock) mtx_unlock(MUTEX.lock);
};

#routine mutex_setLock(EXCEPTION,MUTEX,LOCK)
{
	if (LOCK)
	{
		if (!(MUTEX.lock)) mutex_enable(EXCEPTION,MUTEX)
		else exception_routineThrow(EXCEPTION,"invalid LOCK");
	}
	else if (MUTEX.lock) mutex_disable(MUTEX)
	else exception_routineThrow(EXCEPTION,"invalid LOCK");
};

#macro mutex_getLock(MUTEX)
{
	MUTEX.lock
};
