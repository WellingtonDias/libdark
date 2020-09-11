// Container
Container *Container_create(UnsignedSize SIZE,Boolean FILL);
Container *Container_destroy(Container *CONTAINER);

Pointer Container_getPointer(Container *CONTAINER);
UnsignedSize Container_setSize(Container *CONTAINER,UnsignedSize SIZE);
UnsignedSize Container_getSize(Container *CONTAINER);

void Container_debug(Container *CONTAINER,NullString MESSAGE);
