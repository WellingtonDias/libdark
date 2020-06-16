#macro safe_start(STRUCT)
{
	error_throwUnhandled();
	mutex_lock(STRUCT->mutex);
}

#macro safe_end(STRUCT)
{
	mutex_unlock(STRUCT->mutex);
	return;
}

#macro safe_endReturn(STRUCT,RETURN)
{
	mutex_unlock(STRUCT->mutex);
	return RETURN;
}

#macro safe_endCastReturn(STRUCT,RETURN,#TYPE)
{
	mutex_unlock(STRUCT->mutex);
	return (TYPE) RETURN;
}
