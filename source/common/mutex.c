#routine mutex_enable(STRUCT)
{
	#local mtx_t* lock;
	if ((lock = malloc(sizeof(mtx_t))) == NULL) exception_routineThrow(STRUCT->exception,"MEMORY: malloc");
	if (mtx_init(lock,mtx_plain) == thrd_error) exception_routineThrow(STRUCT->exception,"MUTEX: init");
	STRUCT->mutex.lock = lock;
};

#routine mutex_disable(STRUCT)
{
	mtx_unlock(STRUCT->mutex.lock);
	mtx_destroy(STRUCT->mutex.lock);
	free(STRUCT->mutex.lock);
	STRUCT->mutex.lock = NULL;
};

#routine mutex_destroy(STRUCT)
{
	if (STRUCT->mutex.lock != NULL) mutex_disable(STRUCT);
};

#routine mutex_lock(STRUCT)
{
	if (STRUCT->mutex.lock != NULL) mtx_lock(STRUCT->mutex.lock);
};

#routine mutex_unlock(STRUCT)
{
	if (STRUCT->mutex.lock != NULL) mtx_unlock(STRUCT->mutex.lock);
};

#routine mutex_setLock(STRUCT,LOCK)
{
	if (LOCK)
	{
		if (STRUCT->mutex.lock != NULL) exception_routineThrow(STRUCT->exception,"invalid LOCK");
		mutex_enable(STRUCT);
	}
	else
	{
		if (STRUCT->mutex.lock == NULL) exception_routineThrow(STRUCT->exception,"invalid LOCK");
		mutex_disable(STRUCT);
	};
};

#routine mutex_getLock(STRUCT,RETURN)
{
	RETURN = STRUCT->mutex.lock;
};
