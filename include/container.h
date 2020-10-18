// Container
Container *Container_create(UnsignedSize SIZE,Boolean FILL);
Container *Container_createFromString(String *STRING);
Container *Container_createFromBlob(Blob *BLOB);
Container *Container_createFromMemory(Pointer POINTER,UnsignedSize SIZE);
Container *Container_createFromDisk(NullString PATH);
void Container_saveToDisk(Container *CONTAINER,NullString PATH);
// Container *Container_createFromNetwork(NullString URI);
Container *Container_clone(Container *CONTAINER);
Container *Container_encapsulate(Pointer POINTER,UnsignedSize SIZE);
Container *Container_destroy(Container *CONTAINER);

Pointer Container_getPointer(Container *CONTAINER);
void Container_setSize(Container *CONTAINER,UnsignedSize SIZE,Boolean FILL);
UnsignedSize Container_getSize(Container *CONTAINER);
void Container_setLock(Container *CONTAINER,Boolean LOCK);
Boolean Container_getLock(Container *CONTAINER);

void Container_debug(Container *CONTAINER,NullString MESSAGE);
