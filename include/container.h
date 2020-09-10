// Container
Container *Container_create(UnsignedSize SIZE,Boolean FILL);
Container *Container_createFromMemory(Pointer POINTER,UnsignedSize SIZE);
container *Container_createFromDisk(NullString PATH);
void Container_saveToDisk(Container *CONTAINER,NullString PATH);
Container *Container_destroy(Container *CONTAINER);
Pointer Container_getPointer(Container *CONTAINER);
UnsignedSize Container_setSize(Container *CONTAINER,UnsignedSize SIZE);
UnsignedSize Container_getSize(Container *CONTAINER);
